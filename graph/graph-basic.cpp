#include <stdio.h>

#define MAX  20
int visited[MAX];

typedef struct{
	char vexs[MAX];
	int arcs[MAX][MAX];
	int vexnum,arcnum; }MGraph;
	
	int Locatevex(MGraph *g,char v)
	{ int i;
	for(i=0;i<g->vexnum;++i)
		if(g->vexs[i]==v)  return i;
	}
	
	int  FirstAdjvex(MGraph *g,int v)
	{ int i;
	for(i=0;i<g->vexnum;++i)
		if(g->arcs[v][i]==1)
			return i;
		return -1;
	}
	int  NextAdjvex(MGraph *g,int v,int w)
	{ int  i;
	for(i=w+1;i<g->vexnum;++i)
		if(g->arcs[v][i]==1)
			return i;
		return -1;
	}
	
	CreatUDN(MGraph  *g)
	{ int i,j,k;
	char v1,v2;
	printf("Input the vexnum and arcnum:\n");
	scanf("%d%d",&g->vexnum,&g->arcnum);
	getchar();
	printf("Input the vexs:\n");
	for(i=0;i<g->vexnum;++i)
		scanf("%c",&g->vexs[i]);
	for(i=0;i<g->vexnum;++i)
		for(j=0;j<g->vexnum;++j)
			g->arcs[i][j]=0;
		getchar();
		printf("Input the arcs:\n");
		for(k=0;k<g->vexnum;++k)
		{
			scanf("%c%c,",&v1,&v2);
			i=Locatevex(g,v1); j=Locatevex(g,v2);
			g->arcs[j][i]=g->arcs[i][j]=1;
		}
	}
	
	void DFS(MGraph *g,int v)
	{ int w;
	visited[v]=1;
	printf("%2c",g->vexs[v]);
	for(w=FirstAdjvex(g,v);w>=0;w=NextAdjvex(g,v,w))
		if(!visited[w]) DFS(g,w);
	}
	
	void DFSTraverse(MGraph *g)
	{ int v;
	for(v=0;v<g->vexnum;++v)
		visited[v]=0;
	printf("DFSTraverse:\n");
	for(v=0;v<g->vexnum;++v)
		if(!visited[v]) DFS(g,v);
	}
	
	main()
	{ MGraph g;
	CreatUDN(&g);
	DFSTraverse(&g);
	printf("\n\n");     
}
