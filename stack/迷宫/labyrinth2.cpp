#include <iostream>
#include <stack>
#include <list>
#include <assert.h>
#include <fstream>

using namespace std;

struct Position{  //����λ�ýṹ��
	int r;
	int c;
};

bool FindPath(Position start,Position end,stack<Position>& pos,int **maze)
{
	Position current = start;

	//����̽Ѱ���ĸ�����
	Position offset[4];
	offset[0].r=-1; offset[0].c=0;   //up
	offset[1].r=0;  offset[1].c=1;   //right
	offset[2].r=1;  offset[2].c=0;   //down
	offset[3].r=0;  offset[3].c=-1;  //left

	int di=0;
	int lastDi=3;
	int row,col;

	while(current.c!=end.c || current.r!=end.r)//û���ҵ�����
	{
		while(di<=lastDi)   //�ӵ�ǰλ�ð�˳ʱ��˳��̽Ѱ
		{
			row = current.r+offset[di].r;
			col = current.c+offset[di].c;
			if (maze[row][col] == 0)//��һ��λ�ÿ���
			{
				break;
			}
			di++;
		}
		//find a througth path
		if (di <= lastDi)//�ҵ���һ�����е�λ��
		{
			pos.push(current);//����ǰλ����ջ
			current.r = row;
			current.c = col;
			maze[row][col] = 1;//��ǵ�ǰλ��Ϊ����ͨ��������������ѭ��
			di = 0;
		}
		else//û���ҵ����ڵ�ͨ����·
		{
			if (pos.empty())//û���ҵ�ͨ·
			{
				return false;
			}
			Position next;
			next= pos.top();
			pos.pop();
			if (next.c = current.c)//ȡ�õ�ǰӦ̽Ѱ�ķ���
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
			current = next;//��ǵ�ǰλ��Ϊջ��λ��
		}

	}
	pos.push(end);//��������ջ

	return true;
}

int main()
{
	ifstream in("maze.dat");//�����Թ��ļ�
	assert(in);    

	int row,col;
	int i,j;

	in>>row>>col;//�����Թ����к���

	//�����Թ����飬�Թ����ܼ�ǽ����ʹ�Թ��߽����ڲ��ڵ�ͬ�ȴ���
	int **maze=new int*[row+2];
	for (i=0; i<row+2; i++)
	{
		maze[i] =new int[col+2];
	}

	for (i=0;i<row+2;i++)//�Թ�����Ϊǽ������Ϊ����ͨ��
	{
		maze[i][0] = maze[i][col+1] = 1;
	}
	for (j=0;j<col+2;j++)
	{
		maze[0][j] = maze[row+1][j] = 1;
	}

	Position start,end;
	in>>i>>j;   //�������λ��
	start.r=i; start.c=j;
	in>>i>>j;   //�������λ��
	end.r=i; end.c=j;

	//�����Թ�����
	for (i=1;i<row+1;i++)
	{
		for (j=1;j<col+1;j++)
		{
			in>>maze[i][j];
		}
	}

	stack<Position> path;
	list<Position> show;
	if (FindPath(start,end,path,maze))//�ҵ�һ��·��
	{
		while (!path.empty())
		{
			show.push_front(path.top());//·����ջ
			path.pop();
		}

		list<Position>::iterator it=show.begin();
		for (; it!=show.end(); it++)//��ʾ·��
		{
			cout<<"("<<(*it).r<<" , "<<(*it).c<<")"<<endl;
		}
	}
	else//û���ҵ�·��
	{
		cout<<"Not find any correct path!"<<endl;
	}

	for (i=0; i<row+2; i++)//�ͷ��ڴ�ռ�
	{
		delete []maze[i];
	}
	delete []maze;

	return 0;
}