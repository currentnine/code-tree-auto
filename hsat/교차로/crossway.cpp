#include <iostream>
#include <queue>
#include <vector>
using namespace std;

#define X first   
#define Y second 

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    // Please write your code here.
    int n;
    cin >> n;

    // 방향별 큐
    // q[0] = A
    // q[1] = B
    // q[2] = C
    // q[3] = D
    queue<pair<int, int>> q[4];
    vector<int> ans(n, -1);

    for (int i = 0; i < n; i++) {
        int t;
        char w;

        cin >> t >> w;

        int dir = w - 'A';

        // {도착시간, 입력순서}
        q[dir].push({t, i});
    }

    int cur = 0;

    while (true) {

        bool empty = true;

        // 가장 빠른 다음 차량 시간
        int nextTime = 1e9;

        // 큐가 비었는지 확인
        for (int i = 0; i < 4; i++) {
            if (!q[i].empty()) {
                empty = false;

                // 다음 차량 도착 시간 갱신
                nextTime = min(nextTime, q[i].front().X);
            }
        }

        // 전부 비었으면 종료
        if (empty) break;

        bool exist[4] = {0}, go[4] = {0}, anyExist = false;

        // 현재 시간(cur)에 교차로에 존재하는 차량 체크
        for (int i = 0; i < 4; i++) {
            if (!q[i].empty() && q[i].front().X <= cur) {
                exist[i] = true;
                anyExist = true;
            }
        }

        // 현재 시간에 차량이 하나도 없다면
        // 다음 차량 시간으로 점프
        if (!anyExist) {
            cur = nextTime;
            continue;
        }

        int cntCanGo = 0;

        // 오른쪽 차량이 없으면 통과 가능
        for (int i = 0; i < 4; i++) {
            int right = (i + 3) % 4;

            // 현재 차 존재 + 오른쪽 차 없음
            if (exist[i] && !exist[right]) {
                go[i] = true;
                cntCanGo++;
            }
        }
        // 아무도 못 가면 교착 상태
        if (cntCanGo == 0) break;

        // 통과 처리
        for (int i = 0; i < 4; i++) {
            if (go[i]) {
                int idx = q[i].front().Y;
                // 현재 시간에 통과
                ans[idx] = cur;

                q[i].pop();
            }
        }
        cur++;
    }

    for (int i = 0; i < n; i++) cout << ans[i] << "\n";

    return 0;
}