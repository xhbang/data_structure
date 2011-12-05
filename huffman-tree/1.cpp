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
    printf(" ");

    OutputWeight(Data,strlen(Data),
                 &WhatLetter,
                 &Weight,
                 &Count);

    HuffmanCoding(&HT,&HC,Weight,Count);

    printf(" Letter Weight Code ");
    for(i=0;i<Count;i++)
    {
        printf(" %c ",WhatLetter[i]);
        printf("%d ",Weight[i]);
        printf("%s ",HC[i+1]);
    }
    printf(" ");
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
    cd[Count-1]='