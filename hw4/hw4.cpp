#include <vector>
#include <iostream>
#include <cstdlib>  // For srand() and rand()
#include <fstream>
#include <cmath>
#include <algorithm>

using namespace std;

// Two-dimensional field class
//i know i could put this in a header file but i wanted it to be only on file so...
class Grid
{
  private:
    int 		nx_;// number of spin sites along x axis of grid
    int 		ny_;// number of spin sites along y axis of grid
    int     q_; //q the number of spins possible
    std::vector<int>	data_; // the spin at each point on the grid
  public: 
    Grid(int nx, int ny, int q) : nx_(nx), ny_(ny), q_(q), data_((nx)*(ny))
    {
    }
    int& operator() (int x, int y)       { return data_[x-1+nx_*(y-1)]; }
    int  operator() (int x, int y) const { return data_[x-1+nx_*(y-1)]; }
    
    int nx() const { return nx_; }
    int ny() const { return ny_; }
    int q() const   { return q_;}

    // the functions i use in order to get the peridoic BC
    // i know i could have used modulo division in the operator() function but 
    //i thought this was easyier to understand...
    int right(int x, int y)
    {
      if (x % nx_ == 0 )
        return data_[nx_*(y-1)];
      return data_[x+nx_*(y-1)];;
    }

    int left(int x, int y)
    {
      if (x % nx_ == 1 )
        return data_[nx_-1+nx_*(y-1)];
      return data_[x-2+nx_*(y-1)];
    }

    int up(int x, int y)
    {
      if(y==1)
        return data_[x-1+nx_*(ny_-1)];
      return data_[x-1+nx_*(y-2)];
    }

    int down(int x, int y)
    {
      if(y==ny_)
        return data_[x-1];
      return data_[x-1+nx_*(y)];
    }

};
void save_results(int q, double *averge)
{
  ofstream myfile;
  string name = "q_" + to_string(q)+".dat"; 
  myfile.open (name);
  for (int i = 50; i <= 150; ++i)
    {
      myfile<<averge[i]<<endl;
    }
  myfile.close();
}

void save_grid(Grid &grid, int beta) //used to save the spins on the grid to make a nice picture
{
  ofstream myfile;
  string name = "grid_beta_" + to_string(beta)+".dat"; 
  myfile.open (name);

  for (int y = 1; y <= 20; ++y)
  {
    for (int x = 1; x <= 20; ++x)
    {
      myfile << grid(x,y)<<" ";
    }
    myfile<<endl;
  }
  myfile.close();
}

void randomise(Grid &grid) //completly randomise every spin on the grid
{
  for (int y = 1; y <= grid.ny(); ++y)
    for(int x = 1; x <= grid.nx(); ++x )
      grid(x,y) = drand48()*grid.q();
}

int action(Grid &grid, int x, int y, int spin) //function to tell you the number of nabours that are off diffrent spins  
{
  int action = 0;
  if (spin != grid.up(x,y) )
    ++action;
  if (spin != grid.down(x,y) )
    ++action;
  if (spin != grid.left(x,y) )
    ++action;
  if (spin != grid.right(x,y) )
    ++action;
  //cout<<action<<endl;
  return action;
}


void evolver(Grid &grid, const int steps, const double beta)
{
  //This Sweeps though the grid Steps number of times and accepts or regeects
  //the proposed changes 
  int spin = 0;
  double exped;
  
  // i was orignally doing this picking random points but it turns out its faster to just sweep thought the sites in order
  for (int i = 0; i <= steps; ++i)//the number of times we sweep though the grid
    for(int y = 0; y<=grid.ny();++y)
      for(int x = 0; x<=grid.nx();++x)
      {
        spin = drand48() * grid.q();
        while(grid(x,y) == spin)
          spin = drand48() * grid.q();//generating a random spin that is not the same as the one at the site already
      
        exped = exp(-beta*( action(grid, x, y, spin) - action(grid,x,y, grid(x,y) ) ));
        
        if(drand48()<=exped)//acceptance critiera 
          grid(x,y) = spin;
      }
}

int max_element(int spins[], int q)//returns the  largest element in an array
{
  int arg = 0;
  for (int i = 0; i < q; ++i)
  {
    if (spins[i] > spins[arg])
      arg = i;
  }
  return spins[arg];
}


double fraction_of_sites(Grid &grid)//this returns the function f(sigma) as described in hw sheet
{
  int spins[grid.q()];
  for (int i = 0; i < grid.q(); ++i)
    spins[i] = 0;

  for (int y = 1; y <= grid.ny(); ++y)//this counts the number of occurances of each spins
    for(int x = 1; x <= grid.nx(); ++x )
      ++spins[grid(x,y)]; 

  return 1/float(grid.nx()*grid.ny()) * max_element(spins,grid.q());
}


double fractal_mag(Grid &grid)//This is fractional magnetisation M(sigma) from the hw sheet
{
  return ( grid.q()*fraction_of_sites(grid)-1 ) / ( grid.q() - 1 );  
}

void simulation(const int n, const int q,const int steps = 250,const string save = "no")
{
  Grid grid(n, n, q);
  
  double averge[250];
  for (int i = 0; i < 250; ++i)
    averge[i] = 0;

  int number_of_triles = 1;//this is the number of triles we run to find an averge 

       
  for (int i = 0; i < number_of_triles; ++i)
  {
    for (int beta = 50; beta <= 150; beta=beta+1)//running for differnet tempatures fixed beta
    { 
      //be carefull with how you change beta... 
      randomise(grid);//randomising the grid
      evolver(grid, steps, beta/100.); // evolving the grid
      averge[int(beta)] = averge[beta]+fractal_mag(grid); //keeping track of the averge result
      //save_grid(grid,beta);//this can be used to make the grid digrams

    }
    cout<<i<<endl;
  }

  for (int i = 50; i <= 150; ++i)
  {
      averge[i] = averge[i]/float(number_of_triles);
      cout<<"Beta="<<i/100.<<" <M>="<<averge[i]<<endl;
  }

  if(save =="yes")//this is used so i can graph the results, will save to a .dat file
    save_results(q, averge);
}


int main()
{
  srand48(123);
  //simulation(n, q, #steps, save? )
  /*
  //these are the ones i used to make graphs
  // these take a while to run...
  simulation(20,3,2000,"yes");
  simulation(20,4,2000,"yes");
  simulation(20,5,2000,"yes");
  */

  cout<<"this isnt going to take an averge, so it runs much faster"<<endl;
  simulation(20,5,1000,"no");


}
