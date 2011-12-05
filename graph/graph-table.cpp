#include <iostream>
#include <new>		//新建节点
//#include <stack>		//path
#include <malloc.h>
//#include <vector>
//#include <queue>	//广度优先		怎么去利用STL里面的东西啊！

using namespace  std;
const int maxSize=20;		//最大节点数
typedef struct{
	int *base;
	int * top;
}Queue;

typedef struct{
	int *base;
	int *top;
}Stack;

typedef struct ArcNode{
	int adjvex;
	string info;
	ArcNode *nexarc;
}ArcNode;

typedef struct {
	char data;
	ArcNode *firstarc;
}VNode,AdjList[maxSize];

typedef struct {
	AdjList vex;
	int vexnum;
	int arcnum;
	bool visited[maxSize];		//在递归遍历的时候使用
}DGgraph;

class Graph{
private:
	DGgraph G;
public:
	Graph(){
		G.vexnum=G.arcnum=0;
	}
	Graph(int vex,int arc){				//重载版本
		G.arcnum=arc;
		G.vexnum=vex;
	}
//求顶点在图中的位置
	int locateVex(char v);
//构造没有相关信息的无向图
	void createDG();
//销毁图
	void destroyDG();
//返回序号是v的顶点的值
	char getVex(int v);
//对v赋新值value
	void putVex(int v,char ch);
//返回v的第一个邻接顶点的序号
	int getFirst(char v);
//返回v(w后)的下一个邻接项的点的序号
	int getNext(char v,char w);
//增加新的顶点v
	void addVex(char v);
//删除图G顶点v和相关的弧
	void deleteVex(int v);
//增加弧<v,w>
	void addArc(int v,int w);
//删除弧<v,w>
	void deleteArc(int v,int w);
//从第v个顶点出发深度优先遍历图
	void DFS(int v);
//从第一个节点出发深度遍历图
	void DFSTraverse();
//从第一个节点出发广度遍历图
	void BFSTraverse();
//输出图G,正在考虑用重载
	void Display(ostream &out);
//重载输出，现在有点问题
	ostream &operator<<(ostream &out)const{
		ArcNode *p;
		out<<G.vexnum<<"个顶点"<<endl;
		for(int i=0;i<G.vexnum;i++)
			out<<G.vex[i].data<<"\t";
		out<<endl;
		out<<G.arcnum<<"条边"<<endl;
		for(i=0;i<G.vexnum;i++){
			p=G.vex[i].firstarc;
			while(p){
				out<<G.vex[i].data<<"->"<<p->adjvex<<endl;
				p=p->nexarc;
			}
		}
		return out;
	}
//求v到w的一段简单路径
	void path(char v,char w);
	void dPath(Stack &istack,int i,int j);		//递归部分

};

/*------------实现---------------*/
int Graph::locateVex(char v){
	int i=0;
	for(;i<G.vexnum;i++)
		if(G.vex[i].data==v)
			return i;
	return -1;		//没找到
}

void Graph::createDG(){			//创建有向图
	char cha,chb;
	int i,j,k;
	if(G.arcnum==0 && G.vexnum==0){				//没有初始化过
		cout<<"请输入图的节点数和边数"<<endl;
		cin>>G.vexnum>>G.arcnum;
	}
	for(i=0;i<G.vexnum;i++){
		G.visited[i]=false;
	}
	cout<<"请输入"<<G.vexnum<<"个顶点向量"<<endl;
	for(i=0;i<G.vexnum;i++){
		cin>>G.vex[i].data;
		G.vex[i].firstarc=NULL;			//千万不要把这个搞忘了
	}
	cout<<"请输入"<<G.arcnum<<"条边：格式（点1 点2）"<<endl;
	for(k=0;k<G.arcnum;k++){
		ArcNode *p=NULL;
		cin>>cha>>chb;
		i=locateVex(cha);
		j=locateVex(chb);
		p=new ArcNode;
		p->adjvex=j;
		p->info="0";
		p->nexarc=G.vex[i].firstarc;		//在头结点插入
		G.vex[i].firstarc=p;
	}
}

void Graph::destroyDG(){
	int i;
	ArcNode *p,*q;
	for(i=0;i<G.vexnum;i++){
		p=G.vex[i].firstarc;
		while(p){
			q=p->nexarc;
//			free(p->info);
			free(p);
			p=q;
		}
	}
	G.arcnum=G.vexnum=0;
}

char Graph::getVex(int v){		//v是序号，不是第几个
	if(v<0 || v>=G.vexnum)
		throw 1;
	return G.vex[v].data;
}

void Graph::putVex(int v,char ch){
	int i=locateVex(v);
	if(i!=-1)
		G.vex[i].data=ch;			//但是这里好像有点问题，邻接表边节点上面需不需要修改
}

int Graph::getFirst(char v){
	ArcNode *p;
	int i=locateVex(v);
	if(i==-1)
		return -1;
	p=G.vex[i].firstarc;
	if(p)
		return p->adjvex;
	else
		return -1;
}

