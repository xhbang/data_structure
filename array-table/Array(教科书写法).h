/* �����˳��洢��ʾ */
#include<stdarg.h> /* ��׼ͷ�ļ����ṩ��va_start��va_arg��va_end�� */
/* ���ڴ�ȡ�䳤������ */
typedef int Status

#define OK 1
#define OVERFLOW 2
#define ERROR 0
#define MAX_ARRAY_DIM 8 /* ��������ά�������ֵΪ8 */
typedef struct
{
	ElemType *base; /* ����Ԫ�ػ�ַ����InitArray���� */
	int dim; /* ����ά�� */
	int *bounds; /* ����ά���ַ����InitArray���� */
	int *constants; /* ����ӳ����������ַ����InitArray���� */
}Array;


* ˳��洢����Ļ�������(5��) */
Status InitArray(Array *A,int dim,...)
{ /* ��ά��dim�͸�ά���ȺϷ���������Ӧ������A��������OK */
	int elemtotal=1,i; /* elemtotal������Ԫ����������ֵΪ1(�۳���) */
	va_list ap;
	if(dim<1||dim>MAX_ARRAY_DIM)
		return ERROR;
	(*A).dim=dim;
	(*A).bounds=(int *)malloc(dim*sizeof(int));
	if(!(*A).bounds)
		exit(OVERFLOW);
	va_start(ap,dim);
	for(i=0;i<dim;++i)
	{
		(*A).bounds[i]=va_arg(ap,int);
		if((*A).bounds[i]<0)
			return UNDERFLOW; /* ��math.h�ж���Ϊ4 */
		elemtotal*=(*A).bounds[i];
	}
	va_end(ap);
	(*A).base=(ElemType *)malloc(elemtotal*sizeof(ElemType));
	if(!(*A).base)
		exit(OVERFLOW);
	(*A).constants=(int *)malloc(dim*sizeof(int));
	if(!(*A).constants)
		exit(OVERFLOW);
	(*A).constants[dim-1]=1;
	for(i=dim-2;i>=0;--i)
		(*A).constants[i]=(*A).bounds[i+1]*(*A).constants[i+1];
	return OK;
}


void DestroyArray(Array *A)
{ /* ��������A */
	if((*A).base)
		free((*A).base);
	if((*A).bounds)
		free((*A).bounds);
	if((*A).constants)
		free((*A).constants);
	(*A).base= (*A).bounds=(*A).constants=NULL;
	(*A).dim=0;
}

Status Locate(Array A,va_list ap,int *off) /* Value()��Assign()���ô˺��� */
{ /* ��apָʾ�ĸ��±�ֵ�Ϸ����������Ԫ����A�е���Ե�ַoff */
	int i,ind;
	*off=0;
	for(i=0;i<A.dim;i++)
	{
		ind=va_arg(ap,int);
		if(ind<0||ind>=A.bounds[i])
			return OVERFLOW;
		*off+=A.constants[i]*ind;
	}
	return OK;
}


Status Value(ElemType *e,Array A,...) /* ��VC++�У�...֮ǰ���ββ������������� */
{ /* ...����Ϊ��ά���±�ֵ�������±�Ϸ�����e����ֵΪA����Ӧ��Ԫ��ֵ */
	va_list ap;
	int off;
	va_start(ap,A);
	if(Locate(A,ap,&off)==OVERFLOW) /* ����Locate() */
		return ERROR;
	*e=*(A.base+off);
	return OK;
}

Status Assign(Array A,ElemType e,...) /* ����A��ֵ���䣬�ʲ���Ҫ* */
{ /* ...����Ϊ��ά���±�ֵ�������±�Ϸ�����e��ֵ����A��ָ����Ԫ�� */
	va_list ap;
	int off;
	va_start(ap,e);
	if(Locate(A,ap,&off)==OVERFLOW) /* ����Locate() */
		return ERROR;
	*(A.base+off)=e;
	return OK;
}

