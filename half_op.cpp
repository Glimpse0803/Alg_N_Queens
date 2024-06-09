#include <iostream>
#include <vector>
#include <math.h>
#include <windows.h>
using namespace std;

int x[15];
vector<int> v[3];//处理解数量不足3个的情况
int N, cnt;
int flag, oddCnt;

bool check(int row, int col) {
    //回溯，不会受到后面行的影响
    for (int i = 1; i < row; i++) {
        if (x[i] == col)return false;
        if (abs(row - i) == abs(col - x[i]))return false;
    }
    return true;
}
void DFS(int k) {
    if (k == N + 1) {
        if (flag && x[1] == (N + 1) / 2) {
            oddCnt++;
            if (oddCnt % 2 == 0)cnt++;
        }
        else
            cnt++;
        if (cnt <= 3) {
            for (int i = 1; i <= N; i++) {
                cout << x[i] << " ";
                v[cnt - 1].push_back(x[i]);
            }
            cout << endl;
        }
        return;
    }
    int len = (k == 1) ? (N + flag) / 2 : N;
    for (int i = 1; i <= len; i++) {
        if (check(k, i)) {
            x[k] = i;
            DFS(k + 1);
        }
    }
}

int main() {
    LARGE_INTEGER head, tail, freq;
    cin >> N;
    if (N & 1)flag = 1;
    // similar to CLOCKS_PER_SEC
    QueryPerformanceFrequency(&freq);
    // start time
    QueryPerformanceCounter(&head);
    DFS(1);
    for (int i = cnt, j = cnt - 1; i < 3 && j >= 0; i++, j--) {
        for (int k = N - 1; k >= 0; k--) {
            cout << v[j][k] << " ";
        }
        cout << endl;
    }
    QueryPerformanceCounter(&tail);
    double timeOfSecond = (double)(tail.QuadPart - head.QuadPart) / (double)freq.QuadPart;
    double timeOfMicroSecond = (double)(tail.QuadPart - head.QuadPart) * 1e3 / (double)freq.QuadPart;
    cout << timeOfMicroSecond << endl;
    cout << cnt << endl;
    cout << cnt * 2 << endl;
}
