#include<stdio.h>
#include<malloc.h>
#include<string.h>
typedef struct Fnode/*符号单链表*/
{
	int yxj;
	char fh;
	struct Fnode *next;
}Fnode;

void F_push(Fnode *h,char c)/*尾插*/
{
	Fnode *p;
	p=(Fnode*)malloc(sizeof(Fnode));
	p->fh=c;
	p->next=NULL;
	if(c=='+'||c=='-')
		p->yxj=1;
	else if(c=='*'||c=='/')
		p->yxj=2;
	else if(c=='('||c==')')
		p->yxj=0;
	else
	{ free(p); return;}
	while(h->next!=NULL)
		h=h->next;
	p->next=h->next;
	h->next=p;
}

char F_pop(Fnode *h)/*尾删*/
{
	char c;
	while(h->next->next!=NULL)
		h=h->next;
	c=h->next->fh;
	free(h->next);
	h->next=NULL;
	return c;
}
int F_look(Fnode *h)
{
	while(h->next!=NULL)
		h=h->next;
	return h->yxj;
}

/*------------------------------------------------------------*/
typedef struct Snode/*数字单链表*/
{
	double data;
	struct Snode *next;
}Snode;

void S_push(Snode *h,double c)/*尾插*/
{
	Snode *p;
	p=(Snode*)malloc(sizeof(Snode));
	p->data=c;
	p->next=NULL;
	while(h->next!=NULL)
		h=h->next;
	p->next=h->next;
	h->next=p;
}

double S_pop(Snode *h)/*尾删*/
{
	double i;
	while(h->next->next!=NULL)
		h=h->next;
	i=h->next->data;
	free(h->next);
	h->next=NULL;
	return i;
}
/*-------------------------------------------------------*/

char *change(char *str)/*字符串前加（，后加 ）*/
{
	char *r;
	*(str-1)='(';
	str--;
	r=str;
	strcat(r,")");
	return r;
}
/*;-------------------------------------------------*/
double final(char *str,Fnode *fh,Snode *sh)/*计算表达式结果*/
{
	double i,temp,emp;
	while(*str!='\0')
	{
		if(*str=='(')
		{
			F_push(fh,*str);
			str++;
			continue;
		}
		else if(*str>='0'&&*str<='9')
		{
			emp=0;
			while(*str>='0'&&*str<='9')
			{
				emp=emp*10+(*str-'0');
				str++;
			}
			S_push(sh,emp);
			continue;
		}
		else if(*str=='.')
		{
			i=0.1; str++; emp=0;
			if(*str>='0'&&*str<='9')
			{
				while(*str>='0'&&*str<='9')
				{
					emp+=(*str-'0')*i;
					i*=0.1;
					str++;
				}
				S_push(sh,(S_pop(sh)+emp));
			}           
		}
		else if(*str==')')
		{
			while(F_look(fh)!=0)
			{
				switch(F_pop(fh))
				{
				case '+':emp=S_pop(sh);S_push(sh,(S_pop(sh)+emp));break;
				case '-':emp=S_pop(sh);S_push(sh,(S_pop(sh)-emp));break;
				case '*':emp=S_pop(sh);S_push(sh,(S_pop(sh)*emp));break;
				case '/':emp=S_pop(sh);S_push(sh,(S_pop(sh)/emp));break;
				default :;
				}
			}
			F_pop(fh);
			str++;
			continue;
		}
		else
		{
			if(*str=='+'||*str=='-')
				temp=1;
			else
				temp=2;
			if(temp>F_look(fh))
				F_push(fh,*str);
			else
			{
				switch(F_pop(fh))
				{
				case '+':emp=S_pop(sh);S_push(sh,(S_pop(sh)+emp));break;
				case '-':emp=S_pop(sh);S_push(sh,(S_pop(sh)-emp));break;
				case '*':emp=S_pop(sh);S_push(sh,(S_pop(sh)*emp));break;
				case '/':emp=S_pop(sh);S_push(sh,(S_pop(sh)/emp));break;
				default :;
				}
				F_push(fh,*str);
			}
			str++;continue;
		}
	}
	return  S_pop(sh);
}

main()
{
	Fnode *fh;
	Snode *sh;
	char *str;
	fh=(Fnode*)malloc(sizeof(Fnode));
	fh->next=NULL;
	sh=(Snode*)malloc(sizeof(Snode));
	sh->next=NULL;
	str=change(gets(str));
	printf("%lf",final(str,fh,sh));
	getch();
} 