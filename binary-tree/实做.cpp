/**//********************************************************************
	filename:     bintree.h
	author:      Hang Xie
	*********************************************************************/

#ifndef TREE_H
#define TREE_H


#include <stdio.h>
#include <malloc.h>
#include <stack>
#include <queue>
#include <assert.h>

using namespace std;



typedef int ElemType;

typedef struct treeT
{
	ElemType key;
	struct treeT* left;
	struct treeT* right;
}treeT, *pTreeT;




/**//*===========================================================================
	* Function name:    visit
	* Parameter:        root:树根节点指针
	* Precondition:
	* Description:
	* Return value:
	===========================================================================*/
static void visit(pTreeT root)
{
	if (NULL != root)
	{
		printf(" %d\n", root->key);
	}
}



/**//*===========================================================================
	* Function name:  BT_MakeNode
	* Parameter:      target:元素值
	* Precondition:      None
	* Postcondition:  NULL != pTreeT
	* Description:      构造一个tree节点，置左右指针为空，并且返回指向新节点的指针
	* Return value:      指向新节点的指针
	===========================================================================*/
static pTreeT BT_MakeNode(ElemType target)
{
	pTreeT pNode = (pTreeT) malloc(sizeof(treeT));

	assert( NULL != pNode );

	pNode->key   = target;
	pNode->left  = NULL;
	pNode->right = NULL;

	return pNode;
}


/**//*===========================================================================
	* Function name:    BT_Insert
	* Parameter:        target:要插入的元素值, pNode:指向某一个节点的指针
	* Precondition:         NULL != ppTree
	* Description:        插入target到pNode的后面
	* Return value:        指向新节点的指针
	===========================================================================*/
pTreeT BT_Insert(ElemType target, pTreeT* ppTree)
{
	pTreeT Node;

	assert( NULL != ppTree );

	Node = *ppTree;
	if (NULL == Node)
	{
		return *ppTree = BT_MakeNode(target);
	}

	if (Node->key == target)    //不允许出现相同的元素
	{
		return NULL;
	}
	else if (Node->key > target)    //向左
	{
		return BT_Insert(target, &Node->left);
	}
	else
	{
		return BT_Insert(target, &Node->right);
	}
}


/**//*===========================================================================
	* Function name:    BT_PreOrder
	* Parameter:        root:树根节点指针
	* Precondition:        None
	* Description:        前序遍历
	* Return value:        void
	===========================================================================*/
void BT_PreOrder(pTreeT root)
{
	if (NULL != root)
	{
		visit(root);
		BT_PreOrder(root->left);
		BT_PreOrder(root->right);
	}
}


/**//*===========================================================================
	* Function name:    BT_PreOrderNoRec
	* Parameter:        root:树根节点指针
	* Precondition:        Node
	* Description:        前序(先根)遍历非递归算法
	* Return value:        void
	===========================================================================*/
void BT_PreOrderNoRec(pTreeT root)
{
	stack<treeT *> s;

	while ((NULL != root) || !s.empty())
	{
		if (NULL != root)
		{
			visit(root);
			s.push(root);
			root = root->left;
		}
		else
		{
			root = s.top();
			s.pop();
			root = root->right;
		}
	}
}



/**//*===========================================================================
	* Function name:    BT_InOrder
	* Parameter:        root:树根节点指针
	* Precondition:        None
	* Description:        中序遍历
	* Return value:        void
	===========================================================================*/
void BT_InOrder(pTreeT root)
{
	if (NULL != root)
	{
		BT_InOrder(root->left);
		visit(root);
		BT_InOrder(root->right);
	}
}


/**//*===========================================================================
	* Function name:    BT_InOrderNoRec
	* Parameter:        root:树根节点指针
	* Precondition:        None
	* Description:        中序遍历,非递归算法
	* Return value:        void
	===========================================================================*/
void BT_InOrderNoRec(pTreeT root)
{
	stack<treeT *> s;
	while ((NULL != root) || !s.empty())
	{
		if (NULL != root)
		{
			s.push(root);
			root = root->left;
		}
		else
		{
			root = s.top();
			visit(root);
			s.pop();
			root = root->right;
		}
	}
}



