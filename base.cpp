#include <iostream>
#include <math.h>
#include <windows.h>
using namespace std;

int x[15];//x[k]：第k行上第x[k]个位置摆上了皇后
int N, cnt;//N为棋盘大小，cnt为解的个数

//row,col表示当前尝试摆放皇后的行号与列号
bool check(int row, int col) {
    //回溯，不会受到后面行的影响
    for (int i = 1; i < row; i++) {
        if (x[i] == col)//列冲突
            return false;
        if (abs(row - i) == abs(col - x[i]))//对角线冲突
            return false;
    }
    return true;
}
void queen() {
    //i表示第几册，j表示在第i层搜索位置
    int i = 1, j = 1;
    while (i <= N) {
        while (j <= N) {
            //如果当前位置合法
            if (check(i, j)) {
                //把x[i]暂时赋值成j
                x[i] = j;
                j = 1;
                break;
            }
            else
                j++;
        }
        //第i行没有找到可以放置皇后的位置
        if (x[i] == 0) {
            //如果回溯到了第0行，说明搜索结束
            if (i == 1)
                break;
            //回溯
            else {
                i--;
                j = x[i] + 1;//j为上一行的皇后位置+1
                x[i] = 0;//上一行清零
                continue;
            }
        }
        //如果找到了第N层，输出出来
        if (i == N) {
            cnt++;
            if (cnt <= 3) {
                for (int i = 1; i <= N; i++) {
                    cout << x[i] << " ";
                }
                cout << endl;
            }
            j = x[i] + 1;
            x[i] = 0;
            continue;
        }
        i++;
    }
}

void DFS(int k) {
    if (k == N + 1) {
        cnt++;
        if (cnt <= 3) {
            for (int i = 1; i <= N; i++) {
                cout << x[i] << " ";
            }
            cout << endl;
        }
        return;
    }
    for (int i = 1; i <= N; i++) {
        //如果当前位置合法
        if (check(k, i)) {
            x[k] = i;
            DFS(k + 1);
        }
    }
}

int main() {
    LARGE_INTEGER head, tail, freq;
    cin >> N;
    // similar to CLOCKS_PER_SEC
    QueryPerformanceFrequency(&freq);
    // start time
    QueryPerformanceCounter(&head);
    queen();
    //DFS(1);
    QueryPerformanceCounter(&tail);
    double timeOfSecond = (double)(tail.QuadPart - head.QuadPart) / (double)freq.QuadPart;
    double timeOfMicroSecond = (double)(tail.QuadPart - head.QuadPart) * 1e3 / (double)freq.QuadPart;
    cout << timeOfMicroSecond << endl;
    cout << cnt << endl;
}
