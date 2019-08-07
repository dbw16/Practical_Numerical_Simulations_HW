#include <iostream>
#include <iomanip>
using std::cout;


double dxdt(const double & v)
{
	return v;
}

double dvdt(const double & a)
{
	return a;
}

double dadt(const double & s, const double & v,const double & a)
{
	return -2.017 * a + (v * v) - s;
}

double rk4(double t_start, double t_end, double s_start, double v_start, double a_start, double dt = 0.00001 )
{
	/******************.                  NOTE
	we picked a value a dt = 0.00001  because a dt = 0.0001 changed the soultion in the second deecminal place. With a smaller dt of
	dt=0.000001 it only changed it past the third decimal place so a dt = 0.00001 is accurte Enough . 
	*******************/
	double n = (t_end - t_start) / dt;
	double k0, k1, k2, k3, l0, l1, l2, l3 ,m0, m1, m2, m3, si, vi, ai, si_new, vi_new ,ai_new;

	for(int i=0; i<n; i++)
	{
		k0 = dt * dxdt(v_start);
		l0 = dt * dvdt(a_start);
		m0 = dt * dadt(s_start,v_start,a_start);

		k1 = dt * dxdt(v_start+ .5 * l0);
		l1 = dt * dvdt(a_start+ .5 * m0);
		m1 = dt * dadt(s_start+ .5 * k0, v_start+ .5 * l0, a_start+ .5 * m0);

		k2 = dt * dxdt(v_start+ .5 * l1);
		l2 = dt * dvdt(a_start+ .5 * m1);
		m2 = dt * dadt(s_start+ .5 * k1, v_start+ .5 * l1, a_start+ .5 * m1);

		k3 = dt * dxdt(v_start+ .5 * l2);
		l3 = dt * dvdt(a_start+ .5 * m2);
		m3 = dt * dadt(s_start+ k2, v_start+ l2, a_start+ m2);

		si_new = s_start+ 1/6. * (k0 + 2* k1 + 2* k2 + k3);
		vi_new = v_start+ 1/6. * (l0 + 2* l1 + 2* l2 + l3);
		ai_new = a_start+ 1/6. * (m0 + 2* m1 + 2* m2 + m3);

		v_start = vi_new;
		a_start = ai_new;
		s_start = si_new;
	}
	return si_new;
}

int main()
{
	// rk4 argument(t_start, t_end, s_start,  v_start, a_start, double dt = 0.00001)
	cout << std::setprecision(2) << std::fixed;
	cout << rk4(0, 50, 0.02, 0, 0)<< std::endl;// this gives an answer of 6.94
	cout << rk4(0, 50, 0.0205, 0, 0)<< std::endl; // this gives an answer of 8.17
	return 0; 
}



