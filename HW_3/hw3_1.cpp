#include <iostream>
using namespace std;

struct Node
{
public:
  Node *parent = nullptr;
  Node *left_child = nullptr;
  Node *right_child = nullptr;
  int data;
  char color = 'b';
  Node(int val, char colour) : data(val), color(colour){};
};

class RB_Tree
{
public:
  Node *root;
  RB_Tree() : root(nullptr) {}
  ~RB_Tree();

  void R_Rotate(Node *&);
  void L_Rotate(Node *&);
  void RL_Rotate(Node *&);
  void LR_Rotate(Node *&);
  void checkRoot();
  void checkColor_BeforeInsertion(Node *&, int);
  void checkColor_AfterInsertion(Node *&);

  void insertNode(Node *&, int);
  void deleteTree(Node *&);

  void printAll(Node *);
};

inline void RB_Tree::R_Rotate(Node *&critical_Node) // LL
{
  Node *curr_Node = critical_Node;

  Node *rotate_Node = curr_Node->left_child;

  curr_Node->left_child = rotate_Node->right_child;

  if (curr_Node->left_child != nullptr)
    curr_Node->left_child->parent = curr_Node;
  rotate_Node->right_child = curr_Node;
  rotate_Node->parent = curr_Node->parent;
  if (curr_Node->parent == nullptr)
  {
    root = rotate_Node;
  }
  else
  {
    if (rotate_Node->data <= curr_Node->parent->data)
      curr_Node->parent->left_child = rotate_Node;
    else
      curr_Node->parent->right_child = rotate_Node;
  }

  curr_Node->parent = rotate_Node;
  curr_Node = rotate_Node;
}

inline void RB_Tree::L_Rotate(Node *&critical_Node) // RR
{
  Node *curr_Node = critical_Node;
  Node *rotate_Node = curr_Node->right_child;

  curr_Node->right_child = rotate_Node->left_child;
  if (curr_Node->right_child != nullptr)
    curr_Node->right_child->parent = curr_Node;
  rotate_Node->left_child = curr_Node;
  rotate_Node->parent = curr_Node->parent;
  if (curr_Node->parent == nullptr)
    root = rotate_Node;
  else
  {
    if (rotate_Node->data <= curr_Node->parent->data)
      curr_Node->parent->left_child = rotate_Node;
    else
      curr_Node->parent->right_child = rotate_Node;
  }
  curr_Node->parent = rotate_Node;
  curr_Node = rotate_Node;
}

inline void RB_Tree::RL_Rotate(Node *&critical_Node)
{
  R_Rotate(critical_Node->right_child);
  L_Rotate(critical_Node->parent);
}

inline void RB_Tree::LR_Rotate(Node *&critical_Node)
{
  L_Rotate(critical_Node->left_child);
  R_Rotate(critical_Node->parent);
}

