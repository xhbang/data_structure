//���Ա�����Ĵ���ṹ,ȫ����int Ϊ����
//�����Բ��������c,��α���Ա�ʾ���ӽ�C
typedef struct LNode{
	int data;
	struct LNode *next;	
}LNode,*Linklist

//���ҵ�i���ڵ�,ͷ���Ϊ0
int GetItem_L(Linklist L,int i,int &e){
	p = L->next,j = 1;
	while(p && j<i){
		p = p->next;
		++j;
	}
	if(!p || j>i)
		return -1;
	e = p->data;
	return 0;
}

//�ڵ�����ڵ�i֮ǰ����Ԫ��e
int Insert_L(Linklist &L,int i,int e){
	p = L��j = 0;
	while (p && j<i-1){
		p = p->next;
		++j;
	}
	if(!p || j>i-1)
		return -1;
	s = (Linklist)malloc(sizeof(LNode));
	s->data = e;
	s->next = p->next;
	p-next = s;
	return 0;
}Insert_L

//��������ɾ����i��Ԫ��(�ڵ�)
int Delete_L(Linklist &L,int i ,int &e){
	p = L,j = 0;
	while(p && j<i-1){
		p = p->next;
		++j;
	}
	if(!(p->next) || j>i-1)
		return -1;
	q = p->next;
	p->next = q->next;
	e = p->data;
	//��Ҳ�Ǻ���Ҫ��
	free(q);
	return 0;
}

//������������

void Create_L(Linklist L,int n){
	 L = (Linklist)malloc(sizeof(LNode));
	 L->next = NULL;
	 for(i = n;i>0;--i){
		p=(Linklist)malloc(sizeof(LNode));
		scanf(&p->data);
		p->next = L->next;
		L->next = p;
		return 0;
	 }
}

//2�����ĺϲ�
void Mergelist_L(Linklist &La,Linklist &Lb,Linklist &Lc){
	pa = La->next;
	pb = Lb->next;

	//????
	while (pa && pb){
		if(pa->data <= pb->data){
			pc->next = pa;
			pc = pa;
			pa = pa->next;
		}
		else{
			pc->next = pb;
			pc = pb;
			pb = pa->next;
		}
	}
	pc->next = pa?pa:pb;
	//!!!!!!!!!!!!!!!!!!
	free(Lb);
	return 0;
}Mergelist_L

