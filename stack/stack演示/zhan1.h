//zhan1.h

#define MAX 100
typedef struct stack{
	int cout;
	char data[MAX];
}stack;
//��ʼ��ջ
int Init(stack *L)
{
	*L->data=(char)malloc(sizeof(stack));
	if(!L->data){printf("�ڴ���������");exit(0);}
	L->cout=0;
	L->data[L->cout]='#';
	return 0;
}
//��ʼԪ��e��ջ
int Push(stack *L,char e)
{
	L->data[L->cout++]=e;
	return 0;
}
//��ʼԪ��c��ջ
int Pop(stack *L,char *c)
{
	*c=L->data[--L->cout];
	// printf("%c",c);
	return 0;
}
//����ջ�ĳ���
int stacklength(stack *L)
{
	char c;
	int i=0;
	while(L->cout>0)
	{
		++i;
		Pop(L,&c);
		printf(" %c ",c);
	}
	return i;

}
//�ж��Ƿ��ǿ�ջ
int StackEmpty(stack *L)
{
	if(L->cout>=0)return 1;
	else return 0;
}
//��ջ
int ClearStack(stack *L)
{
	if(L->cout>=0)
	{
		L->cout=0;
		L->data[L->cout]='#';
		printf("\n��ջ�ɹ�������\n");
		return 0;
	}
	else
	{
		printf("\n��ջ�����ڣ���\n");

		return 1;
	}
}
//�ݻ�ջ
int Destory(stack *L)
{
	if(L->cout>=0)
	{
		L->cout=0;
		L->data[L->cout]=NULL;
		return 0;
	}
	else
	{
		printf("\n��ջ�����ڣ���\n");
		return 1;
	}

}

//�ж��Ƿ��������
int is_operator(char op)
{
	switch(op)
	{
	case'+':
	case'-':
	case'*':
	case'/':
	case'(':
	case')':return 1;
	default:return 0;
	}
}
//�ж��Ƿ���/����-
int is_special_code(char str)
{
	if(str=='/'||str=='-')return 1;
	else return 0;
}
//�ж�����������ȼ�
int operator_grade(char op)
{
	switch(op)
	{
	case'+': case'-':return 1;
	case'*': case'/':return 2;
	case'(': case')':return 3;
	default:return 0;
	}
}
//��b��c����str3����
int opera(int b,int c,char str3)
{
	int n;
	if(str3=='+')n=b+c;
	if(str3=='-')n=b-c;
	if(str3=='*')n=b*c;
	if(str3=='/')n=b/c;
	return n;
}
//��a��b����str3����(С���͸�����)
double operad(double a,double b,char str3)
{
	double n;
	if(str3=='+')n=a+b;
	if(str3=='-')n=a-b;
	if(str3=='*')n=a*b;
	if(str3=='/')n=a/b;
	return n;
}
int numberchar(char number[5])
{
	char number1[5];
	for(int i=0,j=strlen(number)-1;j>=0;number1[i++]=number[j--])
		number1[i]='\0';
	return atoi(number1);
}
//ȡ�������������ַ�ת������������
int winnumber(stack *L,char *c,char number1[5])
{
	int i;
	Pop(L,c);
	for(i=0;*c>='0'&&*c<='9';number1[i++]=*c,Pop(L,c));
	number1[i]='\0';
	Push(L,*c); //������ջ�������ֵ��ַ���������ջ��
	// puts(number1);
	// printf("%d",numberchar(number1));
	return numberchar(number1);
}
//������ת��һ�����ַ�����ջ��
int innumber(stack *L,int k)
{
	int i;
	char a;
	for(i=10;(k/i)>=10;i*=10);
	for(;i>=10;a=k/i+48,Push(L,a),k%=i,i/=10);
	a=k+48;
	Push(L,a);
	return 0;
}
//�����*����/�Ļ��Ͱ����ó���
char getachar(stack *L,char *c)
{
	Pop(L,c);
	if(*c=='*'||*c=='/'){return *c;}
	else{Push(L,*c);return 0;}  
}