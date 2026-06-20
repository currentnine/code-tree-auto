#include <iostream>
#include <vector>

using namespace std;
int n;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    // Please write your code here.

    cin >> n;

    vector<int> arr(n);

    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    unsigned long long answer = 0;

    // left와 right 사이에서 arr[left]보다 큰 값의 개수
    vector<vector<int>> bigger_than_left(n, vector<int>(n, 0));

    for (int left = 0; left < n - 2; left++) {
        int count = 0;

        for (int mid = left + 1; mid < n - 1; mid++) {
            if (arr[left] < arr[mid]) {
                count++;
            }

            // left부터 mid까지 봤을 때,
            // arr[left]보다 큰 값이 몇 개 있었는지 저장
            bigger_than_left[left][mid] = count;
        }
    }

    for (int left = 0; left < n - 2; left++) {
        for (int right = left + 2; right < n; right++) {

            // arr[left] > arr[right]인 경우만 확인
            if (arr[left] > arr[right]) {

                // left와 right 사이에 있는 mid 중에서
                // arr[mid] > arr[left]인 개수를 더한다.
                //
                // 즉, arr[mid] > arr[left] > arr[right] 형태의
                // (left, mid, right) 조합 개수를 세는 것
                answer += bigger_than_left[left][right - 1];
            }
        }
    }

    cout << answer;

    return 0;
}