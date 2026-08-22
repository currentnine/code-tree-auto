#include <iostream>
#include <algorithm>
using namespace std;

int n, m;
int board[505][505];
bool visited[505][505];

int answer = 0;

int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

// 현재까지 선택한 칸 수 = depth
void dfs(int x, int y, int depth, int sum) {
    if (depth == 4) {
        answer = max(answer, sum);
        return;
    }

    for (int d = 0; d < 4; d++) {
        int nx = x + dx[d];
        int ny = y + dy[d];

        if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;

        if (visited[nx][ny]) continue;

        visited[nx][ny] = true;
        dfs(nx, ny, depth + 1, sum + board[nx][ny]);
        visited[nx][ny] = false;
    }
}

// T 모양(ㅗ, ㅜ, ㅏ, ㅓ) 검사
void checkT(int x, int y) {
    // ㅜ
    if (y - 1 >= 0 && y + 1 < m && x + 1 < n) {
        int sum = board[x][y]
                + board[x][y - 1]
                + board[x][y + 1]
                + board[x + 1][y];

        answer = max(answer, sum);
    }

    // ㅗ
    if (y - 1 >= 0 && y + 1 < m && x - 1 >= 0) {
        int sum = board[x][y]
                + board[x][y - 1]
                + board[x][y + 1]
                + board[x - 1][y];

        answer = max(answer, sum);
    }

    // ㅏ
    if (x - 1 >= 0 && x + 1 < n && y + 1 < m) {
        int sum = board[x][y]
                + board[x - 1][y]
                + board[x + 1][y]
                + board[x][y + 1];

        answer = max(answer, sum);
    }

    // ㅓ
    if (x - 1 >= 0 && x + 1 < n && y - 1 >= 0) {
        int sum = board[x][y]
                + board[x - 1][y]
                + board[x + 1][y]
                + board[x][y - 1];

        answer = max(answer, sum);
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m;

    for (int i = 0; i < n; i++) 
        for (int j = 0; j < m; j++) cin >> board[i][j];

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            // DFS
            visited[i][j] = true;
            dfs(i, j, 1, board[i][j]);
            visited[i][j] = false;

            // T 블럭
            checkT(i, j);
        }
    }

    cout << answer;

    return 0;
}