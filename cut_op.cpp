#include <iostream>
#include <windows.h>
using namespace std;

int N, cnt, a[15];
//��б�ߡ���б�ߡ���
bool x1[31], x2[31], y[15];

void DFS(int k) {
    if (k == N + 1) {
        cnt++;
        if (cnt <= 3) {
            for (int i = 1; i <= N; i++) {
                cout << a[i] << " ";
            }
            cout << endl;
        }
        return;
    }
    for (int i = 1; i <= N; i++) {
        //����x2�±겻����abs(k-i)�������ǲ��Եģ���Ϊ���Խ��߱��ϵ������Խ��ߣ����ǵ�abs(k-i)����1
        if (!x1[i + k] && !x2[k - i + N] && !y[i]) {
            a[k] = i;
            x1[i + k] = true;
            x2[k - i + N] = true;
            y[i] = true;
            DFS(k + 1);
            x1[i + k] = false;
            x2[k - i + N] = false;
            y[i] = false;
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
    DFS(1);
    QueryPerformanceCounter(&tail);
    double timeOfSecond = (double)(tail.QuadPart - head.QuadPart) / (double)freq.QuadPart;
    double timeOfMicroSecond = (double)(tail.QuadPart - head.QuadPart) * 1e3 / (double)freq.QuadPart;
    cout << timeOfMicroSecond << endl;
    cout << cnt << endl;
}
