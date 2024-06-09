#include <iostream>
#include <queue>
#include <windows.h>
using namespace std;

int n, limit, cnt;
int x[15], k = 1;
//行，左对角线，右对角线
void DFS(int row, int left, int right) {
    if (row != limit) {
        //row|left|right表示这一行的所有禁止位置，取反再和limit按位与，得到的是该行可以放的几个位置
        int pos = limit & ~(row | left | right);
        //每一个可以摆的位置，都要做一次
        while (pos) {
            //找到的可以放皇后的位置（pos二进制最右边的一个1）
            int p = pos & -pos;// pos & (~pos+1);
            //把这一位置0，表示不为空
            pos &= pos - 1;
            if (cnt < 3) {
                int t = p, num = 1;
                while (t != 1) {
                    num++;
                    t >>= 1;
                }
                x[k++] = num;
            }
            //把p所在row，left，right的位都置1。
            //(left | p)<< 1 是因为这一行由左对角线造成的禁止位在下一行要右移一下；right同理
            DFS(row | p, (left | p) << 1, (right | p) >> 1);
            if (cnt < 3) k--;
        }
    }
    else {
        if (cnt < 3) {
            for (int i = 1; i <= n; i++) {
                cout << x[i] << " ";
            }
            cout << endl;
        }
        cnt++;
    }
}
int main() {
    LARGE_INTEGER head, tail, freq;
    cin >> n;
    limit = (1 << n) - 1;
    // similar to CLOCKS_PER_SEC
    QueryPerformanceFrequency(&freq);
    // start time
    QueryPerformanceCounter(&head);
    DFS(0, 0, 0);
    QueryPerformanceCounter(&tail);
    double timeOfSecond = (double)(tail.QuadPart - head.QuadPart) / (double)freq.QuadPart;
    double timeOfMicroSecond = (double)(tail.QuadPart - head.QuadPart) * 1e3 / (double)freq.QuadPart;
    cout << timeOfMicroSecond << endl;
    cout << cnt << endl;
}
