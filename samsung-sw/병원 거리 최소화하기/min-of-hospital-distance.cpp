#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

int n, m;
int answer = INT_MAX;

vector<pair<int, int>> client;
vector<pair<int, int>> hospital;
vector<pair<int, int>> selected;

void backTrack(int start)
{
    if (selected.size() == m)
    {
        int totalDist = 0;

        for (int i = 0; i < client.size(); i++)
        {
            int minDist = INT_MAX;

            for (int j = 0; j < selected.size(); j++)
            {
                int dist =
                    abs(client[i].first - selected[j].first) +
                    abs(client[i].second - selected[j].second);

                minDist = min(minDist, dist);
            }

            totalDist += minDist;
        }

        answer = min(answer, totalDist);
        return;
    }

    for (int i = start; i < hospital.size(); i++)
    {
        selected.push_back(hospital[i]);
        backTrack(i + 1);
        selected.pop_back();
    }
}

int main()
{
    cin >> n >> m;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            int value;
            cin >> value;

            if (value == 1)
                client.push_back({ i, j });

            else if (value == 2)
                hospital.push_back({ i, j });
        }
    }

    backTrack(0);

    cout << answer;

    return 0;
}