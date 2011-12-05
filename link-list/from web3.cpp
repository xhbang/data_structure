#include<stdio.h>
#include<malloc.h>

typedef struct node
{
	int data;
	struct node *next;
}linklist;

int i;
linklist *Creatlist()
{
	char ch;
	linklist *head,*s,*r;
	head=NULL;
	r=NULL;
	ch=getchar();
	i=0;
	while(ch!='$')
	{
		s=(linklist *)malloc(sizeof(linklist));
		s->data=ch;
		if(head==NULL)
			head=s;
		else
			r->next=s;
		r=s; 
		i++;
		ch=getchar();
	}

	if(r!=NULL)
		r->next=NULL;
   return head;
}

void printlinklist(linklist *h)
{
	
	linklist *head,*p;
	int j;
	head=h;
	p=head;
	if(head==NULL)
		printf("??");
	else
		for(j=0;j<i;j++)
		{
			printf("%c",p->data);
			p=p->next;
		}
}

linklist *jh(linklist *x,linklist *y)
{
	linklist *head,*h,*g,*t,*r;
	int i,l,k;
	h=x,g=y;
	head=t;
	for(l=0;l<i;l++)
	{
		t=(linklist *)malloc(sizeof(linklist));
		r->next=t;
		r=t;
	}
	for(l=0,k=0;l<(i/2),k<(i/2);l++,k++)
	{
		
		t->data=h->data;
		t=t->next;
		h=h->next;
      t->data=g->data;
		t=t->next;
		g=g->next;
		
	}
	head=t;
	return head;
	
}

void main()
{
	int j;
	linklist *m,*n,*f;
	m=Creatlist();
	printlinklist(m);
	fflush(stdin);
	n=Creatlist();
	printlinklist(n);
/*
	f=jh(m,n);
	for(j=0;j<i;j++)
	{
		printf("%c",f->data);
		f=f->next;
	}
*/
}