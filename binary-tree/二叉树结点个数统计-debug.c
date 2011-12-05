//#include <alloc.h>
#include <stdio.h>

typedef struct node
{   char data;
    struct node *lchild,*rchild;
}JD;

void countleaf(JD *bt,int *count)
{   if(bt!=NULL)
    {  if((bt->lchild==NULL)&&(bt->rchild==NULL))
       {   (*count)++;
	   return;
       }
       countleaf(bt->lchild,count);
       countleaf(bt->rchild,count);
    }
}

JD *crt_bt_pre(JD *bt)
{  char ch;
   printf("ch=");
   scanf("%c",&ch);
   getchar();
   if(ch==' ')  bt=NULL;
   else
   {   bt=(JD *)malloc(sizeof(JD));
       bt->data=ch;
       bt->lchild=crt_bt_pre(bt->lchild);
       bt->rchild=crt_bt_pre(bt->rchild);
   }
   return(bt);
}

void main()
{  /* ABC00DE0G00F000  */
    JD *head=NULL;
    int count=0;
   head=crt_bt_pre(head);
   countleaf(head,&count);
   printf("count of leaf node is %d\n",count);
}
