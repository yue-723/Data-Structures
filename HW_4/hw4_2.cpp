#include <iostream>
using namespace std;

int vertexNums, edgeNums;
bool found = false;
bool thirsty = false;

void GraphTraversal(int beg_Vtex, int dist_Vtex, bool *isOasis, bool **adjMat, bool *isVisited)
{
	if (thirsty && !isOasis[beg_Vtex])
		return;
	if (isOasis[beg_Vtex])
		thirsty = false;
	else
		thirsty = true;
	bool temp_thirsty = thirsty;
	if (beg_Vtex == dist_Vtex)
		found = true;
	else
	{
		isVisited[beg_Vtex] = true;
		for (int i = 0; i < vertexNums; i++)
		{
			if (adjMat[beg_Vtex][i] && !isVisited[i])
			{
				GraphTraversal(i, dist_Vtex, isOasis, adjMat, isVisited);
				if (found)
					break;
				thirsty = temp_thirsty;
			}
		}
	}
}

int main()
{

	cin >> vertexNums >> edgeNums;

	bool *isOasis = new bool[vertexNums];
	for (int i = 0; i < vertexNums; i++)
		cin >> isOasis[i];
	bool **adjMat = new bool *[vertexNums];
	for (int i = 0; i < vertexNums; i++)
	{
		adjMat[i] = new bool[vertexNums];
		for (int j = 0; j < vertexNums; j++)
			adjMat[i][j] = false;
	}
	int vtex1, vtex2;
	for (int i = 0; i < edgeNums; i++)
	{
		cin >> vtex1 >> vtex2;
		adjMat[vtex1][vtex2] = true;
		adjMat[vtex2][vtex1] = true;
	}
	bool *isVisited = new bool[vertexNums];
	while (cin >> vtex1 >> vtex2)
	{
		found = false;
		thirsty = false;
		for (int i = 0; i < vertexNums; i++)
			isVisited[i] = false;
		GraphTraversal(vtex1, vtex2, isOasis, adjMat, isVisited);
		if (found)
			cout << "Yes\n";
		else
			cout << "No\n";
	}
	delete[] isOasis;
	delete[] isVisited;
	for (int i = 0; i < vertexNums; i++)
		delete[] adjMat[i];
	delete[] adjMat;
}