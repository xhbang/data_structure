#include <iostream>
#include <new>		//分配空间
#include <stack>		//用作简单路径

using namespace std;
//#define INFINITY INT_MAX		//定义无穷大,只有在网才用得着
#define maxSize 20		//定义最大节点数

typedef char Info;			//边信息
//typedef char Type;		//节点数据类型
//图类型
typedef enum Kind{DG,DN,AG,AN} Kind;
//定义边类型
typedef Edge{
	int adj;
	Info *info;		//边关系的信息
}Edge,Matrix[maxSize][maxSize];

//定义图的类型
typedef Graph{
	Matrix arcs;
	int vecnum,arcnum;
	Kind kind;
	char vex[maxSize];
}Graph;


class mGraph{
//类
private Graph my;	 //私有：图类型
public:
//节点定位
	int Locate(char ch);
//创建有向图DG
	void createDG();
	/*
//创建无向图AG
	void createAG();
//创建有向网DN
	void createDN();
//创建无向网AN
	void createAN();
	*/
//图的摧毁
	void destroy();
//返回节点的数据
	char getVex(int pos);
//修改节点的数据
	void putVex(int pos,char n);
//节点的第一个邻节点
	int first(int v);
//下一个邻节点
	int next(int v,int w);

//插入节点
//删除节点

//插入边
//删除边


//深度
	void DFSTraverse(int v);
//广度
	void BFSTraverse()

//输出邻接矩阵


/*--------------------实现部分----------------------*/

};
