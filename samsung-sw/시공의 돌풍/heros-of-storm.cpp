#include <iostream>
#include <vector>
using namespace std;

int n, m, t;
vector<vector<int>> board;

int c_upper, d_upper;

int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

// 먼지 확산
void spread() {
    vector<vector<int>> next(n, vector<int>(m, 0));

    // 청소기 위치
    next[c_upper][0] = -1;
    next[d_upper][0] = -1;

    for (int x = 0; x < n; x++) {
        for (int y = 0; y < m; y++) {
            if (board[x][y] <= 0)
                continue;

            int amount = board[x][y] / 5;
            int cnt = 0;

            for (int d = 0; d < 4; d++) {
                int nx = x + dx[d];
                int ny = y + dy[d];

                if (nx < 0 || nx >= n || ny < 0 || ny >= m)
                    continue;

                if (board[nx][ny] == -1)
                    continue;

                next[nx][ny] += amount;
                cnt++;
            }

            next[x][y] += board[x][y] - amount * cnt;
        }
    }

    board = next;
}

// 시공의 돌풍 작동
void clean() {

    // ======================
    // 위쪽 : 반시계 방향
    // ======================

    // 왼쪽 열 : 아래 -> 위
    for (int x = c_upper - 1; x > 0; x--)
        board[x][0] = board[x - 1][0];

    // 위쪽 행 : 오른쪽 -> 왼쪽
    for (int y = 0; y < m - 1; y++)
        board[0][y] = board[0][y + 1];

    // 오른쪽 열 : 아래 -> 위가 아니라 위쪽 영역에서는 아래 방향 값 가져오기
    for (int x = 0; x < c_upper; x++)
        board[x][m - 1] = board[x + 1][m - 1];

    // 청소기 행 : 왼쪽으로 값 이동
    for (int y = m - 1; y > 1; y--)
        board[c_upper][y] = board[c_upper][y - 1];

    board[c_upper][1] = 0;


    // ======================
    // 아래쪽 : 시계 방향
    // ======================

    // 왼쪽 열 : 위 -> 아래
    for (int x = d_upper + 1; x < n - 1; x++)
        board[x][0] = board[x + 1][0];

    // 아래쪽 행 : 오른쪽 -> 왼쪽
    for (int y = 0; y < m - 1; y++)
        board[n - 1][y] = board[n - 1][y + 1];

    // 오른쪽 열 : 아래 -> 위
    for (int x = n - 1; x > d_upper; x--)
        board[x][m - 1] = board[x - 1][m - 1];

    // 청소기 행
    for (int y = m - 1; y > 1; y--)
        board[d_upper][y] = board[d_upper][y - 1];

    board[d_upper][1] = 0;

    // 청소기 위치 복구
    board[c_upper][0] = -1;
    board[d_upper][0] = -1;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m >> t;

    board.assign(n, vector<int>(m));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> board[i][j];

            if (board[i][j] == -1) {
                if (c_upper == 0)
                    c_upper = i;
                else
                    d_upper = i;
            }
        }
    }

    while (t--) {
        spread();
        clean();
    }

    int answer = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (board[i][j] > 0)
                answer += board[i][j];
        }
    }

    cout << answer;

    return 0;
}