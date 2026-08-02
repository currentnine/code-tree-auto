#include <iostream>
using namespace std;

int n, m;                
int board[20][20], order[400], like[401][4];        
int dr[4] = {-1, 1, 0, 0};
int dc[4] = {0, 0, -1, 1};

// (r,c) 주변에 s가 좋아하는 친구 수(f)와 빈칸 수(e)를 카운트
void count(int r, int c, int s, int &f, int &e) {
    f = 0; e = 0;
    for (int d = 0; d < 4; d++) {
        int nr = r + dr[d], nc = c + dc[d];
        if (nr < 0 || nr >= n || nc < 0 || nc >= n) continue;
        if (board[nr][nc] == 0) e++;
        else for (int k = 0; k < 4; k++)
            if (like[s][k] == board[nr][nc]) f++;
    }
}

int main() {
    cin.sync_with_stdio(0); cin.tie(0);

    cin >> n;
    m = n * n;
    for (int i = 0; i < m; i++) {
        cin >> order[i];
        for (int k = 0; k < 4; k++) cin >> like[order[i]][k];
    }

    // 한 명씩 앉히기
    for (int i = 0; i < m; i++) {
        int s = order[i];
        int bf = -1, be = -1, br = 0, bc = 0;   // best 친구수, 빈칸수, 행, 열

        for (int r = 0; r < n; r++)
            for (int c = 0; c < n; c++) {
                if (board[r][c] != 0) continue;
                int f, e;
                count(r, c, s, f, e);
                // 위에서부터 왼쪽부터 보므로, 동점이면 그냥 넘어감
                if (f > bf || (f == bf && e > be)) {
                    bf = f; be = e; br = r; bc = c;
                }
            }

        board[br][bc] = s;
    }

    // 점수 계산
    int answer = 0;
    for (int r = 0; r < n; r++)
        for (int c = 0; c < n; c++) {
            int f, e;
            count(r, c, board[r][c], f, e);
            if (f == 1) answer += 1;
            else if (f == 2) answer += 10;
            else if (f == 3) answer += 100;
            else if (f == 4) answer += 1000;
        }

    cout << answer;
    return 0;
}