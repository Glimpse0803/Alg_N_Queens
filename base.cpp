#include <iostream>
#include <math.h>
#include <windows.h>
using namespace std;

int x[15];//x[k]����k���ϵ�x[k]��λ�ð����˻ʺ�
int N, cnt;//NΪ���̴�С��cntΪ��ĸ���

//row,col��ʾ��ǰ���԰ڷŻʺ���к����к�
bool check(int row, int col) {
    //���ݣ������ܵ������е�Ӱ��
    for (int i = 1; i < row; i++) {
        if (x[i] == col)//�г�ͻ
            return false;
        if (abs(row - i) == abs(col - x[i]))//�Խ��߳�ͻ
            return false;
    }
    return true;
}
void queen() {
    //i��ʾ�ڼ��ᣬj��ʾ�ڵ�i������λ��
    int i = 1, j = 1;
    while (i <= N) {
        while (j <= N) {
            //�����ǰλ�úϷ�
            if (check(i, j)) {
                //��x[i]��ʱ��ֵ��j
                x[i] = j;
                j = 1;
                break;
            }
            else
                j++;
        }
        //��i��û���ҵ����Է��ûʺ��λ��
        if (x[i] == 0) {
            //������ݵ��˵�0�У�˵����������
            if (i == 1)
                break;
            //����
            else {
                i--;
                j = x[i] + 1;//jΪ��һ�еĻʺ�λ��+1
                x[i] = 0;//��һ������
                continue;
            }
        }
        //����ҵ��˵�N�㣬�������
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
        //�����ǰλ�úϷ�
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
