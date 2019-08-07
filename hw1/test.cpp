#include <vector>
#include <iostream>
#include <cstdlib>  // For srand() and rand()
#include <fstream>
#include <cmath>
#include <algorithm>

using namespace std;

class Grid
{



  public:
  		int mass;
  		int x;
  		int y;
  Grid(int m,int x,int y) : mass(m), x(x), y(y)
  {} 

};

int main()
{
	Grid arid(100,5,4);
	cout<<arid.mass<<endl;
	cout<<arid.x<<endl;




}