/**//*===========================================================================
	* Function name:    BT_PostOrder
	* Parameter:        root:树根节点指针
	* Precondition:        None
	* Description:        后序遍历
	* Return value:        void
	===========================================================================*/
void BT_PostOrder(pTreeT root)
{
	if (NULL != root)
	{
		BT_PostOrder(root->left);
		BT_PostOrder(root->right);
		visit(root);
	}
}


/**//*===========================================================================
	* Function name:    BT_PostOrderNoRec
	* Parameter:        root:树根节点指针
	* Precondition:        None
	* Description:        后序遍历,非递归算法
	* Return value:        void
	===========================================================================*/
void BT_PostOrderNoRec(pTreeT root)
{
	//学习中，尚未明白
	stack<treeT *> s;
	pTreeT pre = NULL;      //始终指向最近刚刚访问过的节点
	//pTreeT top = NULL;
	pTreeT current = root;

	while ((NULL != current) || !s.empty())
	{
		if (NULL != current)
			//表明当前节点及其左右子树均没有访问过，需要找到其最左边的节点
		{
			s.push(current);
			current = current->left;
		}
		else
			//从栈中顶取一个节点作为当前节点
		{
			current = s.top();
			if(current->right != NULL && current->right != pre)
				//有右子树并且其右子树没有访问过
				current = current->right;
			else    //没有右子树了，或者其右子树已经访问过
			{
				visit(current);     //访问当前节点
				pre = current;      //保存最近刚刚访问过的节点
				s.pop();            //访问过之后便出栈
				current = NULL;     //需要重新对当前指针进行赋值，并控制其不再进入左子树循环
			}
		}
	}
}


/**//*===========================================================================
	* Function name:    BT_LevelOrder
	* Parameter:        root:树根节点指针
	* Precondition:        NULL != root
	* Description:        层序遍历
	* Return value:        void
	===========================================================================*/
void BT_LevelOrder(pTreeT root)
{
	queue<treeT *> q;
	treeT *treePtr;

	assert( NULL != root );

	q.push(root);

	while (!q.empty())
	{
		treePtr = q.front();
		q.pop();
		visit(treePtr);

		if (NULL != treePtr->left)
		{
			q.push(treePtr->left);
		}
		if (NULL != treePtr->right)
		{
			q.push(treePtr->right);
		}

	}
}

/**
void BT_PostOrderNoRec(pTreeT root)
{
stack<pTreeT> s;
s.push(root);

while(root != 0 || !s.isEmpty()) {
//找到最左边的叶子
while((root = root->left) != 0) {
s.push(root);
}

pTree pre; //记录前一个访问的节点
root = s.pop(); //弹出栈顶元素

//如果右子树非空，并且右子树未访问过，
//则（在内层while循环中）把右子树压栈
if(root->right != 0 && pre != root->right) {
//要把上一句中弹出的元素重新压栈
s.push(root);
root = root->right;
s.push(root);
}

//否则
else {
弹出栈顶节点，访问它并设置pre为该节点
root = pre = s.pop();
visit(root);
//使root为0以免进入内层循环
root = 0;
}
}
*/

#endif



//测试代码

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//#include "tree.h"

#define MAX_CNT 5
#define BASE  100

int main(int argc, char *argv[])
{
	int i;
	pTreeT root = NULL;

	srand( (unsigned)time( NULL ) );

	for (i=0; i<MAX_CNT; i++)
	{
		BT_Insert(rand() % BASE, &root);
	}

	//前序
	printf("PreOrder:\n");
	BT_PreOrder(root);
	printf("\n");

	printf("PreOrder no recursion:\n");
	BT_PreOrderNoRec(root);
	printf("\n");

	//中序
	printf("InOrder:\n");
	BT_InOrder(root);
	printf("\n");

	printf("InOrder no recursion:\n");
	BT_InOrderNoRec(root);
	printf("\n");

	//后序
	printf("PostOrder:\n");
	BT_PostOrder(root);
	printf("\n");

	//层序
	printf("LevelOrder:\n");
	BT_LevelOrder(root);
	printf("\n");

	return 0;
}
