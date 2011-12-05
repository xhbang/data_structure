
C++����: Codee#7234
//�Թ�����
//ջ&&����

#include<iostream>
using namespace std;
const size_t MaxSize = 100;

int mg[MaxSize][MaxSize];

struct{
    int i;
    int j;
    int d; //��һ�����ߵķ���
}St[MaxSize];
int top = -1;

void Mg(int xi,int yi,int xe,int ye)
{
    int i,j,d,find;
    top++;
    St[top].i = xi;
    St[top].j = yi;
    St[top].d = -1;
    mg[xi][yi] = -1;
    do{
        i = St[top].i;
        j = St[top].j;
        d = St[top].d;
        if( i == xe && j == ye) //�ҵ��˳���
        {
            cout << "����Թ�·�����£�" << endl;
            for(int i=0; i <= top; ++i)
            {
                cout << " (" << St[i].i << "," << St[i].j << ")";
                if((i+1)%5 == 0) cout << endl;
            }
            break;
        }
        find = 0;
        while(d <4 && find == 0)
        {
            d++;
            switch(d)
            {
            case 0:i = St[top].i-1; j = St[top].j; break;
            case 1:i = St[top].i; j = St[top].j+1; break;
            case 2:i = St[top].i+1; j = St[top].j; break;
            case 3:i = St[top].i; j = St[top].j-1; break;
            }
            if(mg[i][j]==0) find = 1;
        }
        if(find == 1)
        {
            St[top].d = d;
            top++;
            St[top].i = i;
            St[top].j = j;
            St[top].d = -1;
            mg[i][j] = -1;
        }
        else
        {
            mg[St[top].i][St[top].j] = 0;
            top--;
        }
    }while(top>-1);
    cout << "û�п���·��" << endl;
}

int main()
{
    int m,n,xi,yi,xe,ye;
    cout << "�������Թ���С�Լ�ģ�����:" <<endl;
    cin >> m >> n;
    for(int i=0;i<m;++i)
        for(int j=0;j<n;++j)
            cin >> mg[i][j];
    cout << "���λ�ã�";
    cin >> xi >> yi;
    cout << "����λ�ã�";
    cin >> xe >> ye;

    Mg(xi,yi,xe,ye);

    return 0;
}
