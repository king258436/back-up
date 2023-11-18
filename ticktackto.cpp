#include<iostream>
#include<string>

using namespace std;
bool o_flag;// 빙고 된거 있는지 알려주는 플레그
bool x_flag;

void isItBingo(string str) {
    for (int i = 0; i < 9; i += 3) {
        if (str[i] != '.' && str[i] == str[i + 1] && str[i] == str[i + 2]) {// 가로에 빙고 있는지 판별.
            if (str[i] == 'O') {
                o_flag = true;
            } else if (str[i] == 'X') {
                x_flag = true;
            }
        }
    }
    for (int i = 0; i < 3; i++) {// 세로에 빙고 있는 지 판별.
        if (str[i] != '.' && str[i] == str[i + 3] && str[i] == str[i + 6]) {
            if (str[i] == 'O') {
                o_flag = true;
            } else if (str[i] == 'X') {
                x_flag = true;
            }
        }
    }
    if (str[0] != '.' && str[0] == str[4] && str[0] == str[8]) {
        if (str[0] == 'O') {
            o_flag = true;
        } else if (str[0] == 'X') {
            x_flag = true;
        }
    }
    if (str[2] != '.' && str[2] == str[4] && str[2] == str[6]) {
        if (str[2] == 'O') {
            o_flag = true;
        } else if (str[2] == 'X') {
            x_flag = true;
        }
    }
}

int main() {
    string str;
    int o_cnt = 0, x_cnt = 0;// 갯수 카운트
    while (cin >> str) {
        if (str == "end") {// 종료조건
            break;
        }
        o_flag = false;
        x_flag = false;// 둘다 빙고 안나옴
        isItBingo(str);// 빙고 있는지 알려줌
        o_cnt = 0;
        x_cnt = 0;
        for (int i = 0; i < 9; i++) {
            if (str[i] == 'O') o_cnt++;
            if (str[i] == 'X') x_cnt++;
        }

        if (x_flag && !o_flag && x_cnt > o_cnt + 1) {// x승리
            cout << "valid" << '\n';
        } else if (!x_flag && o_flag && o_cnt == x_cnt) {//o 승리
            cout << "valid" << '\n';
        } else if (!x_flag && !o_flag && x_cnt == 5 && o_cnt == 4) {//비김
            cout << "valid" << '\n';
        } else {
            cout << "invalid" << '\n';
        }
    }
}
