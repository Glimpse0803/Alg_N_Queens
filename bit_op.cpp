#include <iostream>
#include <queue>
#include <windows.h>
using namespace std;

int n, limit, cnt;
int x[15], k = 1;
//�У���Խ��ߣ��ҶԽ���
void DFS(int row, int left, int right) {
    if (row != limit) {
        //row|left|right��ʾ��һ�е����н�ֹλ�ã�ȡ���ٺ�limit��λ�룬�õ����Ǹ��п��Էŵļ���λ��
        int pos = limit & ~(row | left | right);
        //ÿһ�����԰ڵ�λ�ã���Ҫ��һ��
        while (pos) {
            //�ҵ��Ŀ��ԷŻʺ��λ�ã�pos���������ұߵ�һ��1��
            int p = pos & -pos;// pos & (~pos+1);
            //����һλ��0����ʾ��Ϊ��
            pos &= pos - 1;
            if (cnt < 3) {
                int t = p, num = 1;
                while (t != 1) {
                    num++;
                    t >>= 1;
                }
                x[k++] = num;
            }
            //��p����row��left��right��λ����1��
            //(left | p)<< 1 ����Ϊ��һ������Խ�����ɵĽ�ֹλ����һ��Ҫ����һ�£�rightͬ��
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
