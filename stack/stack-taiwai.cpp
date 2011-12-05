#include<stdio.h>
#include<stdlib.h>
/*堆疊資料結構*/
struct Stack
{
  int Array[10];//陣列空間
  int Top;//堆疊頂端指標       
};
/*檢查堆疊是否為空*/
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
/*推入資料*/
void push(Stack *Stack1,int x)
{
  Stack1->Top=Stack1->Top+1;
  Stack1->Array[Stack1->Top]=x;         
}
/*彈出資料*/
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
  struct Stack *Stack1=(struct Stack *)malloc(sizeof(struct Stack));//宣告資料結構空間
  Stack1->Top=0;
  push(Stack1,3);//推入3
  push(Stack1,4);//推入4
  push(Stack1,1);//推入1
  push(Stack1,10);//推入10
  printf("%d ",pop(Stack1));//彈出10
  printf("%d ",pop(Stack1));//彈出1
  printf("%d ",pop(Stack1));//彈出4
  printf("%d ",pop(Stack1));
  printf("%d ",pop(Stack1));
  system("pause");   
  
}

