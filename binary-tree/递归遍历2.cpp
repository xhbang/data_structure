
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <malloc.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

typedef int Status;
typedef char TElemType;

typedef struct BiTNode
{
 TElemType  data;
 struct BiTNode *lchild, *rchild; //左右孩子子树
}BiTNode, *BiTree;

Status CreateBiTree(BiTree &T)  //按先序次序输入二叉树中结点的值（一个字符），空格表示空树
{         //构造二叉链表表示的二叉树T
 char ch;
 scanf("%c",&ch);
 if(ch=='#')T=NULL;
 else
 {
  if(!(T=(BiTNode *)malloc(sizeof(BiTNode)))) exit(OVERFLOW);
  T->data=ch;     //生成根结点
  CreateBiTree(T->lchild); //构造左子树
  CreateBiTree(T->rchild); //构造右子树
 }
 return OK;
}//CreatBiTree

Status PreOrderTraverse(BiTree T,Status (* visit)(TElemType e))
{         //递归先序遍历
 if(T)
 {
  (*visit)(T->data);
  PreOrderTraverse(T->lchild,visit);
  PreOrderTraverse(T->rchild,visit);
 }
 return OK;
}

Status InOrderTraverse(BiTree T,Status (* visit)(TElemType e))
{         //递归中序遍历
 if(T)
 {
  InOrderTraverse(T->lchild,visit);
  visit(T->data);
  InOrderTraverse(T->rchild,visit);
 }
 return OK;
}

Status PostOrderTraverse(BiTree T,Status (* visit)(TElemType e))
{         //递归后序遍历
 if(T)
 {
  PostOrderTraverse(T->lchild,visit);
  PostOrderTraverse(T->rchild,visit);
  visit(T->data);
 }
 return OK;
}

Status visit(TElemType e)
{
 printf("%c",e);
 return OK;
}

int BiTreeDepth(BiTree T)
 {         //返回二叉树的深度
   int i,j;
   if(!T)
     return 0;
   if(T->lchild)
     i=BiTreeDepth(T->lchild);
   else
     i=0;
   if(T->rchild)
     j=BiTreeDepth(T->rchild);
   else
     j=0;
   return i>j?++i:++j;
 }

int Leaf(BiTree T)   // 求二叉树叶子结点数目
{
 int n,m;
 if (T==NULL) 
  return (0); 
 else if ((T->lchild == NULL) && (T->rchild == NULL)) 
   return (1); // 如果二叉树的左孩子和右孩子均为空，则返回 1
  else     // 如果二叉树的左孩子或右孩子不为空
  {
   n = Leaf (T->lchild);     // 求 T 的左子树的叶子结点数目
   m = Leaf (T->rchild);     // 求 T 的右子树的叶子结点数目
   return ( n+m );      // 返回总的叶子结点数目
  }//else  
}

void main()
{
 BiTree  T;
 CreateBiTree(T);
 printf("依次先序中序后序输出:\n");
 PreOrderTraverse(T,visit); printf("\n");
 InOrderTraverse(T,visit); printf("\n");
 PostOrderTraverse(T,visit); printf("\n");
 printf("树的深度为：%d\n",BiTreeDepth(T));
 printf("树的叶子节点数为:%d\n",Leaf(T));
 
}