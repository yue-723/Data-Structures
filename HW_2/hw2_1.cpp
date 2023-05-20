#include <iostream>
using namespace std;

struct Node {
public:
 Node* left_child = nullptr;
 Node* right_child = nullptr;
 int data;
 Node(int val) :data(val) {};
};

class BinaryTree {
public:
 Node* root = nullptr;
 int nums;
 int totalVal;
 bool flag;
 int nodeVal_arr[51000] = { 0 };

 BinaryTree() :root(nullptr), nums(0), totalVal(0), flag(false) {}
 ~BinaryTree();

 void insertNode(Node*&, int);
 void deleteNode(Node*&, int);
 void deleteTree(Node*&);
 void printAll(Node*);
 void inorder_Traversal(Node*, int*&);
 int L_func(int);
 int M_func(int);
};

BinaryTree::~BinaryTree()
{
 deleteTree(root);
}
inline void BinaryTree::insertNode(Node*& curr_Node, int val)
{
 if (curr_Node == nullptr)
 {
  Node* new_Node = new Node(val);
  curr_Node = new_Node;
  totalVal += val;
  nums++;
  flag = true;
 }
 else
 {
  if (val <= curr_Node->data)
   insertNode(curr_Node->left_child, val);
  else
   insertNode(curr_Node->right_child, val);
 }
}
inline void BinaryTree::deleteNode(Node*& delete_Node, int val)
{
 if (val < delete_Node->data)
  deleteNode(delete_Node->left_child, val);
 else if (val > delete_Node->data)
  deleteNode(delete_Node->right_child, val);
 else {
  totalVal -= val;
  nums--;
  flag = true;
  if (delete_Node->left_child == nullptr && delete_Node->right_child == nullptr)
  {
   delete_Node = nullptr;
  }
  else if (delete_Node->left_child != nullptr && delete_Node->right_child == nullptr)
  {
   delete_Node = delete_Node->left_child;
  }
  else if (delete_Node->left_child == nullptr && delete_Node->right_child != nullptr)
  {
   delete_Node = delete_Node->right_child;
  }
  else
  {
   Node* parent_Node = delete_Node;
   Node* curr_Node = delete_Node->left_child;
   while (curr_Node->right_child != nullptr)
   {
    parent_Node = curr_Node;
    curr_Node = curr_Node->right_child;
   }
   delete_Node->data = curr_Node->data;
   if (delete_Node->left_child != curr_Node)
    parent_Node->right_child = curr_Node->left_child;
   else
    delete_Node->left_child = curr_Node->left_child;
   delete curr_Node;
  }
 }
}
inline void BinaryTree::deleteTree(Node*& curr_Node)
{
 if (curr_Node != nullptr)
 {
  deleteTree(curr_Node->left_child);
  deleteTree(curr_Node->right_child);
  delete curr_Node;
 }
 return;
}
inline void BinaryTree::printAll(Node* curr_Node)
{
 if (curr_Node != nullptr)
 {
  cout << curr_Node->data << "(";
  printAll(curr_Node->left_child);
  cout << ")(";
  printAll(curr_Node->right_child);
  cout << ")";
 }
}
int id = 0;
void BinaryTree::inorder_Traversal(Node* curr_Node, int*& arr)
{
 if (curr_Node != nullptr) {
  inorder_Traversal(curr_Node->left_child, arr);    //L
  arr[id] = curr_Node->data;
  id++;
  inorder_Traversal(curr_Node->right_child, arr);   //R
 }
}
inline int BinaryTree::L_func(int val)
{
 id = 0;
 int L_val = 0;
 if (flag) {
  int* ptr = &nodeVal_arr[0];
  inorder_Traversal(root, ptr);
  flag = false;
 }

 int curr_totalVal = totalVal;
 id = nums;
 while (curr_totalVal > val)
 {
  id--;
  curr_totalVal -= nodeVal_arr[id];
  L_val++;
 }

 return L_val;
}
inline int BinaryTree::M_func(int val)
{
 id = 0;
 int M_val = 0;
 if (flag) {
  int* ptr = &nodeVal_arr[0];
  inorder_Traversal(root, ptr);
  flag = false;
 }
 int curr_totalVal = totalVal;
 while (curr_totalVal >= val && M_val < nums)
 {
  curr_totalVal -= nodeVal_arr[M_val];
  M_val++;
 }

 return M_val - 1;
}
int main() {

 int n, val;
 char cmd;
 BinaryTree tree;
 cin >> n;
 for (int i = 0; i < n; i++) {
  cin >> val;
  tree.insertNode(tree.root, val);
 }
 while (cin >> cmd)
 {
  switch (cmd)
  {
  case 'I':
   cin >> val;
   tree.insertNode(tree.root, val);
   break;
  case 'D':
   cin >> val;
   tree.deleteNode(tree.root, val);
   break;
  case 'P':
   tree.printAll(tree.root);
   cout << endl;
   break;
  case 'L':
   cin >> val;
   cout << tree.L_func(val) << endl;
   break;
  case 'M':
   cin >> val;
   cout << tree.M_func(val) << endl;
   break;
  default:
   break;
  }
 }
 return 0;
}