#include <iostream>
#include <iomanip>

using std::cout;


double f1(double x,double t)
{
	return -2 * x * x * t;
}

double f2(double x,double t)
{
	return (x + t)* (x + t);
}

double rk4(double t_start, double t_end, double x_start , double (*f)(double,double), double n = 2000 )
{
	/********* NOTE
	We picked a dt = 0.001 as it was small enough to agree to 4 decmial places with our
	anyaltical results. 
	**********/
	
	double dt = (t_end - t_start) / n;
	cout<<n<<std::endl;
	double x1 ,x2, x3, x4, ti, xi, xi_new;

	xi = x_start;
	double dt2= dt/2.;

	for(ti=0; ti<t_end; ti=ti+dt)
	{
		x1 = f(xi,ti);
		x2 = f(xi+ dt2*x1, ti+dt2);
		x3 = f(xi+ dt2*x2, ti+dt2);
		x4 = f(xi+ dt*x3, ti+dt);

		xi_new = xi + dt/6.0 * (x1+ 2*x2 + 2*x3+ x4);
		xi = xi_new;
		//cout<<xi<<std::endl;
	}
	return xi;

}

int main()
{
	// rk4 argument(start time, end time, start point, function, timestep=0.0001)
	
	cout << std::setprecision(25) << std::fixed;
	cout <<"the solution to the first ode is" <<rk4(0., 2., 1., f1)<< std::endl; // this gives an answer of .20000
	cout << "the solution to the second ode is " <<rk4(-1., 1., -1., f2)<< std::endl; // this gives an answer of 0.2418
	return 0; 
}

