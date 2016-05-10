#include <iostream>
using namespace std;
class A
{
public:

  int a;
  int b;

  A(int a,int b)
  {
    this->a=a;
    this->b=b;
  }

};
int main(int argc, char const *argv[])
{
  /* code */
  A * point = new A(3,4);
  A obj(1,2);
  int qp[10];
  int * pq = new int[10];
  for (int i = 0; i < 10; i++)
  {
    qp[i] = 9-i;
    pq[i] = i;
  }
  cout<<obj.a<<endl<<point->a<<endl<<pq[9]<<qp[9];
  return 0;
}
