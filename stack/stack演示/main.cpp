#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"zhan1.h"
void main()
{
	printf("            -----------栈的功能演示：-----------------08/12/5\n");
	char m[10]={'a','b','c','d','e','f','g'};
	char m1;
	int j;
	printf("please input the char:\n");
	for(j=0;m[j]!='\0';printf(" %c " ,m[j]),j++);
	stack T;
	printf("\n初始栈T：\n");
	Init(&T);
	printf("元素入栈T：\n");
	j=0;
	if(StackEmpty(&T))
	{
		printf("栈T存在！！\n");
		while(m[j]!='\0')
		{
			Push(&T,m[j]);
			j++;
		}
		printf("元素出栈：\n");
		printf("\n栈T长度为：%d",stacklength(&T));
		ClearStack(&T);
		printf("栈T长度为：%d",stacklength(&T));
		printf("\n摧毁栈!!\n");
		Destory(&T);
	}
	else
	{
		printf("此栈不存在！！");
	}


	printf("\r\n-----------The simple example for formular evaluation---------08/12/5\n\n");
	char formular[25];
	char number1[5];
	int i=0;
	int tag=0; //判断是否是首次执行
	int b=0;
	int k1=0,k2=0;
	int k;
	double d=0,h=0;  //存表达式出现负数小数情况
	char a;
	stack L;   //临时栈，存暂未被取用的符号
	stack S;   //存后缀表达式
	Init(&L);
	Init(&S);
	printf("please input formular(The number must less than 10):\n");
	gets(formular);
	//将中缀表达式转化成后缀表达式
	while(formular[i]!='\0')
	{ 
		if(is_operator(formular[i]))
		{
			if(tag==0)Push(&L,formular[i]);
			if(formular[i]!=')')
			{
				Pop(&L,&a);
				if(operator_grade(formular[i])<operator_grade(a))
				{
					if(a!='(')Push(&S,a);
					Push(&L,formular[i]);
				}
				else
				{
					Push(&L,a);
					Push(&L,formular[i]);
				}
			}//if(formular[i])!=')')
			else
			{
				for(Pop(&L,&a);(L.cout>0)&&(a!='(');Push(&S,a),Pop(&L,&a));
			}
			tag++;
		}//if(is_operator(formular[i]))
		else
		{
			Push(&S,formular[i]);
		}
		i++;
	}
	//在(后留在栈中的运算符放在
	for(Pop(&L,&a);L.cout>0;Push(&S,a),Pop(&L,&a));
	printf("\nThe postfix fomular is:\n");
	for(i=0;S.cout>0;Pop(&S,&a),formular[i]=a,i++);
	formular[i]='\0';
	b=strlen(formular); //存后缀式的长度
	for(i=b-1;i>=0;printf("%c",formular[i]),i--);
	//算出表达式的值
	i=b-1;
	while(i>=0)
	{
		while(!is_operator(formular[i]))
		{
			Push(&S,formular[i]);
			Push(&S,'!');
			i--;
		}
		Pop(&S,&a);//删除!符号
		if(a!='!')Push(&S,a);
		k1=winnumber(&S,&a,number1);
		Pop(&S,&a);//删除!符号
		if(d)
		{
			h=operad(k1,d,formular[i]);
			d=h;
			if(i==0)printf("\nThe result is：%.3f\n",d);
		}
		else
		{
			k2=winnumber(&S,&a,number1);
			if(is_special_code(formular[i])&&(k2<k1))
			{
				//    printf("\n调用判断是否是/或者-");
				d=operad(k2,k1,formular[i]);
				if(i==0)printf("\nThe result is：%.3f\n",d);
			}
			else
			{
				k=opera(k2,k1,formular[i]);
				if(i==0)printf("\nThe result is：%d\n",k);
				innumber(&S,k);
				Push(&S,'!'); //各个数据隔开标志
			}
		}
		i--;
	}
}
