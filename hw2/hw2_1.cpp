#include <iostream>
#include <cmath> 
#include <vector>
#include <fstream>
#include <iomanip>
#include<string>


using namespace std;
ofstream out_data("file.txt");

double dudt(double x,double t)
{
	return -x*x*x * t * exp(-0.5*x*x);
}

double rk4(double x[2], double t_start, double t_end, int n, string wright="no")
{
  double t=t_start;
  double dt = (t_end - t_start)/double(n); 


  for (int i=0;i<n;i++)
  {
    double k1[] = {dt * x[1], dt * dudt(x[0], t)}; 
    double k2[] = {dt * (x[1] + 0.5 * k1[1]), dt * dudt(x[0] + 0.5*k1[0], t + 0.5*dt)}; 
    double k3[] = {dt * (x[1] + 0.5 * k2[1]), dt * dudt(x[0] + 0.5*k2[0], t + 0.5*dt)}; 
    double k4[] = {dt * (x[1] + k3[1]), dt * dudt(x[0] + k3[0],t+ dt)}; 
    
    for (int a=0;a<2;a++) 
    	x[a] += (k1[a]+2.0*k2[a]+2.0*k3[a]+k4[a]) / 6.0;
    
    t= t+dt;

    if (wright=="yes")
    {
      out_data<<x[0]<<" "<<t<<endl;
    }
  }
  //cout<<x[0]<<" "<< x[1]<<std::endl;
  return x[0] ;
}

double bisect_method(double c_high, double c_low, double t_start, double t_end, int n, double tol =.000001)
{
  //This first part makes sure c_high and c_low are on the corect side and if not it swaps them.
  double test[] = {0.0,c_high};
  if( rk4(test, 0, 10, 10000) - 1. > 0)
  {
    double temp = c_low;
    c_low = c_high;
    c_high = temp;
  }
  //Normal bisection method.
  double c_mid =(c_low+c_high)/2.0 ;
  double result = 99999999 ;
  while (abs(result) > tol)
  { 
    double x[] = {0.0 ,c_mid};
    result = rk4(x, 0, 10, 10000) - 1.;
    //cout<<c_mid<<"  "<<result<<endl;
    if(result > 0 )
      c_low = c_mid;
    else
      c_high = c_mid;
    
    c_mid =(c_low+c_high)/2.0 ;
  }
  return c_mid;
}

//This Function reads though all the Resut values and if it detect a change of sign in result then it stores
//the two values of C which are on either side. 
//it then returns this array of Cs.
vector<double> either_side(vector<double> v_r, vector<double> v_c)
{
  vector<double> cs;

  for (int i = 1; i < v_r.size(); ++i)
  {
    if (v_r[i]*v_r[i-1] < 0)
    {
      //cout<<v_r[i]<<v_r[i-1]<<endl;
      //cout<<v_c[i]<<v_c[i-1]<<endl
      cs.push_back(v_c[i]);
      cs.push_back(v_c[i-1]);
    }
  }
  return cs;
}

int main()
{
  std::vector<double> v_c;
  std::vector<double> v_r;
  std::vector<double> cs;

	for(double c =-2.5; c<2.5 ; c+=0.0001)
  //i was orginaly searching in a bigger range but now i know the soultions theres no need
	{
		double x[] = {0.0 ,c };
    //Used the bellow line in order to draw the graph of result vs c
    //out_data<<rk4(x,0, 10, 1000)-1<<" "<< c <<endl;
	  v_r.push_back(rk4(x,0, 10, 1000)-1);
    v_c.push_back(c);
  }


//we first ploted these two quanties to look for the values on eithe side of the 0 value
//However i decieded to implemnt code to do this instead. 
  cs = either_side(v_r,v_c);
  cout << std::setprecision(10) << std::fixed;
  cout<<"The values for x'(t=0) are" <<endl;
  for (int i = 0; i < cs.size(); i=i+2)
  {
    double c = bisect_method(cs[i], cs[i+1], 0, 10, 10000);
    cout<<c<<endl;
    //The following two lines wright to a file for graphing purpeous. 
    //double x[] = {0.0 ,c };
    //rk4(x, 0, 10, 1000,"yes");
  }

	return 0; 
}

