#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;


#define MAX 25

int n, half_n;
int board[MAX][MAX];
bool selected[MAX];
int answer = 0x7fffffff;

int calc()
{
    int sum_a = 0;
    int sum_b = 0;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            // i와 j가 모두 선택된 팀이면 A팀 능력치에 더함
            if (selected[i] && selected[j])
                sum_a += board[i][j];

            // i와 j가 모두 선택되지 않은 팀이면 B팀 능력치에 더함
            else if (!selected[i] && !selected[j])
                sum_b += board[i][j];
        }
    }

    // 두 팀 능력치 차이의 절댓값 반환
    return abs(sum_a - sum_b);
}

void dfs(int cnt, int start)
{
    if (cnt == half_n)
    {
        // 현재 팀 구성에서 능력치 차이를 계산하고 최솟값 갱신
        answer = min(answer, calc());
        return;
    }

    // start부터 사람을 하나씩 선택하며 조합 생성
    for (int i = start; i < n; i++)
    {
        // i번 사람을 A팀으로 선택
        selected[i] = true;

        // 다음 사람부터 이어서 선택
        dfs(cnt + 1, i + 1);

        selected[i] = false;
    }
}


int main() {
    // Please write your code here.

    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n;

    half_n = n / 2;

    for (int r = 0; r < n; r++)
    {
        for (int c = 0; c < n; c++)
        {
            cin >> board[r][c];
        }
    }

    // A팀과 B팀은 서로 바뀌어도 능력치 차이가 같음
    // 따라서 0번 사람을 A팀에 고정해서 중복 조합을 절반으로 줄임
    selected[0] = true;
    dfs(1, 1);

    cout << answer;

    return 0;
}
