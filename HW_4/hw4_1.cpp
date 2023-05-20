#include <iostream>
using namespace std;

void Swap(int &a, int &b)
{
  int temp = a;
  a = b;
  b = temp;
}
void Heapify(int *Seq, int SeqSize, int index)
{
  /*
                  0
          1              2
      3       4       5      6

  */
  int left_Child = 2 * index + 1;
  int right_Child = 2 * index + 2;
  int curr_Node = index;

  if (left_Child < SeqSize && Seq[left_Child] > Seq[curr_Node])
    curr_Node = left_Child;

  if (right_Child < SeqSize && Seq[right_Child] > Seq[curr_Node])
    curr_Node = right_Child;

  if (curr_Node != index)
  {
    Swap(Seq[index], Seq[curr_Node]);
    Heapify(Seq, SeqSize, curr_Node);
  }
}

void HeapSort(int *Seq, int SeqSize)
{
  for (int i = SeqSize - 1; i >= 0; i--)
  {
    Swap(Seq[0], Seq[i]);
    Heapify(Seq, i, 0);
  }
}

int main()
{

  int n;
  int m;
  cin >> n;
  for (int i = 0; i < n; i++)
  {
    cin >> m;
    int *Seq = new int[m];
    for (int j = 0; j < m; j++)
      cin >> Seq[j];

    for (int j = m / 2 - 1; j >= 0; j--)
      Heapify(Seq, m, j);

    HeapSort(Seq, m);

    for (int j = 0; j < m - 1; j++)
      cout << Seq[j] << ' ';
    cout << Seq[m - 1] << endl;

    delete[] Seq;
  }
  return 0;
}
