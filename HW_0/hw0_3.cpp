#include<iostream>
using namespace std;

int main()
{
    unsigned long long int n;

    while( cin >> n )
    {
        unsigned long long int sum = (1+n)*n/2%997;
        cout << sum << endl;
    }

    return 0;
}