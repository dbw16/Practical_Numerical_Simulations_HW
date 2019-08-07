#include <iostream> 
using std::cout; 
#include <cmath>
#include <fstream>
using namespace std;
ofstream out_data("hw2_2.txt");

class Planet
{
  public:
    double mass; //i know some of these could be private
    double x[2];
    double v[2];
}; 


void evolve_x(Planet p[], double dt) //the evolver for the position of the planets
{
  for (int i=0;i<4;i++)
  {
    for (int j=0;j<2;j++) 
      p[i].x[j] += dt * p[i].v[j]; //Updates the i and j position of the 4 planets 
  }
}

double dist(Planet p1,Planet p2)
{
  return sqrt(pow(p1.x[0]-p2.x[0],2) + pow(p1.x[1]-p2.x[1],2)); //gives us the distance between two planets
}

void evolve_v(Planet p[], double dt) // the evolver for the velocity. import to rember that force is a vector and has a direction 
{
  /** We are doing some calcuations twice which we do not need to as the Force(plante 1, planet 2) = Force(plante 2, planet 1)
      but i cant think of an easy way to fix with out adding alot of code and the program isnt exactly slow. 
  **/
  for (int i=0;i<4;i++)
  {
    double acc=0, acc_x = 0, acc_y = 0, theta = 0; // acc is acceleration: theta a varible to store angle between the planets  
    
    for (int j=0;j<4;j++)
      if (i!=j)
      {
        acc = (p[j].mass / pow(dist(p[i], p[j]),2)); //first find the magatnude of the total acceleration 
        theta = atan2( (p[j].x[1]-p[i].x[1]) , (p[j].x[0] - p[i].x[0])); //finds the angle between these planets atan2 is imporntant because atan is a multivaued funtion
        acc_x = acc * cos(theta); // gives us the x part of the acceleration
        acc_y = acc * sin(theta); // gives us the y part of the acceleration
        p[i].v[0] = p[i].v[0] + dt * acc_x; // we then update our x and y velocity 
        p[i].v[1] = p[i].v[1] + dt * acc_y;
      }
    
  }
}


void evolver(Planet ps[], double t_end, int n=20000)//this is large eneghe value for n to give us desired accurancy 
{
  double dt = t_end/float(n);
  dt = 1;
  evolve_x(ps,0.5*dt); //we take a half step for our symplectic integrator
  double t = 0.5*dt; 
  
  while(t<t_end-dt)
  {
    evolve_v(ps, dt); 
    evolve_x(ps, dt);
    // the belllow line wrights the x and y postions of each planet to a text file so i can graph them later
    //out_data<<ps[0].x[0]<<" "<<ps[0].x[1]<<" "<<ps[1].x[0]<<" "<<ps[1].x[1]<<" "<<ps[2].x[0]<<" "<<ps[2].x[1]<<" "<<ps[3].x[0]<<" "<<ps[3].x[1]<<endl;
    t = t + dt;
    cout<<t<<endl;
  }
    evolve_x(ps,0.5*dt); // we take that final half step
    cout<<t+ 0.5*dt <<endl; // sanity check
}


int main()
{
  Planet planets[4]; 
  double t_end =3;
  //Inishalsing our four planets
  planets[0].mass = 2.; planets[0].x[0] = -.5; planets[0].x[1] = 0.0; planets[0].v[0] = -.94; planets[0].v[1] = .65; 
  planets[1].mass = 1.; planets[1].x[0] = -.6; planets[1].x[1] = -0.2; planets[1].v[0] = 1.86; planets[1].v[1] = .7; 
  planets[2].mass = 1.;planets[2].x[0] = .5; planets[2].x[1] = 0.1; planets[2].v[0] = -.44; planets[2].v[1] = -1.4; 
  planets[3].mass = .4; planets[3].x[0] = .6; planets[3].x[1] = 0.3; planets[3].v[0] =  1.15; planets[3].v[1] = -1.5; 

  //We then starte the evoultion of or system
  evolver(planets, t_end);

  
  //print the postions of each planet at time t=3
  cout<<"location of the planets at t = 3 to 3sf"<<endl;
  for (int k=0;k<4;k++) 
    cout << k << ": " << planets[k].x[0] << "," << planets[k].x[1] << "\n";

}
