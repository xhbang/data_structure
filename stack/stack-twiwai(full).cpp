/*��ջ�Ľṹ����*/
typedef struct { 
  SLink top; �� ��// ջ��ָ�� 
  int length; �� // ջ��Ԫ�ظ���
}Stack;

typedef struct{
	Element data;
	Element* next;
}Slink;

void InitStack ( Stack &S )
{ 
  // ����һ����ջ S
  S.top = NULL; ����// ��ջ��ָ��ĳ�ֵΪ"��" 
  S.length = 0; ����// ��ջ��Ԫ�ظ���Ϊ0
} // InitStack
/*�ܷ���ջ�е�ָ�뷽�򷴹�������ջ�׵�ջ����  
 ���У�����������Ļ���ɾ��ջ��Ԫ��ʱ��Ϊ�޸���ǰ��ָ�룬��Ҫ��ջ��һֱ�ҵ�ջ����*/ 

void Push ( Stack &S, Element e )
{
  // ��ջ��֮�ϲ���Ԫ�� e Ϊ�µ�ջ��Ԫ��
  p = new Slink; ����// ���µĽ��
  if(!p) exit(1);����// �洢����ʧ��
  p -> data = e;
  p -> next = S.top;��// ���ӵ�ԭ����ջ��
  S.top = p; ��������// �ƶ�ջ��ָ��
  ++S.length;�������� // ջ�ĳ�����1
} // Push
/*����ջ�����Ͷ���������"ջ��Ԫ�ظ���"�ĳ�Ա��Ϊ�˱������ջ�ĳ��ȡ�*/

bool Pop ( Stack &S, Element &e )
{ 
  // ��ջ���գ���ɾ��S��ջ��Ԫ�أ��� e ������ֵ��
  // ������ TRUE�����򷵻� FALSE
  if ( !S.top )
    return FALSE; 
    else 
    {
      e = S.top -> data; ����// ����ջ��Ԫ�� 
      q = S.top; 
      S.top = S.top -> next;��// �޸�ջ��ָ�� 
      --S.length; ���������� // ջ�ĳ��ȼ�1 
      delete q;���������� ��// �ͷű�ɾ���Ľ��ռ�
      return TRUE;
    }
} // Pop  