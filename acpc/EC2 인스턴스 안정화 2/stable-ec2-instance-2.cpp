#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>

using namespace std;

int n;
const long long ee = -4e18;

vector<vector<long long>> dp(3, vector<long long>(2, ee));

int main() {
    // Please write your code here.

    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n;

    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    dp[0][0] = 0;
    dp[1][1] = 0;

    for (int i = 0; i < n - 1; i++) {
        vector<vector<long long>> ndp(3, vector<long long>(2, ee));

        for (int cnt = 0; cnt <= 2; cnt++) {
            for (int cur = 0; cur <= 1; cur++) {
                if (dp[cnt][cur] == ee) continue;

                long long x = a[i] * (cur ? 2 : 1);

                for (int nxt = 0; nxt <= 1; nxt++) {
                    int ncnt = cnt + nxt;
                    if (ncnt > 2) continue;
                    
                    // 현재 위치와 다음 위치를 각각 2배로 할지 모든 조합을 확인
                    long long y = a[i + 1] * (nxt ? 2 : 1);
                    long long diff = llabs(x - y);

                    // 현재 위치 cur, 다음 위치 nxt 상태의 인접 차이를 더해 최대 점수 갱신
                    // ncnt는 다음 위치까지 2배로 만든 총 개수
                    ndp[ncnt][nxt] = max(ndp[ncnt][nxt], dp[cnt][cur] + diff);
                }
            }
        }

        dp = ndp;
    }

    cout << max(dp[2][0], dp[2][1]);

    return 0;
}