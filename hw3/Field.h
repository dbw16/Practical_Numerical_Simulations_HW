#include <vector>
// Two-dimensional field
class Field
{
  private:
    int 		nx_;
    int 		ny_;
    std::vector<double>	data_; 
  public: 
    Field(int nx, int ny) : nx_(nx), ny_(ny), data_((nx+1)*(ny+1))
    {
    }
    double& operator() (int x, int y)       { return data_[x+(nx_+1)*y]; }
    double  operator() (int x, int y) const { return data_[x+(nx_+1)*y]; }
    Field& operator=(double val)
    {
      int n = (nx_+1)*(ny_+1);
      for (int i=0;i<n;i++) data_[i] = val;
      return *this;
    }
    int nx() const { return nx_; }
    int ny() const { return ny_; }
};
