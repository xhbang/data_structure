#include <stdio.h>

typedef char data;
const int maxSize=20;		//最大值
//int matrix[maxSize][maxSize];
typedef enum{DG,DN,UDG,UDN} Kind;		//种类，初始化第一步
bool visited[maxSize];
typedef struct mgraph{
	data myvec[maxSize];
	int my[maxSize][maxSize];
	int vecnum,arcnum;
	Kind kind;
}mgraph;


void createDG(mgraph &my){
	int x=0,y=0;
	printf("input the number of vec and arc\n");
	scanf("%d%d",&my.vecnum,&my.arcnum);
	for(int i=0;i<my.vecnum;i++)
		for(int j=0;j<my.vecnum;j++)
			my.my[i][j]=0;			//初始化为0
	printf("please input the data \n");
	for(i=0;i<my.vecnum;i++)
		scanf("%c",&my.myvec[i]);
	for(i=0;i<my.arcnum;i++){
		printf("please input v1 and v2 to locate in the grapg\n");
		scanf("%d%d",&x,&y);
		my.my[x-1][y-1]=1;
	}
}
/*
void create(mgraph &my){
	printf("please input the kind of graph\n");
	scanf("%d",&my.kind);
	switch(my.kind){
	case DG:
		createDG(my);
		break;
		//		case UDG:				//先只写了一种
	default:
		printf("ERROR\n");
		break;
	}
}
*/

int First(mgraph G,int v){
	for(int i=0;i<G.vecnum;i++)
		if(G.my[v][i]==1)
			return i;
		return -1;
}

int Next(mgraph G,int v,int w){
	for(int i=w+1;i<G.vecnum;i++)
		if(G.my[v][i]==1)
			return i;
		return -1;
}

void DFS(mgraph G,int v){
	visited[v]=true;
	printf("the data:%c",G.myvec[v]);		//遇到难题，怎么去判断邻接节点
	for(int i=First(G,v);i>=0;i=Next(G,v,i))
		if(!visited[i])
			DFS(G,i);
}
void Travel(mgraph G){
	for(int i=0;i<G.vecnum;i++)
		visited[i]=false;				//初始化
	for(i=0;i<G.vecnum;i++)
		if(!visited[i])
			DFS(G,i);
}


int Locate(mgraph G,data ch){
	for (int i=0;i<G.vecnum;i++)
	{
		if (ch==G.myvec[i])
		{
			return i;
		}
	}
	return -1;			//如果没找到Data
}


int main(){
	mgraph G;
	createDG(G);
	Travel(G);

	return 0;
}
