#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"zhan1.h"
void main()
{
	printf("            -----------ջ�Ĺ�����ʾ��-----------------08/12/5\n");
	char m[10]={'a','b','c','d','e','f','g'};
	char m1;
	int j;
	printf("please input the char:\n");
	for(j=0;m[j]!='\0';printf(" %c " ,m[j]),j++);
	stack T;
	printf("\n��ʼջT��\n");
	Init(&T);
	printf("Ԫ����ջT��\n");
	j=0;
	if(StackEmpty(&T))
	{
		printf("ջT���ڣ���\n");
		while(m[j]!='\0')
		{
			Push(&T,m[j]);
			j++;
		}
		printf("Ԫ�س�ջ��\n");
		printf("\nջT����Ϊ��%d",stacklength(&T));
		ClearStack(&T);
		printf("ջT����Ϊ��%d",stacklength(&T));
		printf("\n�ݻ�ջ!!\n");
		Destory(&T);
	}
	else
	{
		printf("��ջ�����ڣ���");
	}


	printf("\r\n-----------The simple example for formular evaluation---------08/12/5\n\n");
	char formular[25];
	char number1[5];
	int i=0;
	int tag=0; //�ж��Ƿ����״�ִ��
	int b=0;
	int k1=0,k2=0;
	int k;
	double d=0,h=0;  //����ʽ���ָ���С�����
	char a;
	stack L;   //��ʱջ������δ��ȡ�õķ���
	stack S;   //���׺���ʽ
	Init(&L);
	Init(&S);
	printf("please input formular(The number must less than 10):\n");
	gets(formular);
	//����׺���ʽת���ɺ�׺���ʽ
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
	//��(������ջ�е����������
	for(Pop(&L,&a);L.cout>0;Push(&S,a),Pop(&L,&a));
	printf("\nThe postfix fomular is:\n");
	for(i=0;S.cout>0;Pop(&S,&a),formular[i]=a,i++);
	formular[i]='\0';
	b=strlen(formular); //���׺ʽ�ĳ���
	for(i=b-1;i>=0;printf("%c",formular[i]),i--);
	//������ʽ��ֵ
	i=b-1;
	while(i>=0)
	{
		while(!is_operator(formular[i]))
		{
			Push(&S,formular[i]);
			Push(&S,'!');
			i--;
		}
		Pop(&S,&a);//ɾ��!����
		if(a!='!')Push(&S,a);
		k1=winnumber(&S,&a,number1);
		Pop(&S,&a);//ɾ��!����
		if(d)
		{
			h=operad(k1,d,formular[i]);
			d=h;
			if(i==0)printf("\nThe result is��%.3f\n",d);
		}
		else
		{
			k2=winnumber(&S,&a,number1);
			if(is_special_code(formular[i])&&(k2<k1))
			{
				//    printf("\n�����ж��Ƿ���/����-");
				d=operad(k2,k1,formular[i]);
				if(i==0)printf("\nThe result is��%.3f\n",d);
			}
			else
			{
				k=opera(k2,k1,formular[i]);
				if(i==0)printf("\nThe result is��%d\n",k);
				innumber(&S,k);
				Push(&S,'!'); //�������ݸ�����־
			}
		}
		i--;
	}
}
