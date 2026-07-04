#include <iostream>
#include <vector>

using namespace std;

int n, m;
int board[5][5];
bool visited[5][5];

vector<pair<int, int>> targets;
int answer = 0;

int dr[4] = {0, 1, 0, -1};
int dc[4] = {1, 0, -1, 0};

bool isInRange(int row, int col) {
    return row >= 0 && row < n && col >= 0 && col < n;
}

// 아직 순서가 아닌 다음 목적지들을 먼저 밟는 경우는 무효
bool isFutureTarget(int row, int col, int targetIdx) {
    for (int i = targetIdx + 1; i < m; i++) {
        if (targets[i].first == row && targets[i].second == col) {
            return true;
        }
    }
    return false;
}

void dfs(int row, int col, int targetIdx) {
    // 모든 목적지를 순서대로 방문한 경우
    if (targetIdx == m) {
        answer++;
        return;
    }

    for (int dir = 0; dir < 4; dir++) {
        int nextRow = row + dr[dir];
        int nextCol = col + dc[dir];

        if (!isInRange(nextRow, nextCol)) continue;
        if (board[nextRow][nextCol] == 1) continue;
        if (visited[nextRow][nextCol]) continue;

        // 다음 목적지가 아닌 미래 목적지를 먼저 밟으면 순서 위반
        if (isFutureTarget(nextRow, nextCol, targetIdx)) continue;

        visited[nextRow][nextCol] = true;

        // 이번에 이동한 칸이 현재 목표 지점이면 다음 목표로 넘어감
        if (nextRow == targets[targetIdx].first &&
            nextCol == targets[targetIdx].second) {
            dfs(nextRow, nextCol, targetIdx + 1);
        } else {
            dfs(nextRow, nextCol, targetIdx);
        }

        visited[nextRow][nextCol] = false;
    }
}

int main() {
    // Please write your code here.
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;

    for (int row = 0; row < n; row++) {
        for (int col = 0; col < n; col++) {
            cin >> board[row][col];
        }
    }

    targets.resize(m);

    for (int i = 0; i < m; i++) {
        int row, col;
        cin >> row >> col;

        // 입력은 1-indexed, 내부 계산은 0-indexed
        targets[i] = {row - 1, col - 1};
    }

    int startRow = targets[0].first;
    int startCol = targets[0].second;

    visited[startRow][startCol] = true;

    // 첫 번째 목적지는 시작점이므로, 두 번째 목적지부터 찾기 시작
    dfs(startRow, startCol, 1);

    cout << answer << '\n';

    return 0;
}