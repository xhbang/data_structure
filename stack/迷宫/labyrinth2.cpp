#include <iostream>
#include <stack>
#include <list>
#include <assert.h>
#include <fstream>

using namespace std;

struct Position{  //定义位置结构体
	int r;
	int c;
};

bool FindPath(Position start,Position end,stack<Position>& pos,int **maze)
{
	Position current = start;

	//定义探寻的四个方向
	Position offset[4];
	offset[0].r=-1; offset[0].c=0;   //up
	offset[1].r=0;  offset[1].c=1;   //right
	offset[2].r=1;  offset[2].c=0;   //down
	offset[3].r=0;  offset[3].c=-1;  //left

	int di=0;
	int lastDi=3;
	int row,col;

	while(current.c!=end.c || current.r!=end.r)//没有找到出口
	{
		while(di<=lastDi)   //从当前位置按顺时针顺序探寻
		{
			row = current.r+offset[di].r;
			col = current.c+offset[di].c;
			if (maze[row][col] == 0)//下一个位置可行
			{
				break;
			}
			di++;
		}
		//find a througth path
		if (di <= lastDi)//找到下一个可行的位置
		{
			pos.push(current);//将当前位置入栈
			current.r = row;
			current.c = col;
			maze[row][col] = 1;//标记当前位置为不可通过，以免陷入死循环
			di = 0;
		}
		else//没有找到相邻的通行线路
		{
			if (pos.empty())//没有找到通路
			{
				return false;
			}
			Position next;
			next= pos.top();
			pos.pop();
			if (next.c = current.c)//取得当前应探寻的方向
			{
				if ( next.r>current.r )
				{
					di = 1;
				}
				else
					di = 3;
			}
			else if (next.r = current.r)
			{
				di = 3 + next.c-current.c;
			}
			current = next;//标记当前位置为栈顶位置
		}

	}
	pos.push(end);//将出口入栈

	return true;
}

int main()
{
	ifstream in("maze.dat");//定义迷宫文件
	assert(in);    

	int row,col;
	int i,j;

	in>>row>>col;//读入迷宫的行和列

	//定义迷宫数组，迷宫四周加墙，以使迷宫边界与内部节点同等处理
	int **maze=new int*[row+2];
	for (i=0; i<row+2; i++)
	{
		maze[i] =new int[col+2];
	}

	for (i=0;i<row+2;i++)//迷宫四周为墙，设置为不可通过
	{
		maze[i][0] = maze[i][col+1] = 1;
	}
	for (j=0;j<col+2;j++)
	{
		maze[0][j] = maze[row+1][j] = 1;
	}

	Position start,end;
	in>>i>>j;   //读入入口位置
	start.r=i; start.c=j;
	in>>i>>j;   //读入出口位置
	end.r=i; end.c=j;

	//读入迷宫数据
	for (i=1;i<row+1;i++)
	{
		for (j=1;j<col+1;j++)
		{
			in>>maze[i][j];
		}
	}

	stack<Position> path;
	list<Position> show;
	if (FindPath(start,end,path,maze))//找到一条路径
	{
		while (!path.empty())
		{
			show.push_front(path.top());//路径出栈
			path.pop();
		}

		list<Position>::iterator it=show.begin();
		for (; it!=show.end(); it++)//显示路径
		{
			cout<<"("<<(*it).r<<" , "<<(*it).c<<")"<<endl;
		}
	}
	else//没有找到路径
	{
		cout<<"Not find any correct path!"<<endl;
	}

	for (i=0; i<row+2; i++)//释放内存空间
	{
		delete []maze[i];
	}
	delete []maze;

	return 0;
}