#include<iostream>
using namespace std;

int main()
{
    int a, b, temp;

    while( cin >> a >> b )
    {
        while( b!=0 )
        {
            temp = b;
            b = a%b;
            a = temp;
        }
        cout << a << endl;
    }

    return 0;
}