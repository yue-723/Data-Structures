#include <iostream>
#include <string>
using namespace std;

// Linked listStack
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

//笿 "<" 秈︽ユ传
string swapOperation(string str)
{
	if (str.find("<") != -1)
	{
		int i = str.find("<");  // "<"竚
		int index = i - 1;      //stringindex
		int bracketPair = 0;    //ゼで皌珹腹计秖

		string left, right;     // "<" 綟﹃

		if (str[index] != ']')  //тleft string
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

		if (!isdigit(str[index])) //тright string
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
		str.erase((i - left.length()), (swappedStr.length() + 1)); //璶ユ传ㄢ﹃珹 "<" 睲奔
		str.insert((i - left.length()), swappedStr);               //干秈ЧΘユ传﹃
		str = swapOperation(str); //т "<"
	}
	return str;
}
//矪瞶n[s]
string decryptString(string s)
{
	StackList decryptStack;
	for (int i = 0; i < s.length(); i++) {
		// 笿 ']'  popn[s]s
		if (s[i] == ']') {
			string temp;
			while (!decryptStack.isEmpty() && decryptStack.Top() != '[') {
				temp = decryptStack.Top() + temp;
				decryptStack.Pop();
			}
			// pop奔 '['
			decryptStack.Pop();

			int num = 0;    //repeatΩ计
			int times = 1;  //秈
			while (!decryptStack.isEmpty() && isdigit(decryptStack.Top())) {  //рn[s]n锣Θint
				num = int(decryptStack.Top() - '0') * times + num;
				times *= 10;
				decryptStack.Pop();
			}

			string repeat; //秆n[s]
			for (int j = 0; j < num; j++)
				repeat += temp;
			for (char c : repeat)
				decryptStack.Push(c);
		}
		// 笿 ']'玡常push秈stack
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
		inputStr = swapOperation(inputStr);        //ユ传
		cout << decryptString(inputStr) << endl;   //秆絏
	}

	return 0;
}
