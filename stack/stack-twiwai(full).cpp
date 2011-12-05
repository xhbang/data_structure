/*链栈的结构定义*/
typedef struct { 
  SLink top; 　 　// 栈顶指针 
  int length; 　 // 栈中元素个数
}Stack;

typedef struct{
	Element data;
	Element* next;
}Slink;

void InitStack ( Stack &S )
{ 
  // 构造一个空栈 S
  S.top = NULL; 　　// 设栈顶指针的初值为"空" 
  S.length = 0; 　　// 空栈中元素个数为0
} // InitStack
/*能否将链栈中的指针方向反过来，从栈底到栈顶？  
 不行，如果反过来的话，删除栈顶元素时，为修改其前驱指针，需要从栈底一直找到栈顶。*/ 

void Push ( Stack &S, Element e )
{
  // 在栈顶之上插入元素 e 为新的栈顶元素
  p = new Slink; 　　// 建新的结点
  if(!p) exit(1);　　// 存储分配失败
  p -> data = e;
  p -> next = S.top;　// 链接到原来的栈顶
  S.top = p; 　　　　// 移动栈顶指针
  ++S.length;　　　　 // 栈的长度增1
} // Push
/*在链栈的类型定义中设立"栈中元素个数"的成员是为了便于求得栈的长度。*/

bool Pop ( Stack &S, Element &e )
{ 
  // 若栈不空，则删除S的栈顶元素，用 e 返回其值，
  // 并返回 TRUE；否则返回 FALSE
  if ( !S.top )
    return FALSE; 
    else 
    {
      e = S.top -> data; 　　// 返回栈顶元素 
      q = S.top; 
      S.top = S.top -> next;　// 修改栈顶指针 
      --S.length; 　　　　　 // 栈的长度减1 
      delete q;　　　　　 　// 释放被删除的结点空间
      return TRUE;
    }
} // Pop  