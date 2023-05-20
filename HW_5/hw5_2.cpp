#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <climits>
using namespace std;

void getShortestPath(map<int, int> &nodeDist, int **adjMap, vector<int> pathStart, vector<int> pathEnd, int startNode)
{
	nodeDist[startNode] = 0;
	for (int i = 0; i < nodeDist.size() - 1; i++)
	{
		for (int j = 0; j < pathStart.size(); j++)
		{
			if (nodeDist[pathStart[j]] != INT_MAX &&
				nodeDist[pathEnd[j]] > nodeDist[pathStart[j]] + adjMap[pathStart[j]][pathEnd[j]])
			{
				nodeDist[pathEnd[j]] = nodeDist[pathStart[j]] + adjMap[pathStart[j]][pathEnd[j]];
			}
		}
	}

	vector<pair<int, int>> ans;
	for (const auto &dist : nodeDist)
	{
		ans.emplace_back(dist);
	}

	sort(ans.begin(), ans.end(),
		 [](const auto &x, const auto &y)
		 { return x.second < y.second; });

	vector<pair<int, int>>::iterator iter;
	for (iter = ans.begin(); iter != ans.end(); iter++)
	{
		if (iter->second != INT_MAX)
			cout << iter->first << " " << iter->second << endl;
	}

	ans.clear();
}
int main()
{

	int nodeNums, edgeNums;

	while (cin >> nodeNums >> edgeNums)
	{
		map<int, int> nodeDist;
		int **adjMat = new int *[nodeNums + 1];
		for (int i = 0; i <= nodeNums; i++)
		{
			nodeDist[i] = INT_MAX;

			adjMat[i] = new int[nodeNums + 1];
			for (int j = 1; j <= nodeNums; j++)
				adjMat[i][j] = 0;
		}

		int node1, node2, dist;
		vector<int> pathStart;
		vector<int> pathEnd;
		for (int i = 0; i < edgeNums; i++)
		{
			cin >> node1 >> node2 >> dist;
			adjMat[node1][node2] = dist;
			pathStart.push_back(node1);
			pathEnd.push_back(node2);
		}

		int startNode;
		cin >> startNode;
		getShortestPath(nodeDist, adjMat, pathStart, pathEnd, startNode);

		nodeDist.clear();
		pathStart.clear();
		pathEnd.clear();
		for (int i = 0; i <= nodeNums; i++)
			delete[] adjMat[i];
		delete[] adjMat;
	}
}