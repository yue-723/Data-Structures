#include <iostream>
#include <string>
using namespace std;

// Linked list��Stack
struct StackNode {
	char data;
	StackNode* next;
	StackNode() :data('\0'), next(NULL) {};
	StackNode(char c) :data(c), next(NULL) {};
};

class StackList {
private:
	StackNode* top;
public:
	StackList() : top(NULL) {};
	~StackList();
	void Push(char c);
	void Pop();
	bool isEmpty();
	char Top();
};

StackList::~StackList()
{
	while (!isEmpty()) 
		Pop();
}

inline void StackList::Push(char c) {

	if (isEmpty()) {
		top = new StackNode(c);
		return;
	}

	StackNode* newNode = new StackNode(c);  
	newNode->next = top;
	top = newNode;
}

inline void StackList::Pop() {

	if (isEmpty())
		return;

	StackNode* deleteNode = top;
	top = top->next;
	delete deleteNode;
}

inline bool StackList::isEmpty() {

	return (top == NULL);    
}

inline char StackList::Top() {

	if (isEmpty()) 
		return NULL;

	return top->data;
}

//�J�� "<" �i��洫
string swapOperation(string str)
{
	if (str.find("<") != -1)
	{
		int i = str.find("<");  // "<"����m
		int index = i - 1;      //string��index
		int bracketPair = 0;    //���ǰt�A�����ƶq

		string left, right;     //�s "<" �۾F���r��

		if (str[index] != ']')  //��left string
			left = str[index];
		else
		{
			while (index != 0)
			{
				if (str[index] == ']')
					bracketPair++;
				if (str[index] == '[')
					bracketPair--;
				index--;
				if (bracketPair == 0)
					break;
			}
			while (index >= 0 && isdigit(str[index]))
				index--;

			left = str.substr(index + 1, i - index - 1);
		}
		bracketPair = 0;
		index = i + 1;

		if (!isdigit(str[index])) //��right string
			right = str[index];
		else
		{
			while (isdigit(str[index]))
				index++;
			while (index < str.length())
			{
				if (str[index] == '[')
					bracketPair++;
				if (str[index] == ']')
					bracketPair--;
				if (bracketPair == 0)
					break;
				index++;
			}
			right = str.substr(i + 1, index - i);
		}

		string swappedStr = right + left;
		str.erase((i - left.length()), (swappedStr.length() + 1)); //�n�洫����r��]�A "<" �M��
		str.insert((i - left.length()), swappedStr);               //�ɶi�����洫���r��
		str = swapOperation(str); //��U�@�� "<"
	}
	return str;
}
//�B�zn[s]
string decryptString(string s)
{
	StackList decryptStack;
	for (int i = 0; i < s.length(); i++) {
		// �J�� ']' �� pop�Xn[s]��s
		if (s[i] == ']') {
			string temp;
			while (!decryptStack.isEmpty() && decryptStack.Top() != '[') {
				temp = decryptStack.Top() + temp;
				decryptStack.Pop();
			}
			// pop�� '['
			decryptStack.Pop();

			int num = 0;    //repeat������
			int times = 1;  //�Q�i��
			while (!decryptStack.isEmpty() && isdigit(decryptStack.Top())) {  //��n[s]��n�নint
				num = int(decryptStack.Top() - '0') * times + num;
				times *= 10;
				decryptStack.Pop();
			}

			string repeat; //��n[s]
			for (int j = 0; j < num; j++)
				repeat += temp;
			for (char c : repeat)
				decryptStack.Push(c);
		}
		// �J�� ']'�e��push�istack
		else
			decryptStack.Push(s[i]);
	}
	string ans;
	while (!decryptStack.isEmpty()) {
		ans = decryptStack.Top() + ans;
		decryptStack.Pop();
	}
	return ans;
}

int main()
{
	string inputStr;
	while (cin >> inputStr)
	{
		inputStr = swapOperation(inputStr);        //���洫
		cout << decryptString(inputStr) << endl;   //�b�ѽX
	}

	return 0;
}
