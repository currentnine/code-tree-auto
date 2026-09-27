#include <iostream>
#include <deque>
using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    deque<int> chair[4];

    for (int i = 0; i < 4; i++) {
        string s;
        cin >> s;
        for (char c : s)
            chair[i].push_back(c - '0');
    }

    int k;
    cin >> k;

    while (k--) {
        int num, dir;
        cin >> num >> dir;
        num--;  // 0-based index

        int rotateDir[4] = {0};
        rotateDir[num] = dir;

        // 왼쪽으로 전파
        for (int i = num - 1; i >= 0; i--) {
            if (chair[i][2] != chair[i + 1][6])
                rotateDir[i] = -rotateDir[i + 1];
            else
                break;
        }

        // 오른쪽으로 전파
        for (int i = num + 1; i < 4; i++) {
            if (chair[i - 1][2] != chair[i][6])
                rotateDir[i] = -rotateDir[i - 1];
            else
                break;
        }

        // 실제 회전
        for (int i = 0; i < 4; i++) {
            if (rotateDir[i] == 1) { // 시계 방향
                chair[i].push_front(chair[i].back());
                chair[i].pop_back();
            }
            else if (rotateDir[i] == -1) { // 반시계 방향
                chair[i].push_back(chair[i].front());
                chair[i].pop_front();
            }
        }
    }

    int answer = 0;

    for (int i = 0; i < 4; i++) {
        if (chair[i][0] == 1)
            answer += (1 << i);  // 1, 2, 4, 8
    }

    cout << answer;

    return 0;
}