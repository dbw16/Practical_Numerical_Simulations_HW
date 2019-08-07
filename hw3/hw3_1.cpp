#include "Field.h" 
#include <iostream>
#include <cstdlib>
#include <cstdlib>
#include <cmath> 
#include <vector>
#include <fstream>
#include <iomanip>
#include<string>
using namespace std;


// commented out as i dont want to creat a file on you computer
ofstream out_data("hw3_1.dat"); //used for ployying data


void out_put_graph_data(Field &phi)//used for graphing the data
{
	
	for (int x = 0; x < phi.nx(); x = x+1)
		{
			for (int y = 0; y <= phi.ny(); y=y+1)
			{
				out_data<<x<<" "<<y<<" "<<phi(x,y)<<endl;
			}
			out_data<<"\n";
		}
	
}


void set_outer_bourder(Field &phi)// sets outer border
{
	for (int i = 0; i <= phi.nx(); ++i)
	{
		phi(0,i) = 0;
		phi(phi.nx(),i) = 0;
		phi(i,0) = 0;
		phi(i,phi.nx()) = 0;
	}
}

void set_inner_bourder(Field &phi) // sets inner border
{
	for (int y = phi.ny()*.1; y <= phi.ny()*.2; ++y)
	{	for (int x = phi.nx()*.1; x <= phi.nx() * .8; ++x)
		{
			phi(x,y) = 1;
		}
	}

	for (int y = phi.ny()*.4; y <= phi.ny()*.9; ++y)
	{	for (int x = phi.nx()*.6; x <= phi.nx() * .7; ++x)
		{
			phi(x,y) = -1;
		}
	}
}


double avg_nabours(Field &phi, int x, int y, double omega = 1.95)//takes the averge of the 4 nabours and times it by omega
{
	return  omega*.25*( phi(x-1,y) + phi(x+1,y) + phi(x,y-1) + phi(x,y+1) ) + (1-omega) * phi(x,y);
}


bool on_border_true_flase(const double &x, const double &y,const int nx,const int ny)//function that tells us if a point is on a border
{
	//First Box
	if( (x == nx*.1 || x == nx*.8) && (y<=ny*.2 && y>=ny*.1) )
		return true;
	if( (y == ny*.1 || y == ny*.2) && (x>=nx*.1 && x<=nx*.8) )
		return true;
	//Second box
	if( (y == ny*.4 || y == ny*.9) && (x>=nx*.6 && x<=nx*.7) )
		return true;
	if( (x == nx*.6 || x == nx*.7) && (y<=ny*.9 && y>=ny*.4) )
		return true;

	return false;
}

vector<int> rand_points(int num_points, int grid_size) //generates a number of random points
{	
	std::vector<int> points;
	srand48(1727721);//could use time but dosent realy matter
	for (int i = 0; i < num_points; ++i)
	{
		points.push_back(drand48() * grid_size);
		points.push_back(drand48() * grid_size);
	}
	return points;
}


bool test_converg(const Field &phi, const vector<int> &points, double &old_value)
{
	double new_value = 0;

	for (int i = 0; i < points.size(); i=i+2)
		new_value = new_value + phi(points[i],points[i+1]);
		

	if (abs(new_value-old_value)<=.000006)//if the sum of the values at the random points have not changed will return true
		return true;

	old_value = new_value;
	return false;	
}

void solver(Field &phi)
{
	int a =0; //just to keep count of who many interations have run
	bool converged = false; 
	std::vector<int> points = rand_points(500,phi.nx() );//gentertating random points we will track to see if system has converged
	double old_value = 9999999999; //sumed value of the points
	
	while(converged == false)
	{
		for (int y = 1; y < phi.ny()-1; ++y)
		{
			for (int x = 1; x <= phi.nx()-1; ++x)
			{
				//std::cout<<x<<" "<<y<<std::endl;
				if (on_border_true_flase(x,y,phi.nx(), phi.ny() ) == false)//if the value is on the border function will return true and will not update that grid spot
				{
					phi(x,y) = avg_nabours(phi,x,y); // taking the averge of the 4 nabours multaplied by omega (Over realaction consant)		
				}
			}
		}
		cout<<phi(phi.nx()*.3,phi.nx()*.6)<<" "<<a<<endl; //print the value of phi(3/10,6/10)
		//out_data<<phi(phi.nx()*.3,phi.nx()*.6)<<endl;
		a++;
		converged = test_converg(phi, points, old_value); //convergence test
	}
}


int main()
{
	int n = 400;
  	Field phi(n,n); // creating our grid
  	phi = 0.0000001; //giveing all the points of the grid a value
  	set_outer_bourder(phi); //setting out boundary values
  	set_inner_bourder(phi); //setting inner boundary value
  	solver(phi); //solveing the PDE
  	cout<<"phi(3/10,6/10)= "<<phi(phi.nx()*.3,phi.nx()*.6)<<endl;
  	cout<<"I used a smaller grid 200x200 so this would run faster so the answer is only accurete to 2sf\n";
  	cout<<" using a 500x500 we get an answer of −0.158\n";



  	out_put_graph_data(phi);
  	return 0;
}