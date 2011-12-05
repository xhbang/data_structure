#include <malloc.h>
#include <stdio.h>
#define M 15
typedef struct node
{  int key;
   struct node *link;
}JD;

int h(int k)
{  return(k%13);
}

JD *slbwlcz(JD *t[],int k)
{  JD *p;
   int i;
   i=h(k);
   if(t[i]==NULL)
       return(NULL);
   p=t[i];
   while(p!=NULL)
      if(p->key==k)
	  return(p);
      else
	  p=p->link;
   return(NULL);
}

int slbwlcr(JD *t[],int k)
{  int i;
   JD *p;
   i=h(k);
   if(t[i]==NULL)
   {  p=(JD *)malloc(sizeof(JD));
      p->key=k;
      p->link=NULL;
      t[i]=p;
      printf("\nInserted %d",k);
      return(1);
   }
   else
   {  p=t[i];
      while(p!=NULL)
	 if(p->key==k)
	 {  printf("\nExisted %d",k);
	    return(0);
	 }
	 else if(p->link!=NULL)
	    p=p->link;
	 else
	 {  p->link=(JD *)malloc(sizeof(JD));
	    p=p->link;
	    p->key=k;
	    p->link=NULL;
	    printf("\nInserted %d",k);
	    return(1);
	 }

   }
   return(0);
}

int slbwlsc(JD *t[],int k)
{  int i;
   JD *p,*q;
   i=h(k);
   if(t[i]==NULL)
      return(0);
   p=t[i];
   if(p->key==k)
   {   t[i]=p->link;
       free(p);
       return(1);
   }
   while(p->link!=NULL)
   {  q=p;
      p=p->link;
      if(p->key==k)
      {  q->link=p->link;
	 free(p);
	 return(1);
      }
   }
   return(0);
}

void main()
{   int i,n=12;
    int key[]={19,14,23,1,68,20,84,27,55,11,10,79};
    static JD *table[M],*p;
    for(i=0;i<n;i++)
       slbwlcr(table,key[i]);
    printf("\n");
    for(i=0;i<M;i++)
    {  p=table[i];
       while(p!=NULL)
       {  printf("%d  ",p->key);
	  p=p->link;
       }
       printf("\n");
    }
    p=slbwlcz(table,27);
    if(p==NULL)
	 printf("\nNot found");
    else
	 printf("\nfound %d\n",p->key);
    slbwlsc(table,19);
    slbwlsc(table,27);
    printf("\n");
    for(i=0;i<M;i++)
    {  p=table[i];
       while(p!=NULL)
       {  printf("%d  ",p->key);
	  p=p->link;
       }
       printf("\n");
    }
    p=slbwlcz(table,27);
    if(p==NULL)
	 printf("\nNot found");
    else
	 printf("\nfound %d\n",p->key);
}


