#include <iostream>
using namespace std;
int ROW, COL;

struct Point
{
    int x = 0;
    int y = 0;
};

//�T�{�I�O�_�bmaze�d���
bool isValid(int row, int col)
{
    return (row >= 0) && (row < ROW) &&
        (col >= 0) && (col < COL);
}

//node�|�P���I
int rowNum[] = { -1, 0, 0, 1 };
int colNum[] = { 0, -1, 1, 0 };

struct QueueNode {
    Point pt;  // node���y��
    int dist;  // node�PStart_Pt���Z��
    QueueNode* next;
    QueueNode() :pt({ 0,0 }),dist(0), next(NULL) {};
    QueueNode(Point Pt,int dis) :pt(Pt), dist(dis), next(NULL) {};
};

//Linked list��queue
class QueueList {
private:
    QueueNode* front;
    QueueNode* back;
public:
    QueueList() :front(NULL), back(NULL) {};
    ~QueueList();
    void Push(Point Pt, int dis);
    void Pop();
    bool isEmpty();
    QueueNode* getFront();
};

QueueList::~QueueList()
{ 
    while (!isEmpty()) {
        Pop();
    }
}

inline void QueueList::Push(Point Pt, int dis) {

    if (isEmpty()) {
        front = new QueueNode(Pt,dis);
        back = front;
        return;
    }

    QueueNode* newNode = new QueueNode(Pt, dis);
    back->next = newNode;
    back = newNode;         // update back pointer
}

inline void QueueList::Pop() {

    if (isEmpty()) 
        return;
    
    QueueNode* deleteNode = front;
    front = front->next;    // update front pointer
    delete deleteNode;
    //deleteNode = 0;
}

inline QueueNode* QueueList::getFront() {

    if (isEmpty()) 
        return NULL;
    
    return front;
}

inline bool QueueList::isEmpty() {

    return ((front && back) == 0);
}

// ��̵u�Z��
int BFS(int** maze, Point src, Point dest)
{
    
    if (!maze[src.x][src.y] || !maze[dest.x][dest.y])
        return -1;

    bool** visited;
    visited = new bool* [ROW];
    for (int i = 0; i < ROW; i++)
    {
        visited[i] = new bool[COL];
        for (int j = 0; j < COL; j++)
            visited[i][j] = false;
    }
    
    visited[src.x][src.y] = true;

    QueueList q;

    q.Push(src, 0);

    while (!q.isEmpty())
    {
        Point currPt = q.getFront()->pt;
        int currDist = q.getFront()->dist;

        // ������I
        if (currPt.x == dest.x && currPt.y == dest.y)
        {
            for (int i = 0; i < ROW; i++)
                delete[] visited[i];
            delete[] visited;
            return currDist;
        }

        // ��U���I
        q.Pop();

        for (int i = 0; i < 4; i++)
        {
            int row = currPt.x + rowNum[i];
            int col = currPt.y + colNum[i];

            // ��S��L�B�O�i�����[�Jqueue
            if (isValid(row, col) && maze[row][col] &&
                !visited[row][col])
            {
                visited[row][col] = true;
                q.Push({ row, col }, currDist + 1);
            }
        }
    }
    for (int i = 0; i < ROW; i++)
        delete[] visited[i];
    delete[] visited;

    return -1;
}

int main() {

    while (cin >> ROW >> COL) {

        //�ʺA�t�m�G���}�C for maze
        int** maze;
        maze = new int* [ROW];
        for (int i = 0; i < ROW; i++)
            maze[i] = new int[COL];

        Point Start_Pt;    //�_�l�I
        Point Dest_Pt;     //���I

        //load maze
        for (int i = 0; i < ROW; i++)
        {
            for (int j = 0; j < COL; j++)
            {
                char c;
                cin >> c;
                if (c == '#')
                    maze[i][j] = 0;
                else
                    maze[i][j] = 1;
                if (c == '.')
                    Start_Pt = { i, j };
                else if (c == '@')
                    Dest_Pt = { i, j };
            }
        }

        int dist = BFS(maze, Start_Pt, Dest_Pt);

        cout << dist << endl;

        //free memory
        for (int i = 0; i < ROW; i++)
            delete[] maze[i];
        delete[] maze;
    }

}