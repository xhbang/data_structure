#include<stdio.h>
#include<stdlib.h>
/*�ѯB�Y�ϽY��*/
struct Stack
{
  int Array[10];//��п��g
  int Top;//�ѯB픶�ָ��       
};
/*�z��ѯB�Ƿ���*/
bool stack_empty(Stack *Stack1)
{
  if(Stack1->Top==0)
  {
    return true;            
  }     
  else
  {
    return false;    
  }
}
/*�����Y��*/
void push(Stack *Stack1,int x)
{
  Stack1->Top=Stack1->Top+1;
  Stack1->Array[Stack1->Top]=x;         
}
/*�����Y��*/
int pop(Stack *Stack1)
{
  if(stack_empty(Stack1))
  {
    printf("underflowing");
  }
  else
  {
    Stack1->Top=Stack1->Top-1;
    return Stack1->Array[Stack1->Top+1];    
  }
         
}
int main()
{
  struct Stack *Stack1=(struct Stack *)malloc(sizeof(struct Stack));//�����Y�ϽY�����g
  Stack1->Top=0;
  push(Stack1,3);//����3
  push(Stack1,4);//����4
  push(Stack1,1);//����1
  push(Stack1,10);//����10
  printf("%d ",pop(Stack1));//����10
  printf("%d ",pop(Stack1));//����1
  printf("%d ",pop(Stack1));//����4
  printf("%d ",pop(Stack1));
  printf("%d ",pop(Stack1));
  system("pause");   
  
}

