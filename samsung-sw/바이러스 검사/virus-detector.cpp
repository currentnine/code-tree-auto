#include <iostream>
#include <vector>

using namespace std;

int n, x, y;

int main() 
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    long long answer = 0;
    cin >> n;

    vector<int> v(n);

    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }

    cin >> x >> y;

    // 팀장 확인
    for (int i = 0; i < n; i++) {
        if (v[i] <= x) {
            answer++;
            v[i] = 0;
        }
        else {
            answer++;
            v[i] -= x;
        }
    }

    // 팀원 확인
    for (int i = 0; i < n; i++) {
        if (v[i] <= 0) continue;

        answer += v[i] / y;
        
        if (v[i] % y > 0) answer++;
    }

    cout << answer;

    return 0;
}