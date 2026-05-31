#include <iostream>
using namespace std;

int n, t, answer;
int timeArr[50], profit[50];

void DFS(int start, int sum)
{
    if (start + timeArr[start] > n)
    {
        if (start + timeArr[start] == n + 1) sum += profit[start];
        if (answer < sum) answer = sum;

        return;
    }

    for (int i = start + timeArr[start]; i <= n; i++) DFS(i, sum + profit[start]);
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    // Please write your code here.
    t = 1;

    for (int i = 1; i <= t; i++)
    {
        cin >> n;

        for (int i = 1; i <= n; i++)
        {
            cin >> timeArr[i] >> profit[i];
        }

        answer = 0;

        for (int i = 1; i <= n; i++)
        {
            DFS(i, 0);
        }

        cout << answer;
    }

    return 0;
}