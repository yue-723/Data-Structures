#include<iostream>
using namespace std;
int main()
{
    int n,m;
    while(cin>>n>>m)
    {
      int a = n,b;
      if ((m/n)>=2)
          {
            if ((m%2) ==0)
              b = m/2 -1;
            else
              b = m/2;
        }
      else{
        while (a<m){
          if ((m-a)<a)
          {
            b = m - a;
            break;
          }
          a++;
        }
      }
      cout << b <<endl;
    }
    return 0;
}