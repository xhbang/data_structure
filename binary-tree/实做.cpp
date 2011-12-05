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
	* Parameter:        root:�����ڵ�ָ��
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
	* Parameter:      target:Ԫ��ֵ
	* Precondition:      None
	* Postcondition:  NULL != pTreeT
	* Description:      ����һ��tree�ڵ㣬������ָ��Ϊ�գ����ҷ���ָ���½ڵ��ָ��
	* Return value:      ָ���½ڵ��ָ��
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
	* Parameter:        target:Ҫ�����Ԫ��ֵ, pNode:ָ��ĳһ���ڵ��ָ��
	* Precondition:         NULL != ppTree
	* Description:        ����target��pNode�ĺ���
	* Return value:        ָ���½ڵ��ָ��
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

	if (Node->key == target)    //�����������ͬ��Ԫ��
	{
		return NULL;
	}
	else if (Node->key > target)    //����
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
	* Parameter:        root:�����ڵ�ָ��
	* Precondition:        None
	* Description:        ǰ�����
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
	* Parameter:        root:�����ڵ�ָ��
	* Precondition:        Node
	* Description:        ǰ��(�ȸ�)�����ǵݹ��㷨
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
	* Parameter:        root:�����ڵ�ָ��
	* Precondition:        None
	* Description:        �������
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
	* Parameter:        root:�����ڵ�ָ��
	* Precondition:        None
	* Description:        �������,�ǵݹ��㷨
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
	* Parameter:        root:�����ڵ�ָ��
	* Precondition:        None
	* Description:        �������
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
	* Parameter:        root:�����ڵ�ָ��
	* Precondition:        None
	* Description:        �������,�ǵݹ��㷨
	* Return value:        void
	===========================================================================*/
void BT_PostOrderNoRec(pTreeT root)
{
	//ѧϰ�У���δ����
	stack<treeT *> s;
	pTreeT pre = NULL;      //ʼ��ָ������ոշ��ʹ��Ľڵ�
	//pTreeT top = NULL;
	pTreeT current = root;

	while ((NULL != current) || !s.empty())
	{
		if (NULL != current)
			//������ǰ�ڵ㼰������������û�з��ʹ�����Ҫ�ҵ�������ߵĽڵ�
		{
			s.push(current);
			current = current->left;
		}
		else
			//��ջ�ж�ȡһ���ڵ���Ϊ��ǰ�ڵ�
		{
			current = s.top();
			if(current->right != NULL && current->right != pre)
				//��������������������û�з��ʹ�
				current = current->right;
			else    //û���������ˣ��������������Ѿ����ʹ�
			{
				visit(current);     //���ʵ�ǰ�ڵ�
				pre = current;      //��������ոշ��ʹ��Ľڵ�
				s.pop();            //���ʹ�֮����ջ
				current = NULL;     //��Ҫ���¶Ե�ǰָ����и�ֵ���������䲻�ٽ���������ѭ��
			}
		}
	}
}


/**//*===========================================================================
	* Function name:    BT_LevelOrder
	* Parameter:        root:�����ڵ�ָ��
	* Precondition:        NULL != root
	* Description:        �������
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
//�ҵ�����ߵ�Ҷ��
while((root = root->left) != 0) {
s.push(root);
}

pTree pre; //��¼ǰһ�����ʵĽڵ�
root = s.pop(); //����ջ��Ԫ��

//����������ǿգ�����������δ���ʹ���
//�����ڲ�whileѭ���У���������ѹջ
if(root->right != 0 && pre != root->right) {
//Ҫ����һ���е�����Ԫ������ѹջ
s.push(root);
root = root->right;
s.push(root);
}

//����
else {
����ջ���ڵ㣬������������preΪ�ýڵ�
root = pre = s.pop();
visit(root);
//ʹrootΪ0��������ڲ�ѭ��
root = 0;
}
}
*/

#endif



//���Դ���

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

	//ǰ��
	printf("PreOrder:\n");
	BT_PreOrder(root);
	printf("\n");

	printf("PreOrder no recursion:\n");
	BT_PreOrderNoRec(root);
	printf("\n");

	//����
	printf("InOrder:\n");
	BT_InOrder(root);
	printf("\n");

	printf("InOrder no recursion:\n");
	BT_InOrderNoRec(root);
	printf("\n");

	//����
	printf("PostOrder:\n");
	BT_PostOrder(root);
	printf("\n");

	//����
	printf("LevelOrder:\n");
	BT_LevelOrder(root);
	printf("\n");

	return 0;
}
