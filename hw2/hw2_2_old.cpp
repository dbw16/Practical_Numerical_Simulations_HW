#include <iostream>
#include <iomanip>
#include <cmath> 
#include <fstream>

#include <vector>

using namespace std;

using namespace std;
ofstream out_data("hw2_2.txt");


class Planet
{
  private:
    double	m;
  public: 
    double	x[2];	// position of planet
    double	v[2];	// velocity of planet

    Planet(double mass, double x0, double x1, double v0, double v1) 
    {
      m = mass; 
      x[0] = x0; x[1] = x1; 
      v[0] = v0; v[1] = v1; 
    }

    double mass() const { return m; } 
    double kinetic_energy() const { return 0.5*m*(v[0]*v[0]+v[1]*v[1]); } 
};

double dist(Planet forced_p, Planet p2)
{ 
  return sqrt(pow(p2.x[0]-forced_p.x[0],2) + pow(p2.x[1]-forced_p.x[1],2));
}


vector<double> force_on_planet(Planet forced_p, Planet p1, Planet p2, Planet p3)
{
  double force_x, force_y, theta, force = 0, G = 1;
  
  force = G  * (p1.mass() / pow(dist(forced_p, p1),2));
  theta = atan( (p1.x[0]-forced_p.x[0])/(p1.x[1]-forced_p.x[1]));
  force_x = force*cos(theta);
  force_y = force*sin(theta);

  force = (G * p2.mass() / pow(dist(forced_p, p2),2));
  theta = atan( (p2.x[0]-forced_p.x[0])/(p2.x[1]-forced_p.x[1]));
  force_x = force_x + force*cos(theta);
  force_y = force_y + force*sin(theta);

  force = (G * p3.mass() / pow(dist(forced_p, p3),2));
  theta = atan( (p3.x[0]-forced_p.x[0])/(p3.x[1]-forced_p.x[1]));
  force_x = force_x + force*cos(theta);
  force_y = force_y + force*sin(theta);
  vector<double> force_x_y;
  force_x_y.push_back(force_x);
  force_x_y.push_back(force_y);
  return force_x_y;
}


Planet planet_revolver(Planet p1, Planet p2, Planet p3, Planet p4, double t_end, int n = 10000)
{
	float dt = t_end/float(n);
  float t = 0;
  vector<double> f;
   
   cout<< "time t= "<<t<<endl;
   cout <<"position of p1 "<< p1.x[0]<<" "<<p1.x[1]<<endl;
   cout <<"position of p2 "<< p2.x[0]<<" "<<p2.x[1]<<endl;
   cout <<"position of p3 "<< p3.x[0]<<" "<<p3.x[1]<<endl;
   cout <<"position of p4 "<< p4.x[0]<<" "<<p4.x[1]<<endl;

   p1.x[0] = p1.x[0] + dt/.2 * p1.v[0];
   p1.x[1] = p1.x[1] + dt/.2 * p1.v[1];
   

   p2.x[0] = p2.x[0] + dt/.2 * p2.v[0];
   p2.x[1] = p2.x[1] + dt/.2 * p2.v[1];


   p3.x[0] = p3.x[0] + dt/.2 * p3.v[0];
   p3.x[1] = p3.x[1] + dt/.2 * p3.v[1];


   p4.x[0] = p4.x[0] + dt/.2 * p4.v[0];
   p4.x[1] = p4.x[1] + dt/.2 * p4.v[1];

   cout<< "time t= "<<t<<endl;
   cout <<"position of p1 "<< p1.x[0]<<" "<<p1.x[1]<<endl;
   cout <<"position of p2 "<< p2.x[0]<<" "<<p2.x[1]<<endl;
   cout <<"position of p3 "<< p3.x[0]<<" "<<p3.x[1]<<endl;
   cout <<"position of p4 "<< p4.x[0]<<" "<<p4.x[1]<<endl;

	while(t < t_end)
	{
   f = force_on_planet(p1,p2,p3,p4);
   p1.v[0] = p1.v[0] + dt * f[0];
   p1.v[1] = p1.v[1] + dt * f[1];
   p1.x[0] = p1.x[0] + dt * p1.v[0];
   p1.x[1] = p1.x[1] + dt * p1.v[1];

   f = force_on_planet(p2,p1,p3,p4);
   p2.v[0] = p2.v[0] + dt * f[0];
   p2.v[1] = p2.v[1] + dt * f[1];
   p2.x[0] = p2.x[0] + dt * p2.v[0];
   p2.x[1] = p2.x[1] + dt * p2.v[1];

   f = force_on_planet(p3,p2,p1,p4);
   p3.v[0] = p3.v[0] + dt * f[0];
   p3.v[1] = p3.v[1] + dt * f[1];
   p3.x[0] = p3.x[0] + dt * p3.v[0];
   p3.x[1] = p3.x[1] + dt * p3.v[1];

   f = force_on_planet(p4,p2,p3,p1);
   p4.v[0] = p4.v[0] + dt * f[0];
   p4.v[1] = p4.v[1] + dt * f[1];
   p4.x[0] = p4.x[0] + dt * p4.v[0];
   p4.x[1] = p4.x[1] + dt * p4.v[1];


   out_data<<p1.x[0]<<" "<<p1.x[1]<<" "<<p2.x[0]<<" "<<p2.x[1]<<" "<<p3.x[0]<<" "<<p3.x[1]<<" "<<p4.x[0]<<" "<<p4.x[1]<<endl;
   t = t + dt;
	}

   cout<< "time t= "<<t<<endl;
   cout <<"position of p1 "<< p1.x[0]<<" "<<p1.x[1]<<endl;
   cout <<"position of p2 "<< p2.x[0]<<" "<<p2.x[1]<<endl;
   cout <<"position of p3 "<< p3.x[0]<<" "<<p3.x[1]<<endl;
   cout <<"position of p4 "<< p4.x[0]<<" "<<p4.x[1]<<endl;

   return p1, p2, p3, p4;

}

int main()
{
  Planet p1(2., -.5, 0, -.94, .65);
  Planet p2(1., -.6, -.2, 1.86, .7); 
  Planet p3(1., .5, .1, -.44, -1.4); 
  Planet p4(.4, .6, .3, 1.5, -1.5);  

  cout <<"position of p1 "<< p1.x[0]<<" "<<p1.x[1]<<endl;
  cout <<"position of p2 "<< p2.x[0]<<" "<<p2.x[1]<<endl;
  cout <<"position of p3 "<< p3.x[0]<<" "<<p3.x[1]<<endl;
  cout <<"position of p4 "<< p4.x[0]<<" "<<p4.x[1]<<endl;

  p1, p2, p3, p4 = planet_revolver(p1,p2,p3,p4,3);


}