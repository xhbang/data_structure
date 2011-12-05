#include<stdio.h> 
#include<stdbool.h> 
#define MAX_STACK_SIZE 100 
#define EXIT_ROW 9 
#define EXIT_COL 9 


int maze[10][10] = { 
	{1,0,1,1,1,1,1,1,1,1}, 
	{1,0,0,1,0,0,0,1,0,1}, 
	{1,0,0,1,0,0,0,1,0,1}, 
	{1,0,0,0,0,1,1,0,0,1}, 
	{1,0,1,1,1,0,0,0,0,1}, 
	{1,0,0,0,1,0,0,0,0,1}, 
	{1,0,1,0,0,0,1,0,0,1}, 
	{1,0,1,1,1,1,1,1,0,1}, 
	{1,1,0,0,0,0,0,0,0,1}, 
	{1,1,1,1,1,1,1,1,0,1}};/*��ʼ���Թ�*/ 
	int mark[10][10] = {0};/*��ʼ����־λ,0����û�߹�,1�����߹�*/ 

	/*����*/ 
	typedef struct{ 
		short int vert; 
		short int horiz; 
	}offsets; 

	offsets move[4] = {{0,1},{1,0},{0,-1},{-1,0}};/*��,��,��,��*/ 


	/*�Թ�����*/ 
	typedef struct { 
		short int row; 
		short int col; 
		short int dir; 
	}element; 

	element stack[MAX_STACK_SIZE]; 


	void path(void); 
	element delete(int* top); 
	void add(int* top,element item); 


	element delete(int* top)/*��ջ,topָ��ջ��Ԫ��*/ 
	{ 
		if(*top == -1) 
		{ 
			printf("stack is empty!\n"); 
		} 
		return stack[(*top)--]; 
	} 


	void add(int* top,element item)/*��ջ*/ 
	{ 
		if(*top >= MAX_STACK_SIZE - 1) 
		{ 
			printf("stack is full!\n"); 
			return; 
		} 
		stack[++*top] = item; 
	} 


	void path(void)/*�Թ�����*/ 
	{ 
		element position; 
		int i,row,col,next_row,next_col,dir,top; 
		_Bool found = 0; 
		mark[1][1] = 1,top = 0;/*��ʼ����־����Ԫ���Լ�ջ*/ 
		stack[0].row = 1,stack[0].col = 1,stack[0].dir = 0; 
		while(top > -1 && !found) 
		{ 
			position = delete(&top);    /*��ջ��Ԫ��ȡ��,*/ 
			row = position.row;            /*�����м����row,col,dir�Ⱥ��ж�*/ 
			col = position.col; 
			dir = position.dir; 
			while(dir < 4 && !found) 
			{ 
				next_row = row + move[dir].vert; 
				next_col = col + move[dir].horiz; 
				if(next_row == EXIT_ROW && next_col == EXIT_COL) 
					found = 1; 
				else if(!maze[next_row][next_col] && !mark[next_row][next_col])/*�ж���һ�����߲���û�߹�,����ջ*/ 
				{ 
					mark[next_row][next_col] = 1; 
					position.row = row; 
					position.col = col; 
					position.dir = ++dir; 
					add(&top,position);/*��������ջ*/ 
					row = next_row;/*����������*/ 
					col = next_col;dir = 0; 
				} 
				else 
					dir++;/*dir<4ʱ,�ı䷽��*/ 
			} 
			if(found)/*�ж��Ƿ��г���*/ 
			{ 
				printf("the path is:\n"); 
				printf("row col\n"); 
				for(i = 0;i <= top;++i) 
					printf("%2d%5d",stack[i].row,stack[i].col); 
				printf("%2d%5d\n",row,col); 
				printf("%2d%5d\n",EXIT_ROW,EXIT_COL); 
			}  
		} 
	} 


	int main(void) 
	{   
		path(); 
		return 0; 
	} 