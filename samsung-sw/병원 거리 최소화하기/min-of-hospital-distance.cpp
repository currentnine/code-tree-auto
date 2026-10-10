#include <bits/stdc++.h>
using namespace std;

int n, m, answer = INT_MAX;
vector<pair<int, int>> people, hospital;
vector<int> selected; 

void dfs(int start) {
    // 병원 m개를 선택했다면 거리 계산
    if (selected.size() == m) {
        int sum = 0;

        // 각 사람마다 가장 가까운 병원 거리 계산
        for (auto [x, y] : people) {
            int dist = INT_MAX;

            for (int idx : selected) {
                auto [hx, hy] = hospital[idx];

                // 맨해튼 거리 계산
                dist = min(dist, abs(x - hx) + abs(y - hy));
            }

            sum += dist;
        }

        // 전체 병원 거리의 최솟값 갱신
        answer = min(answer, sum);
        return;
    }

    // 병원 m개를 선택하는 조합 탐색
    for (int i = start; i < hospital.size(); i++) {
        selected.push_back(i); // 병원 선택
        dfs(i + 1);           // 다음 병원 탐색
        selected.pop_back();  // 선택 취소
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;

    // 사람(1)과 병원(2)의 좌표 저장
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int x;
            cin >> x;

            if (x == 1) people.push_back({i, j});
            if (x == 2) hospital.push_back({i, j});
        }
    }

    dfs(0); // 병원 조합 탐색 시작

    cout << answer;
    return 0;
}
