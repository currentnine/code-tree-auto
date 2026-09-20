#include <iostream>
#include <queue>
#include <vector>
#include <cmath>

using namespace std;

int N, L, R;
int board[50][50];
bool visited[50][50];

int dy[] = {-1, 1, 0, 0};
int dx[] = {0, 0, -1, 1};

bool bfs(int sy, int sx)
{
    queue<pair<int, int>> q;
    vector<pair<int, int>> group;

    q.push({sy, sx});
    group.push_back({sy, sx});
    visited[sy][sx] = true;

    int sum = board[sy][sx];

    while (!q.empty())
    {
        auto [y, x] = q.front();
        q.pop();

        // 현재 국가 기준으로 상하좌우 탐색
        for (int d = 0; d < 4; d++)
        {
            int ny = y + dy[d];
            int nx = x + dx[d];

            // 맵 범위를 벗어나면 제외
            if (ny < 0 || nx < 0 || ny >= N || nx >= N) continue;

            // 이미 같은 날 탐색한 국가는 제외
            if (visited[ny][nx]) continue;

            int diff = abs(board[y][x] - board[ny][nx]);

            // 인구 차이가 L 이상 R 이하일 때만 국경 개방
            if (diff < L || diff > R) continue;

            // 같은 연합에 포함
            visited[ny][nx] = true;
            q.push({ny, nx});
            group.push_back({ny, nx});

            // 연합 전체 인구 계산
            sum += board[ny][nx];
        }
    }

    // 연합이 자기 자신 하나뿐이면 인구 이동 없음
    if (group.size() == 1) return false;

    // 연합의 평균 인구 계산
    int population = sum / group.size();

    // 연합에 속한 모든 국가의 인구를 평균값으로 변경
    for (auto [y, x] : group) board[y][x] = population;

    return true;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> N >> L >> R;

    for (int y = 0; y < N; y++)
        for (int x = 0; x < N; x++)
            cin >> board[y][x];

    int day = 0;

    while (true)
    {
        // 하루가 시작될 때 방문 배열 초기화
        fill(&visited[0][0], &visited[0][0] + 50 * 50, false);

        // 오늘 하루 동안 인구 이동이 발생했는지 확인
        bool moved = false;

        for (int y = 0; y < N; y++)
        {
            for (int x = 0; x < N; x++)
            {
                // 아직 어느 연합에도 포함되지 않은 국가에서 BFS 시작
                if (!visited[y][x])
                {
                    if (bfs(y, x))
                        moved = true;
                }
            }
        }

        // 하루 동안 어떤 인구 이동도 없었다면 종료
        if (!moved)
            break;

        day++;
    }

    cout << day << '\n';
}