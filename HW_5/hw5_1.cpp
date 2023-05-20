#include <iostream>
#include <vector>
#include <map>
#include <queue>
using namespace std;

struct Edge
{
	int node1;
	int node2;
	int weight;
	Edge() : node1(0), node2(0), weight(0){};
	Edge(int n1, int n2, int w) : node1(n1), node2(n2), weight(w){};
};
struct compare
{
	bool operator()(const Edge &a, const Edge &b)
	{
		if (a.weight == b.weight && a.node1 != b.node1)
		{
			return a.node1 > b.node1;
		}
		else if (a.weight == b.weight && a.node1 == b.node1)
		{
			return a.node2 > b.node2;
		}
		else
		{
			return a.weight > b.weight;
		}
	}
};
map<int, int> set;
int findSetHead(int a)
{
	while (a != set[a])
		a = set[a];
	return a;
}
int main()
{

	int nodeNums, edgeNums;

	while (cin >> nodeNums >> edgeNums)
	{

		//int** adjMat = new int* [nodeNums + 1];
		//for (int i = 0; i <= nodeNums; i++)
		//{
		//    adjMat[i] = new int[nodeNums + 1];
		//    for (int j = 1; j <= nodeNums; j++)
		//        adjMat[i][j] = 0;
		//}

		int node1, node2, weight;
		priority_queue<Edge, vector<Edge>, compare> edges;
		for (int i = 0; i < edgeNums; i++)
		{
			cin >> node1 >> node2 >> weight;
			Edge e(node1, node2, weight);
			edges.push(e);
			set[node1] = node1;
			set[node2] = node2;
		}
		/*cout << "---------------------\n";
        while (!edges.empty())
        {
            Edge e = edges.top();
            outputFormat(e.node1, e.node2, e.weight);
            edges.pop();
        }*/
		priority_queue<Edge, vector<Edge>, compare> mst;
		while (!edges.empty())
		{
			Edge e = edges.top();
			if (findSetHead(e.node1) != findSetHead(e.node2))
			{
				set[findSetHead(e.node2)] = set[findSetHead(e.node1)];
				Edge temp;
				if (e.node1 < e.node2)
					temp = e;
				else
				{
					temp.node1 = e.node2;
					temp.node2 = e.node1;
					temp.weight = e.weight;
				}
				mst.push(temp);
			}
			edges.pop();
		}

		while (!mst.empty())
		{
			Edge e = mst.top();
			cout << e.node1 << " " << e.node2 << " " << e.weight << endl;
			mst.pop();
		}
		set.clear();
		//for (int i = 0; i <= nodeNums; i++)
		//    delete[] adjMat[i];
		//delete[] adjMat;
	}
}