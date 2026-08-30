#include <bits/stdc++.h>
using namespace std;

int n, m, k;
const int INF = 1e9;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m >> k;

    vector<vector<int>> graph(n + 1);
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        graph[a].push_back(b);
    }

    vector<int> people(k);
    for (int i = 0; i < k; i++) cin >> people[i];


    vector<vector<int>> dist(k, vector<int>(n + 1, INF));

    // 각 사람의 출발 도시를 기준으로 BFS를 돌려 모든 노드까지의 최단거리를 구함
    for (int i = 0; i < k; i++) {
        int s = people[i];
        dist[i][s] = 0;
        queue<int> q;
        q.push(s);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int v : graph[u]) {
                if (dist[i][v] == INF) {
                    dist[i][v] = dist[i][u] + 1;
                    q.push(v);
                }
            }
        }
    }

    // 각 후보 노드 v에 대해 k명의 최댓값(가장 오래 걸리는 사람)을 구하고, 그 중 최솟값을 찾음
    int ans = INF;
    for (int v = 1; v <= n; v++) {
        int cur = 0;
        bool ok = true;
        for (int i = 0; i < k; i++) {
            if (dist[i][v] == INF) {
                ok = false;
                break;
            }
            cur = max(cur, dist[i][v]);
        }
        if (ok) ans = min(ans, cur);
    }

    cout << (ans != INF ? ans : -1) << "\n";

    return 0;
}