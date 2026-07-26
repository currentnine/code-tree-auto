#include <iostream>

using namespace std;

int n, m;
int carRow, carCol, carDirection;
int road[55][55];

int rowDirection[4] = {-1, 0, 1, 0};
int colDirection[4] = {0, 1, 0, -1};

int driveCar()
{
    int visitedCount = 0;

    while (true)
    {
        // 현재 위치가 처음 방문한 도로라면 방문 처리한다.
        if (road[carRow][carCol] == 0)
        {
            road[carRow][carCol] = 2;
            visitedCount++;
        }

        bool moved = false;

        // 현재 방향을 기준으로 왼쪽 방향부터 차례대로 4방향을 확인한다.
        for (int count = 0; count < 4; count++)
        {
            // 왼쪽으로 회전한다.
            carDirection = (carDirection + 3) % 4;

            int nextRow = carRow + rowDirection[carDirection];
            int nextCol = carCol + colDirection[carDirection];

            // 왼쪽 방향이 한 번도 방문하지 않은 도로라면 한 칸 전진한다.
            if (road[nextRow][nextCol] == 0)
            {
                carRow = nextRow;
                carCol = nextCol;
                moved = true;
                break;
            }

            // 인도이거나 이미 방문한 도로라면
            // 다시 왼쪽으로 회전하여 다음 방향을 확인한다.
        }

        // 방문하지 않은 도로로 전진했다면 다시 1번 과정부터 진행한다.
        if (moved) continue;

        // 4방향 모두 전진할 수 없다면 현재 방향을 유지한 채 한 칸 후진
        int backRow = carRow - rowDirection[carDirection];
        int backCol = carCol - colDirection[carDirection];

        // 뒤쪽 공간이 인도라서 후진할 수 없다면 작동을 멈춤
        if (road[backRow][backCol] == 1) break;

        // 뒤쪽이 도로라면 방문 여부와 관계없이 한 칸 후진
        carRow = backRow;
        carCol = backCol;
    }

    return visitedCount;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m;
    cin >> carRow >> carCol >> carDirection;

    for (int row = 0; row < n; row++)
    {
        for (int col = 0; col < m; col++)
        {
            cin >> road[row][col];
        }
    }

    cout << driveCar();

    return 0;
}