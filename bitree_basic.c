#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

#define OK 1 
#define OVERFLOW -2 
typedef struct BinNode        
{   
    char data; 
    struct BinNode    *lchild,*rchild; 
} BinNode, *BinTree; 
 
int CreateBinTree(BinTree *Tree) 
{ 
    char ch; 
    scanf("%c",&ch); 
    if(ch == '.')  
        (*Tree) = NULL; 
    else
    { 
        if(!((*Tree) = (BinTree)malloc(sizeof(BinNode))))  
            exit(OVERFLOW); 
        (*Tree)->data = ch; 
        CreateBinTree(&((*Tree)->lchild)); 
        CreateBinTree(&((*Tree)->rchild)); 
    } 
    return (OK);  
}/*CreateBiTree*/ 
 
int depth(BinTree T) 
{ 
    int n,n1,n2; 
    if(!T) 
        n=0; 
    else 
    { 
        n1=depth(T->lchild); 
        n2=depth(T->rchild); 
        n=1+(n1>n2?n1:n2); 
    } 
    return n; 
} 
 
int  leaf(BinTree T) 
{ 
    int n1,n2; 
    if(!T) return 0; 
    else if((!T->lchild) &&  (!T->rchild))return 1; 
    else 
    { 
         n1=leaf(T->lchild); 
         n2=leaf(T->rchild); 
         return(n1+n2); 
    } 
} 
 
void main()         
{   
    BinTree T=NULL; 
    printf("BEGIN\n"); 
 
    CreateBinTree(&T);             
    printf("END\n"); 
    printf("DEPTH\n"); 
    printf("%d\n",depth(T)); 
    printf("LEAF\n"); 
    printf("%d\n",leaf(T)); 
}
