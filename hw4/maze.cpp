#include <iostream>
#include <stack>
using namespace std;
const int MAXSIZE=100; // up to 100 by 100 maze allowed
bool maze[MAXSIZE+2][MAXSIZE+2];                // 미로
bool mark[MAXSIZE+1][MAXSIZE+1] = {0};          // 방문한 노드 표시

enum directions { N, NE, E, SE, S, SW, W, NW };
struct offsets
{
    int a, b;
} mov[8] = { {-1, 0},{-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1} };
struct Items {
    Items(int xx=0, int yy=0, int dd=0): x(xx), y(yy), dir(dd) {}
    int x, y, dir;
};
template <class T>
ostream& operator<< (ostream& os, stack<T>& s) {
    // 스택의 내용을 역순으로 출력
    stack<T> s2;        // 역으로 출력하기 위해 임시 스택 s2 이용
    while(!s.empty()) {
        s2.push(s.top());
        s.pop();
    }
    while (!s2.empty()) {
        os << " -> " << s2.top();
        s.push(s2.top());
        s2.pop();
    }
    
    return os;
}
ostream& operator<<(ostream& os, Items& item)
{
    // 5개의 Items가 출력될 때마다 개행
    static int count = 0;
    os << "(" << item.x << "," << item.y << ")";
    count++;
    if ((count % 5) == 0) cout << endl;
    return os;
}
void Path(const int m, const int p)
{
    int nodes = 1;          // 방문한 노드 수를 저장하기 위해 시작점을 포함한 1로 초기화
    mark[1][1] = 1;         // (1,1) 시작
    stack<Items> stack;
    Items temp(1, 1, E);    // 1,1 위치에서 E방향부터 (시계방향으로) 순서대로 시도
    stack.push(temp);
    while (!stack.empty())
    {
        temp = stack.top(); stack.pop();    // 스택의 가장 위의 노드를 빼내 temp에 저장
        int i = temp.x; int j = temp.y; int d = temp.dir;
        while (d < 8)       // d 방향으로 이동
        {
            // (i,j)에서 (g,h)로 이동
            int g = i + mov[d].a; int h = j + mov[d].b;
            if ((g == m) && (h == p)) { // 끝에 도달했을 때
                cout << stack;          // 스택 안의 노드들을 거꾸로 출력
                // 마지막 경로((i,j) -> (m,p)) 출력 후 개행
                temp.x = i; temp.y = j; cout << " -> " << temp;
                temp.x = m; temp.y = p; cout << " -> " << temp << endl;
                
                // 방문한 노드 수 출력
                cout << "#nodes visited = "<< nodes << " out of 180" << endl;
                return;
            }
            // Path continued
            if ((!maze[g][h]) && (!mark[g][h])) {   // 새로운 위치로 이동할 수 있으면
                mark[g][h] = 1;                     // 방문한 적이 있다고 표시
                temp.x = i; temp.y = j; temp.dir = d + 1;   // 현 위치와 실패 시 다음에 시도할 방향 저장
                stack.push(temp);           // 스택에 추가
                nodes++;                    // 방문한 노드 수 +1
                i = g; j = h; d = N;        // N방향부터 (시계방향으로) 시도
            }
            else d++;   // 다음 방향 시도
        }
    }
    cout << "No path in maze." << endl;     // 경로가 없음
}
void getdata(istream& is, int& m, int & p)
{
    // 자료화일을 읽어들여 maze에 저장한다.
    is >> m >> p;
    for (int i = 0; i < m+2; i++) { maze[i][0] = 1; maze[i][p+1] = 1; }
    for (int j = 1; j <= p; j++) { maze[0][j] = 1; maze[m+1][j] = 1; }
    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= p; j++)
            is >> maze[i][j];
}