#include <stdio.h>
#include <malloc.h>
#include <iostream>
using namespace std;
#define MAX_VERTEX_NUM 20
struct Edge
{
	int adjvex;// 边的另一个顶点位置
	int weight;//权值
	Edge *nextarc;  //下一条边链指针

};
struct Vertex
{
	char data; //顶点的值，
	Edge *firstarc; //出边表的头指针
};
struct Graph
{
	Vertex *NodeTable; //顶点表
	int NumVertices; //当前顶点个数
	int NumEdges; //当前边数
};
typedef struct
{
	int *base;
	int *top;
}SqStack; 
bool Visited[MAX_VERTEX_NUM];
bool visited[MAX_VERTEX_NUM];
bool visit[MAX_VERTEX_NUM];
void InsertVertex(Graph &G,char &name);
void CreateGraph(Graph &G);
int GetVertexPos(Graph &G,char &tail);
void InsertEdge(Graph &G,int k,int j,int weight);
void DFSTraverse(Graph &G);
void BFSTraverse(Graph &G);
void DFS(Graph &G,int v);
int GetfirstNeighbor(Graph &G,int &v);
int GetNextNeighbor(Graph &G,int &v,int &w);
void BFS(Graph &G,int v);
void Path(Graph &G,int a,int b,SqStack &s);
SqStack& InitStack(SqStack &s);
void main()
{
	Graph graph;
	char i,s;
	SqStack T;
	T=InitStack(T);
	CreateGraph(graph);
	cout<<"按深度优先搜索可得："<<endl;
	DFSTraverse(graph);
	cout<<endl;
	cout<<"按广度优先搜索可得："<<endl;
	BFSTraverse(graph);
	cout<<endl;
	cout<<"请输入第一个顶点"<<endl;
	cin>>i;
	int a=GetVertexPos(graph,i);
	if(a==-1)
		return ;
	cout<<"请输入第二个顶点"<<endl;
	cin>>s;
	int b=GetVertexPos(graph,s);
	if(b==-1)
		return;
	Path(graph,b,a,T);

}
void CreateGraph(Graph &G)
{
	int n,m,k,j;
	int weight;
	char name,tail,head;
	G.NumEdges=0;
	G.NumVertices=0;
	cout<<"请输入该图的顶点个数"<<endl;
	cin>>n;
	G.NodeTable=(Vertex *)malloc(n*sizeof(Vertex));
	cout<<"请输入顶点"<<endl;
	for (int i=0;i<n;i++)
	{
		cin>>name;
		InsertVertex(G,name);
	}
	cout<<"请输入边的条数"<<endl;
    cin>>m;
     cout<<"请输入起始和终止结点，权值"<<endl;
	for (i=0;i<m;i++)
	{
		cin>>tail>>head>>weight;
	       k=GetVertexPos(G,tail);
		     j=GetVertexPos(G,head);
		        InsertEdge(G,k,j,weight);
	}
}
void InsertVertex(Graph &G,char &name)
{
    G.NodeTable[G.NumVertices].data=name;
	G.NodeTable[G.NumVertices].firstarc=NULL;
	 G.NumVertices++;
}
int GetVertexPos(Graph &G,char &tail)
{
	for (int i=0;i<G.NumVertices;i++)
	   if (G.NodeTable[i].data==tail)
	       return i;
	return -1;
}
void InsertEdge(Graph &G,int k,int j,int weight)
{
	Edge *p,*q;
	p=(Edge *)malloc(sizeof(Edge));
	p->adjvex=j;
	p->weight=weight;
	p->nextarc=NULL;
     q=G.NodeTable[k].firstarc;
	   if (q==NULL)
	     G.NodeTable[k].firstarc=p;
	   else
	   {
    		while(q->nextarc!=NULL)
		       q=q->nextarc;
			q->nextarc=p;
	   }	   
	
    G.NumEdges++;
}
void DFSTraverse(Graph &G)
{
	for (int i=0;i<G.NumVertices;i++)
	   Visited[i]=false;
	DFS(G,0);
	
}
void DFS(Graph &G,int v)
{
    cout<<G.NodeTable[v].data<<' ';
	Visited[v]=1;
	int w=GetfirstNeighbor(G,v);
	 while (w!=-1)
	 {
		 if (!Visited[w])
		    DFS(G,w);
		   w=GetNextNeighbor(G,v,w);
	 }
}
int GetfirstNeighbor(Graph &G,int &v)
{
	if (v!=-1)
	{
	    Edge *p=G.NodeTable[v].firstarc;
		 if (p!=NULL)
		   return p->adjvex;
	}
	return -1;
}
int GetNextNeighbor(Graph &G,int &v,int &w)
{
	if (v!=-1)
	{
		Edge *p=G.NodeTable[v].firstarc;
		 while(p!=NULL)
		 {
			 if (p->adjvex==w&&p->nextarc!=NULL)
			   return p->nextarc->adjvex;
			 else p=p->nextarc;
			 
		 }
	}
	return -1;
}
void BFSTraverse(Graph &G)
{
	for (int i=0;i<G.NumVertices;i++)
	    visited[i]=false;
	BFS(G,0);
}
void BFS(Graph &G,int v)
{
	int *p;
	int front=0,rear=0;
	int w;
	p=(int *)malloc(G.NumVertices*sizeof(int));
	cout<<G.NodeTable[v].data<<" ";
	  visited[v]=true;
	    p[rear]=v;
		  rear++;
		while(front!=rear)
		{
			v=p[front];
			  front++;
			w=GetfirstNeighbor(G,v);
			 while (w!=-1)
			 {
				 if (!visited[w])
				 {
					 cout<<G.NodeTable[w].data<<" ";
					   visited[w]=true;
					     p[rear]=w;
						   rear++;
				 }
				 w=GetNextNeighbor(G,v,w);
			 }
		}
		delete p;
}
SqStack& InitStack(SqStack &s)
{//构造空栈
	s.base=(int*)malloc(MAX_VERTEX_NUM*sizeof(int));
	s.top=s.base;
	return s;
}
void Path(Graph &G,int a,int b,SqStack &S)
{
	int w,*i;
	int *s;
	s=(int *)malloc(G.NumVertices*sizeof(int));
	Edge *p;
	visit[a]=true;
	*S.top=a;
	S.top++;
	i=S.top;
	if(a==b)  //找到简单路径，输出
	{
		while(i!=S.base)
		{
			i--;
			cout<<G.NodeTable[*i].data;
		}
	     cout<<endl;
	} 
	p=G.NodeTable[a].firstarc;
	while(p!=NULL)
	{
		w=p->adjvex;
		if(!visit[w])
			Path(G,w,b,S);
		p=p->nextarc;
	}
	visit[a]=false;
	S.top--;
}