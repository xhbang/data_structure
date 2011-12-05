
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
 struct BiTNode *lchild, *rchild; //���Һ�������
}BiTNode, *BiTree;

Status CreateBiTree(BiTree &T)  //�������������������н���ֵ��һ���ַ������ո��ʾ����
{         //������������ʾ�Ķ�����T
 char ch;
 scanf("%c",&ch);
 if(ch=='#')T=NULL;
 else
 {
  if(!(T=(BiTNode *)malloc(sizeof(BiTNode)))) exit(OVERFLOW);
  T->data=ch;     //���ɸ����
  CreateBiTree(T->lchild); //����������
  CreateBiTree(T->rchild); //����������
 }
 return OK;
}//CreatBiTree

Status PreOrderTraverse(BiTree T,Status (* visit)(TElemType e))
{         //�ݹ��������
 if(T)
 {
  (*visit)(T->data);
  PreOrderTraverse(T->lchild,visit);
  PreOrderTraverse(T->rchild,visit);
 }
 return OK;
}

Status InOrderTraverse(BiTree T,Status (* visit)(TElemType e))
{         //�ݹ��������
 if(T)
 {
  InOrderTraverse(T->lchild,visit);
  visit(T->data);
  InOrderTraverse(T->rchild,visit);
 }
 return OK;
}

Status PostOrderTraverse(BiTree T,Status (* visit)(TElemType e))
{         //�ݹ�������
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
 {         //���ض����������
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

int Leaf(BiTree T)   // �������Ҷ�ӽ����Ŀ
{
 int n,m;
 if (T==NULL) 
  return (0); 
 else if ((T->lchild == NULL) && (T->rchild == NULL)) 
   return (1); // ��������������Ӻ��Һ��Ӿ�Ϊ�գ��򷵻� 1
  else     // ��������������ӻ��Һ��Ӳ�Ϊ��
  {
   n = Leaf (T->lchild);     // �� T ����������Ҷ�ӽ����Ŀ
   m = Leaf (T->rchild);     // �� T ����������Ҷ�ӽ����Ŀ
   return ( n+m );      // �����ܵ�Ҷ�ӽ����Ŀ
  }//else  
}

void main()
{
 BiTree  T;
 CreateBiTree(T);
 printf("������������������:\n");
 PreOrderTraverse(T,visit); printf("\n");
 InOrderTraverse(T,visit); printf("\n");
 PostOrderTraverse(T,visit); printf("\n");
 printf("�������Ϊ��%d\n",BiTreeDepth(T));
 printf("����Ҷ�ӽڵ���Ϊ:%d\n",Leaf(T));
 
}