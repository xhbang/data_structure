
C++语言: Codee#7234
//迷宫问题
//栈&&回溯

#include<iostream>
using namespace std;
const size_t MaxSize = 100;

int mg[MaxSize][MaxSize];

struct{
    int i;
    int j;
    int d; //下一步可走的方向
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
        if( i == xe && j == ye) //找到了出口
        {
            cout << "解得迷宫路径如下：" << endl;
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
    cout << "没有可走路径" << endl;
}

int main()
{
    int m,n,xi,yi,xe,ye;
    cout << "请输入迷宫大小以及模拟矩阵:" <<endl;
    cin >> m >> n;
    for(int i=0;i<m;++i)
        for(int j=0;j<n;++j)
            cin >> mg[i][j];
    cout << "入口位置：";
    cin >> xi >> yi;
    cout << "出口位置：";
    cin >> xe >> ye;

    Mg(xi,yi,xe,ye);

    return 0;
}
