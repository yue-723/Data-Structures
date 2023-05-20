#include <iostream>
using namespace std;
int ROW, COL;

struct Point
{
    int x = 0;
    int y = 0;
};

//確認點是否在maze範圍裡
bool isValid(int row, int col)
{
    return (row >= 0) && (row < ROW) &&
        (col >= 0) && (col < COL);
}

//node四周圍的點
int rowNum[] = { -1, 0, 0, 1 };
int colNum[] = { 0, -1, 1, 0 };

struct QueueNode {
    Point pt;  // node的座標
    int dist;  // node與Start_Pt的距離
    QueueNode* next;
    QueueNode() :pt({ 0,0 }),dist(0), next(NULL) {};
    QueueNode(Point Pt,int dis) :pt(Pt), dist(dis), next(NULL) {};
};

//Linked list的queue
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

// 找最短距離
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

        // 走到終點
        if (currPt.x == dest.x && currPt.y == dest.y)
        {
            for (int i = 0; i < ROW; i++)
                delete[] visited[i];
            delete[] visited;
            return currDist;
        }

        // 找下個點
        q.Pop();

        for (int i = 0; i < 4; i++)
        {
            int row = currPt.x + rowNum[i];
            int col = currPt.y + colNum[i];

            // 把沒找過且是可走的加入queue
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

        //動態配置二維陣列 for maze
        int** maze;
        maze = new int* [ROW];
        for (int i = 0; i < ROW; i++)
            maze[i] = new int[COL];

        Point Start_Pt;    //起始點
        Point Dest_Pt;     //終點

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