#include <iostream>
using namespace std;

int n, score[4][100000] = {0, }, cnt[4][3001] = {0, }, ranking[4][3001] = {0, };

int main() {
    // Please write your code here.
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;

    // 0~2번은 각 대회 점수, 3번은 총점으로 사용
    for (int round = 0; round < 3; round++) {
        for (int i = 0; i < n; i++) {
            cin >> score[round][i];

            // 해당 대회의 점수별 인원 수 저장
            cnt[round][score[round][i]]++;

            // 총점 누적
            score[3][i] += score[round][i];
        }
    }

    // 총점도 점수별 인원 수 저장
    for (int i = 0; i < n; i++) {
        cnt[3][score[3][i]]++;
    }

    // 각 대회별 등수 + 총점 등수 계산
    for (int round = 0; round < 4; round++) {
        int bigger = 0; // 현재 점수보다 높은 점수를 받은 사람 수

        // 높은 점수부터 내려오면서 등수 계산
        for (int s = 3000; s >= 0; s--) {
            if (cnt[round][s] == 0) continue;

            // 등수 = 나보다 점수가 높은 사람 수 + 1
            ranking[round][s] = bigger + 1;

            // 다음 낮은 점수의 등수 계산에 반영
            bigger += cnt[round][s];
        }
    }

    for (int round = 0; round < 4; round++) {
        for (int i = 0; i < n; i++) {
            cout << ranking[round][score[round][i]] << " ";
        }
        cout << "\n";
    }

    return 0;
}