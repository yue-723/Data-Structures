#include <iostream>
using namespace std;

int getMaxHeight(int h1, int h2)
{
	return h1 > h2 ? h1 : h2;
}

struct Node {
public:
	Node* left_child = nullptr;
	Node* right_child = nullptr;
	int data;
	int height;
	Node(int val, int h) :data(val), height(h) {};
};

class AVL_Tree {
public:
	Node* root = nullptr;

	AVL_Tree() :root(nullptr) {}
	~AVL_Tree();

	void R_Rotate(Node*&);
	void  L_Rotate(Node*&);
	void RL_Rotate(Node*&);
	void LR_Rotate(Node*&);
	int getHeight(Node*);

	void insertNode(Node*&, int);
	void deleteNode(Node*&, int);
	void deleteTree(Node*&);

	void printAll(int);
	void preorder_Traversal(Node*);
	void inorder_Traversal(Node*);
	void postorder_Traversal(Node*);
};

AVL_Tree::~AVL_Tree()
{
	deleteTree(root);
}

inline void AVL_Tree::R_Rotate(Node*& curr_Node)
{
	if (curr_Node->left_child != nullptr)
	{
		Node* rotate_Node = curr_Node->left_child;
		curr_Node->left_child = rotate_Node->right_child;
		rotate_Node->right_child = curr_Node;
		curr_Node->height = getMaxHeight(getHeight(curr_Node->left_child), getHeight(curr_Node->right_child)) + 1;
		rotate_Node->height = getMaxHeight(getHeight(rotate_Node->left_child), getHeight(rotate_Node->right_child)) + 1;
		curr_Node = rotate_Node;
	}

}

inline void AVL_Tree::L_Rotate(Node*& curr_Node)
{
	if (curr_Node->right_child != nullptr)
	{
		Node* rotate_Node = curr_Node->right_child;
		curr_Node->right_child = rotate_Node->left_child;
		rotate_Node->left_child = curr_Node;
		curr_Node->height = getMaxHeight(getHeight(curr_Node->left_child), getHeight(curr_Node->right_child)) + 1;
		rotate_Node->height = getMaxHeight(getHeight(rotate_Node->left_child), getHeight(rotate_Node->right_child)) + 1;
		curr_Node = rotate_Node;
	}

}

inline void AVL_Tree::RL_Rotate(Node*& curr_Node)
{
	R_Rotate(curr_Node->right_child);
	L_Rotate(curr_Node);
}

inline void AVL_Tree::LR_Rotate(Node*& curr_Node)
{
	L_Rotate(curr_Node->left_child);
	R_Rotate(curr_Node);
}

inline int AVL_Tree::getHeight(Node* curr_Node)
{
	if (curr_Node == nullptr)
		return -1;
	else
		return curr_Node->height;
}
inline void AVL_Tree::insertNode(Node*& curr_Node, int val)
{
	if (curr_Node == nullptr)
	{
		Node* new_Node = new Node(val, 0);
		curr_Node = new_Node;
	}
	else
	{
		if (val <= curr_Node->data)
		{
			insertNode(curr_Node->left_child, val);
			curr_Node->height = getMaxHeight(getHeight(curr_Node->left_child), getHeight(curr_Node->right_child)) + 1;
			if (getHeight(curr_Node->left_child) - getHeight(curr_Node->right_child) > 1)
			{
				if (val < curr_Node->left_child->data)		 // LL
					R_Rotate(curr_Node);
				else						// LR
					LR_Rotate(curr_Node);
			}
		}

		else
		{
			insertNode(curr_Node->right_child, val);
			curr_Node->height = getMaxHeight(getHeight(curr_Node->left_child), getHeight(curr_Node->right_child)) + 1;
			if (getHeight(curr_Node->right_child) - getHeight(curr_Node->left_child) > 1)
			{
				if (val > curr_Node->right_child->data)			// RR
					L_Rotate(curr_Node);
				else							// RL
					RL_Rotate(curr_Node);
			}
		}
	}

}
inline void AVL_Tree::deleteNode(Node*& delete_Node, int val)
{
	if (val < delete_Node->data)
		deleteNode(delete_Node->left_child, val);
	else if (val > delete_Node->data)
		deleteNode(delete_Node->right_child, val);
	else {
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

			Node* curr_Node = delete_Node->left_child;
			while (curr_Node->right_child != nullptr)
				curr_Node = curr_Node->right_child;

			delete_Node->data = curr_Node->data;
			deleteNode(delete_Node->left_child, delete_Node->data);
			delete curr_Node;

		}
	}
	if (delete_Node == nullptr)
		return;
	delete_Node->height = getMaxHeight(getHeight(delete_Node->left_child), getHeight(delete_Node->right_child)) + 1;

	if (getHeight(delete_Node->right_child) - getHeight(delete_Node->left_child) > 1) // R > L
	{
		if (getHeight(delete_Node->right_child->right_child) - getHeight(delete_Node->right_child->left_child) >= 0)  
		{
			L_Rotate(delete_Node);
		}
		else // RL
			RL_Rotate(delete_Node);
	}
	else if (getHeight(delete_Node->left_child) - getHeight(delete_Node->right_child) > 1)  // L > R
	{
		if (getHeight(delete_Node->left_child->left_child) - getHeight(delete_Node->left_child->right_child) >= 0)  
		{
			R_Rotate(delete_Node);
		}
		else		// LR
			LR_Rotate(delete_Node);
	}
}
inline void AVL_Tree::deleteTree(Node*& curr_Node)
{
	if (curr_Node != nullptr)
	{
		deleteTree(curr_Node->left_child);
		deleteTree(curr_Node->right_child);
		delete curr_Node;
	}
	return;
}
inline void AVL_Tree::printAll(int val)
{
	switch (val)
	{
	case 1:         //preorder
		preorder_Traversal(root);
		break;		//inorder
	case 2:
		inorder_Traversal(root);
		break;
	case 3:			//postorder
		postorder_Traversal(root);
		break;
	default:
		break;
	}
	cout << endl;
}
inline void AVL_Tree::preorder_Traversal(Node* curr_Node)
{
	if (curr_Node != nullptr) {
		cout << curr_Node->data << "(";
		preorder_Traversal(curr_Node->left_child);
		cout << ")(";
		preorder_Traversal(curr_Node->right_child);
		cout << ")";
	}
}
inline void AVL_Tree::inorder_Traversal(Node* curr_Node)
{
	if (curr_Node != nullptr) {
		cout << "(";
		inorder_Traversal(curr_Node->left_child);
		cout << ")" << curr_Node->data << "(";
		inorder_Traversal(curr_Node->right_child);
		cout << ")";
	}
}
inline void AVL_Tree::postorder_Traversal(Node* curr_Node)
{
	if (curr_Node != nullptr) {
		cout << "(";
		postorder_Traversal(curr_Node->left_child);
		cout << ")(";
		postorder_Traversal(curr_Node->right_child);
		cout << ")" << curr_Node->data;
	}
}
int main() {

	int n, val;
	char cmd;
	AVL_Tree tree;
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
			cin >> val;
			tree.printAll(val);
			break;
		default:
			break;
		}
	}
	return 0;
}