int Graph::getNext(char v,char w){
	int i,j;
	i=locateVex(v);	
	j=locateVex(w);
	ArcNode *p=NULL;
	p=G.vex[i].firstarc;
	if(i==-1 || j==-1)
		throw 1;
	while(p&&p->adjvex!=j)		//写成W了
		p=p->nexarc;
	if(!p || !(p->nexarc))			//找完了是空或者p是最后一个节点
		return -1;
	else
		return p->nexarc->adjvex;
}

void Graph::addVex(char v){
	G.vex[G.vexnum].data=v;
	G.vex[G.vexnum].firstarc=NULL;
	G.vexnum++;
}

//删除节点过于复杂
void Graph::deleteVex(int v){
	int i,j;
	ArcNode *p,*q;
	i=locateVex(v);
	if(i==-1)
		throw 1;
	p=G.vex[i].firstarc;		//准备删除以i为出度的边
	while(p){
		q=p->nexarc;
//		free(p->info);
		free(p);
		p=q;
		G.arcnum--;
	}
	G.vexnum--;
	for(j=i;j<G.vexnum;j++){		//整体迁移
		G.vex[i]=G.vex[i+1];
	}
	for(j=0;j<G.vexnum;i++){
		p=G.vex[j].firstarc;
		while(p){
			if(p==G.vex[j].firstarc){		//正好是头的那一个
				G.vex[j].firstarc=p->nexarc;
//				free(p->info);
				free(p);
				p=G.vex[j].firstarc;
				G.arcnum--;				//有向图啦
			}
			else{
				q=p->nexarc;
//				free(p->info);
				free(p);
				p=q;
			}
		}
	}
}

//其他几个暂时不想写

void Graph::DFSTraverse(){		
	int v;
	for(v=0;v<G.vexnum;v++)
		G.visited[v]=false;				//记得一定要初始化，因为其他操作可能改变其值
	for(v=0;v<G.vexnum;v++)
		if(!G.visited[v])
			DFS(v);
}

void Graph::Display(ostream &out){
	ArcNode *p;
	out<<G.vexnum<<"个顶点"<<endl;
	for(int i=0;i<G.vexnum;i++)
		out<<G.vex[i].data<<" ";
	out<<endl;
	out<<G.arcnum<<"条边"<<endl;
	for(i=0;i<G.vexnum;i++){
		p=G.vex[i].firstarc;
		out<<G.vex[i].data;
		while(p){
			out<<"->"<<G.vex[p->adjvex].data;
			p=p->nexarc;
		}
		out<<endl;
	}
}
void Graph::DFS(int v){
	G.visited[v]=true;
	cout<<G.vex[v].data<<" ";
	int w;
	for(w=getFirst(getVex(v));w>=0;w=getNext(getVex(v),getVex(w)))
		if(!G.visited[w])
			DFS(w);
}

void Graph::BFSTraverse(){			//参考书上170页.我是想在这里用STL的，但是出了点问题
	int i,w,v;
	int *qu=(int *)malloc(G.vexnum*sizeof(int));
	int rear,front;
	rear=front=0;
	
//	vector<int> vec;
	for(i=0;i<G.vexnum;i++)
		G.visited[i]=false;
	for(i=0;i<G.vexnum;i++){
		if(!G.visited[i]){
			G.visited[i]=true;
			cout<<G.vex[i].data<<" ";
			qu[rear]=i;
			rear++;
			while(front!=rear){
				v=qu[front];
				front++;
				for(w=getFirst(getVex(v));w>=0;w=getNext(getVex(v),getVex(w))){
					if(!G.visited[w]){
						G.visited[w]=true;
						cout<<G.vex[w].data<<" ";
						qu[rear]=w;
						rear++;
					}
				}
			}//while
		}//if
	}
}

void Graph::path(char v,char w){
	int i,j,k;
	for(k=0;k<G.vexnum;k++)
		G.visited[k]=false;
	i=locateVex(v);
	j=locateVex(w);
	Stack istack;
	istack.base=(int *)malloc(G.vexnum*sizeof(int));
	istack.top=istack.base;			//辅助栈的初始化
	dPath(istack,i,j);
}

void Graph::dPath(Stack &istack,int i,int j){
	G.visited[i]=true;
	*istack.top=i;		//有个*
	istack.top++;
	if(i==j){
		int *temp=istack.base;
		while(temp!=istack.top){
			cout<<G.vex[*temp].data<<" ";
			temp++;
		}
		cout<<endl;
	}
	ArcNode *p=NULL;
	int w;		//储存节点的值
	p=G.vex[i].firstarc;
	while(p){
		w=p->adjvex;
		if(!G.visited[w])
			dPath(istack,w,j);
		p=p->nexarc;
	}
	G.visited[i]=false;			//写成了w,害的我调试半天
	istack.top--;
}

int main(){
	Graph my(9,20);			//点数，边数,下一步，怎么运用try,catch
	try{			
		my.createDG();
	//	cout<<my;				//怎么进行重载
		my.Display(cout);
		cout<<"深度优先"<<endl;
		my.DFSTraverse();
		cout<<endl;
		cout<<"广度优先"<<endl;
		my.BFSTraverse();
		cout<<endl;
		cout<<"需找A到H的一条简单路径"<<endl;
		my.path('a','h');
	}catch(int i){
		if(i=1)
			cout<<"肯定是输入了没有的点"<<endl;
	}
	return 0;
}
