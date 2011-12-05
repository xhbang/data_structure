霍夫曼树： 带权路径长度达到最小的扩充二叉树即为霍夫曼树。
在霍夫曼树中，权值大的结点离根最近。 
霍夫曼算法 
(1) 由给定的n个权值{w0, w1, w2, …, wn-1}，构造具有n棵扩充二叉树的森林F = {T0, T1, T2, …, Tn-1}，其中每一棵扩充二叉树Ti只有一个带有权值wi的根结点，其左、右子树均为空。
(2) 重复以下步骤, 直到F中仅剩下一棵树为止： 
① 在F中选取两棵根结点的权值最小的扩充二叉树, 做为左、右子树构造一棵新的二叉树。置新的二叉树的根结点的权值为其左、右子树上根结点的权值之和。
② 在F中删去这两棵二叉树。 
③ 把新的二叉树加入F。 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

typedef struct
{
    unsigned int Weight;
    unsigned int Parent;
    unsigned int lChild;
    unsigned int rChild;
}HTNode,*HuffmanTree;

typedef char **HuffmanCode;

int LookFor(char *str,char letter,int count);
void OutputWeight(char *Data,int Length,
                  char **WhatLetter,
                  int **Weight,int *Count);
void HuffmanCoding(HuffmanTree *HT,
                   HuffmanCode *HC,
                   int *Weight,
                   int Count);
void Select(HuffmanTree HT,int Count,int *s1,int *s2);
int main()
{
    HuffmanTree HT;
    HuffmanCode HC; 
    char Data[100];
    char *WhatLetter;
    int *Weight;
    int Count;
    int i;

    printf("Please input the line:");
    /* Example: aaaaaaaaaaaaaabcccccc*/
    scanf("%s",Data);
    printf("\n");

    OutputWeight(Data,strlen(Data),
                 &WhatLetter,
                 &Weight,
                 &Count);

    HuffmanCoding(&HT,&HC,Weight,Count);

    printf(" Letter Weight Code\n");
    for(i=0;i<Count;i++)
    {
        printf(" %c ",WhatLetter[i]);
        printf("%d ",Weight[i]);
        printf("%s\n",HC[i+1]);
    }
    printf("\n");
    getch();
    return 0;
}

void HuffmanCoding(HuffmanTree *HT,
                   HuffmanCode *HC,
                   int *Weight,
                   int Count)
{
    int i;
    int s1,s2;
    int TotalLength;
    HuffmanTree p;
    char* cd;
    unsigned int c;
    unsigned int f;
    int start;

    if(Count<=1) return;
    TotalLength=Count*2-1;
    (*HT)=(HuffmanTree)malloc((TotalLength+1)*sizeof(HTNode));

    p=((*HT)++);
    for(i=1;i<=Count;i++)
    {
        (*HT)[i].Parent=0;
        (*HT)[i].rChild=0;
        (*HT)[i].lChild=0;
        (*HT)[i].Weight=(*Weight);
        Weight++;
    }
    for(i=Count+1;i<=TotalLength;i++)
    {
        (*HT)[i].Weight=0;
        (*HT)[i].Parent=0;
        (*HT)[i].lChild=0;
        (*HT)[i].rChild=0; 
    }
    /*///////////////////Create HuffmanTree////////////////*/
    for(i=Count+1;i<=TotalLength;++i)
    {
        Select((*HT),i-1,&s1,&s2);
       (*HT)[s1].Parent=i;
       (*HT)[s2].Parent=i;
       (*HT)[i].lChild=s1;
       (*HT)[i].rChild=s2;
       (*HT)[i].Weight=(*HT)[s1].Weight+(*HT)[s2].Weight;
    }
    /*///////////////////Output Huffman Code///////////////*/
    (*HC)=(HuffmanCode)malloc((Count+1)*sizeof(char*));
    cd=(char*)malloc(Count*sizeof(char));
    cd[Count-1]='\0';
    for(i=1;i<=Count;++i)
    {
        start=Count-1;
        for(c=i,f=(*HT)[i].Parent;f!=0;c=f,f=(*HT)[f].Parent)
        {
            if((*HT)[f].lChild==c)
                cd[--start]='0';
            else
                cd[--start]='1';
            (*HC)[i]=(char*)malloc((Count-start)*sizeof(char));
            strcpy((*HC)[i],&cd[start]);
        }
    }
}
void Select(HuffmanTree HT,int Count,int *s1,int *s2)
/*/(*s1) is smallest,(*s2) is smaller.*/
{
    int i;
    unsigned int temp1=0;
    unsigned int temp2=0;
    unsigned int temp3;
    for(i=1;i<=Count;i++)
    {
        if(HT[i].Parent==0)
        {
            if(temp1==0)
            {
                temp1=HT[i].Weight;
                (*s1)=i;
            }
            else
            {
                if(temp2==0)
                {
                    temp2=HT[i].Weight;
                    (*s2)=i;
                    if(temp2<temp1)
                    {
                        temp3=temp2;
                        temp2=temp1;
                        temp1=temp3;

                        temp3=(*s2);
                        (*s2)=(*s1);
                        (*s1)=temp3;
                    }
                }
                else
                {
                    if(HT[i].Weight<temp1)
                    {
                        temp2=temp1;
                        temp1=HT[i].Weight;

                        (*s2)=(*s1);
                        (*s1)=i;
                    }
                    if(HT[i].Weight>temp1&&HT[i].Weight<temp2)
                    {
                        temp2=HT[i].Weight;
                        (*s2)=i;
                    }
                }
            }
        }
    }
}

int LookFor(char *str,char letter,int count)
{
    int i;
    for(i=0;i<count;i++)
    {
        if(str[i]==letter) return i;
    }
    return -1;
}
void OutputWeight(char *Data,int Length,
                  char **WhatLetter,
                  int **Weight,int *Count)
{
    int i;
    char* Letter=(char*)malloc(Length);
    int* LetterCount=(int *)malloc(Length);
    int AllCount=0;
    int Index;
    int Sum=0;
    float Persent=0;

    for(i=0;i<Length;i++)
    {
        if(i==0)
        {
            Letter[0]=Data[i];
            LetterCount[0]=1;
            AllCount++;
        }
        else
        {
            Index=LookFor(Letter,Data[i],AllCount);
            if(Index==-1)
            {
                Letter[AllCount]=Data[i];
                LetterCount[AllCount]=1;
                AllCount++;
            }
            else
            {
                LetterCount[Index]++;
            }
        }
    }
    for(i=0;i<AllCount;i++)
    {
        Sum=Sum+LetterCount[i];
    }
    (*Weight)=(int*)malloc(AllCount);
    (*WhatLetter)=(char*)malloc(AllCount);

    for(i=0;i<AllCount;i++)
    {
        Persent=(float)LetterCount[i]/(float)Sum;
        (*Weight)[i]=(int)(1000*Persent);
        (*WhatLetter)[i]=Letter[i];
    }
    (*Count)=AllCount;
} 