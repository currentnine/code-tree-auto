#include <iostream>
#include <string>
#include <vector>
using namespace std;

char table[5][5];
int rowPos[26];
int colPos[26];
bool used[26];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    // Please write your code here.

    string message, key;
    cin >> message >> key;

    // J는 I로 치환
    for (char& c : message) {
        if (c == 'J') c = 'I';
    }

    for (char& c : key) {
        if (c == 'J') c = 'I';
    }

    // 1. 5x5 키 테이블 생성
    int idx = 0;

    for (char c : key) {
        int num = c - 'A';

        if (used[num]) continue;

        used[num] = true;
        table[idx / 5][idx % 5] = c;
        idx++;
    }

    used['J' - 'A'] = true;

    for (char c = 'A'; c <= 'Z'; c++) {
        int num = c - 'A';

        if (used[num]) continue;

        used[num] = true;
        table[idx / 5][idx % 5] = c;
        idx++;
    }

    // 2. 각 알파벳 위치 저장
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            int num = table[i][j] - 'A';
            rowPos[num] = i;
            colPos[num] = j;
        }
    }

    // 3. 메시지 두 글자씩 나누기 위한 전처리
    string plain = "";

    for (char c : message) {
        if (plain.size() % 2 == 1 && plain.back() == c) {
            if (c == 'X') plain += 'Q';
            else plain += 'X';
        }

        plain += c;
    }

    if (plain.size() % 2 == 1) {
        plain += 'X';
    }

    // 4. Playfair 암호화
    string result = "";

    for (int i = 0; i < plain.size(); i += 2) {
        char a = plain[i];
        char b = plain[i + 1];

        int ax = rowPos[a - 'A'];
        int ay = colPos[a - 'A'];
        int bx = rowPos[b - 'A'];
        int by = colPos[b - 'A'];

        if (ax == bx) {
            // 같은 행: 오른쪽 문자
            result += table[ax][(ay + 1) % 5];
            result += table[bx][(by + 1) % 5];
        }
        else if (ay == by) {
            // 같은 열: 아래 문자
            result += table[(ax + 1) % 5][ay];
            result += table[(bx + 1) % 5][by];
        }
        else {
            // 직사각형: 같은 행, 상대 열
            result += table[ax][by];
            result += table[bx][ay];
        }
    }

    cout << result;

    return 0;
}