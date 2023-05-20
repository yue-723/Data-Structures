#include <iostream>
#define MAX_NUMS 510000
using namespace std;

int main()
{

	int n, m;
	cin >> n;
	int *seq = new int[MAX_NUMS];
	for (int i = 0; i < MAX_NUMS; i++)
		seq[i] = -1;
	for (int i = 0; i < n; i++)
	{
		int query;
		cin >> query;
		seq[query] = i;
	}
	cin >> m;
	int searchNum;

	while (cin >> searchNum)
	{
		if (seq[searchNum] == -1)
			cout << -1 << endl;
		else
			cout << seq[searchNum] << endl;
	}
}