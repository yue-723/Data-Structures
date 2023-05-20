#include <iostream>
#include <vector>
#include <map>
using namespace std;

int main()
{
	int n, findNum;
	vector<int> nums;
	map<int, int> hashTable;

	cin >> n;
	for (int i = 0; i < n; i++)
	{
		int num;
		cin >> num;
		nums.push_back(num);
	}

	while (cin >> findNum)
	{
		int idx = 0;
		while (hashTable.find(findNum - nums[idx]) == hashTable.end())
		{
			hashTable[nums[idx]] = idx;
			idx++;
		}
		cout << nums[hashTable[findNum - nums[idx]]] << " " << nums[idx] << endl;
		hashTable.erase(hashTable.begin(), hashTable.end());
	}
}