inline void RB_Tree::checkRoot()
{
  root->color = 'b';
}
inline void RB_Tree::checkColor_BeforeInsertion(Node *&curr_Node, int val)
{
  root->color = 'b';
  if (curr_Node != nullptr)
  {
    if (curr_Node->left_child != nullptr && curr_Node->right_child != nullptr)
      if (curr_Node->left_child->color == 'r' && curr_Node->right_child->color == 'r')
      {
        curr_Node->color = 'r';
        curr_Node->left_child->color = 'b';
        curr_Node->right_child->color = 'b';
      }
    if (curr_Node->parent != nullptr)
    {
      if (curr_Node->color == 'r' && curr_Node->parent->color == 'r')
      {
        if (curr_Node->parent->data > curr_Node->parent->parent->data)
        {
          if (curr_Node->data > curr_Node->parent->data) // RR
          {
            curr_Node->parent->parent->color = 'r';
            curr_Node->parent->color = 'b';
            curr_Node->color = 'r';
            L_Rotate(curr_Node->parent->parent);
          }
          else // RL
          {
            curr_Node->parent->parent->color = 'r';
            curr_Node->parent->color = 'r';
            curr_Node->color = 'b';
            RL_Rotate(curr_Node->parent->parent);
          }
        }
        else
        {
          if (curr_Node->data <= curr_Node->parent->data) // LL
          {
            curr_Node->parent->parent->color = 'r';
            curr_Node->parent->color = 'b';
            curr_Node->color = 'r';
            R_Rotate(curr_Node->parent->parent);
          }
          else // LR
          {
            curr_Node->parent->parent->color = 'r';
            curr_Node->parent->color = 'r';
            curr_Node->color = 'b';
            LR_Rotate(curr_Node->parent->parent);
          }
        }
      }
    }
    if (curr_Node->data < val)
    {
      checkColor_BeforeInsertion(curr_Node->right_child, val);
    }
    else
    {
      checkColor_BeforeInsertion(curr_Node->left_child, val);
    }

    root->color = 'b';
  }
}
inline void RB_Tree::checkColor_AfterInsertion(Node *&curr_Node)
{
  root->color = 'b';
  if (curr_Node != root && curr_Node->parent->color == 'r')
  {

    if (curr_Node->parent->parent->data < curr_Node->parent->data)
    {
      /*  a
         \
          b
         / \
        c   c  */
      if (curr_Node->parent->data < curr_Node->data) // RR
      {
        curr_Node->parent->parent->color = 'r';
        curr_Node->parent->color = 'b';
        curr_Node->color = 'r';
        L_Rotate(curr_Node->parent->parent);
      }

      else // RL
      {
        curr_Node->parent->parent->color = 'r';
        curr_Node->parent->color = 'r';
        curr_Node->color = 'b';
        RL_Rotate(curr_Node->parent->parent);
      }
    }
    else
    {
      /*     a
          /
         b
        / \
         c   c  */
      if (curr_Node->parent->data > curr_Node->data) // LL
      {
        curr_Node->parent->parent->color = 'r';
        curr_Node->parent->color = 'b';
        curr_Node->color = 'r';
        R_Rotate(curr_Node->parent->parent);
      }

      else // LR
      {
        curr_Node->parent->parent->color = 'r';
        curr_Node->parent->color = 'r';
        curr_Node->color = 'b';
        LR_Rotate(curr_Node->parent->parent);
      }
    }
  }
  root->color = 'b';
}
Node *temp = nullptr;
inline void RB_Tree::insertNode(Node *&curr_Node, int val)
{
  if (curr_Node == nullptr)
  {
    Node *new_Node = new Node(val, 'r');
    curr_Node = new_Node;
    curr_Node->parent = temp;
    checkColor_AfterInsertion(curr_Node);
  }
  else
  {
    temp = curr_Node;
    if (val <= curr_Node->data)
    {
      insertNode(curr_Node->left_child, val);
    }
    else
    {
      insertNode(curr_Node->right_child, val);
    }
  }
}

inline void RB_Tree::printAll(Node *curr_Node)
{
  if (curr_Node != nullptr)
  {
    cout << curr_Node->data << '_' << curr_Node->color << '(';
    printAll(curr_Node->left_child);
    cout << ")(";
    printAll(curr_Node->right_child);
    cout << ')';
  }
}

RB_Tree::~RB_Tree()
{
  deleteTree(root);
}

inline void RB_Tree::deleteTree(Node *&curr_Node)
{
  if (curr_Node != nullptr)
  {
    deleteTree(curr_Node->left_child);
    deleteTree(curr_Node->right_child);
    delete curr_Node;
  }
}

int main()
{

  int val;
  char cmd;
  RB_Tree tree;
  while (cin >> cmd)
  {
    switch (cmd)
    {
    case 'I':
      cin >> val;
      if (tree.root != nullptr)
        tree.checkColor_BeforeInsertion(tree.root, val);
      tree.insertNode(tree.root, val);
      break;
    case 'P':
      tree.printAll(tree.root);
      cout << endl;
      break;
    default:
      break;
    }
  }
  return 0;
}
