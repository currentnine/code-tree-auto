#include <iostream>
#include <deque>
#include <algorithm>

using namespace std;

int n, k;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> k;

    deque<int> a(2 * n);
    deque<int> p(2 * n, 0);

    for (int &x : a) cin >> x;

    int turn = 0;

    while (true) {
        turn++;

        // 1. 무빙워크 회전
        a.push_front(a.back());
        a.pop_back();

        p.push_front(p.back());
        p.pop_back();

        p[n - 1] = 0; // n번 칸 도착하면 내림

        // 2. 사람 이동
        for (int i = n - 2; i >= 0; i--) {
            if (p[i] && !p[i + 1] && a[i + 1] > 0) {
                p[i] = 0;
                p[i + 1] = 1;
                a[i + 1]--;
            }
        }

        p[n - 1] = 0; // 이동해서 n번 칸 도착한 사람 내림

        // 3. 1번 칸에 사람 올리기
        if (!p[0] && a[0] > 0) {
            p[0] = 1;
            a[0]--;
        }

        // 4. 안정성 0인 칸이 k개 이상이면 종료
        if (count(a.begin(), a.end(), 0) >= k)
            break;
    }

    cout << turn;
}