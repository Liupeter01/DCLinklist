#include"DCList.h"

LinkNode* CreateNode(ElemType x)		//�ڵ㴴������
{
		  LinkNode* s = (LinkNode*)malloc(sizeof(LinkNode));
		  assert(s != NULL);
		  s->data = x;
		  s->next = s->prior = NULL;
		  return s;
}

void DisplayLinkList(LinkNode* s)			  //ѭ��˫�����Ԫ�����
{
		  LinkNode* p = s->next;	  //����ͷ���
		  while (p != s)
		  {
					printf("%d<--->", p->data);
					p = p->next;
		  }
		  printf("END\n");
}

LinkNode* LocateElemByNum(DCList* SL, ElemType key)//����Ԫ��
{
		  LinkNode* p = SL->first->next;
		  while (p != SL->first && p->data != key)					  //��Ϊͷ���
		  {
					p = p->next;
		  }
		  return p;
}

void InitDCList(DCList* SL)			//ѭ����ʼ��
{
		  SL->last = SL->first = (LinkNode*)malloc(sizeof(LinkNode));			//��ʼ��ͷ���
		  assert(SL->first != NULL);
		  SL->last->next = SL->first;			  //last����һ�����ָ��ͷ���
		  SL->first->prior = SL->first;			  //first��ͷ���Ҫָ��ͷ
		  SL->amount = 0;	  //��СΪ0
}

void DCListPushBack(DCList* SL)	//ѭ��˫�����β�巨
{
		  if (SL == NULL)					//������û�б���ʼ��
		  {
					InitDCList(SL);
		  }
		  ElemType item = 0;
		  printf("��������Ҫͨ��β�巨���������(-1��������):>");
		  while (scanf("%d", &item) && item != -1)
		  {
					LinkNode* s = CreateNode(item);
					s->next = SL->last->next;		  //β���ڵ�next����ͷ������γ�ѭ���ṹ
					SL->first->prior = s;
					s->prior = SL->last;
					SL->last->next = s;
					SL->last = s;				  //s��Ϊ���һ�����
					SL->amount++;					//�����������
		  }
}

void DCListPushFront(DCList* SL)//ѭ��˫�����ͷ�巨
{
		  if (SL == NULL)					//������û�б���ʼ��
		  {
					InitDCList(SL);
		  }
		  printf("��������Ҫͨ��ͷ�巨���������(-1��������):>");
		  ElemType item = 0;
		  while (scanf("%d", &item) && item != -1)
		  {
					LinkNode* s = CreateNode(item);
					if (SL->first->next == NULL && SL->amount == 0)			  //û����Ԫ�ڵ�
					{
							  SL->last = s;	//���ֻ��һ����Ԫ��㣬��ǰ��Ԫ�ڵ�Ϊβ���
							  SL->last->prior = SL->first;			//s����ǰ�����Ϊͷ���
							  SL->last->next = SL->first;			  //β���ڵ�next����ͷ������γ�ѭ���ṹ
							  SL->first->prior = SL->last;			//ͷ���ڵ�prior����β������γ�ѭ���ṹ
					}
					else									//����Ԫ�ڵ�
					{
							  SL->first->next->prior = s;			//��Ԫ�ڵ��ǰ�����Ϊs
							  s->next = SL->first->next;	//ԭ�ȵ���Ԫ���Ϊs�ĺ�̽��
							  s->prior = SL->first;
					}
					SL->first->next = s;					  //sΪ�µ���Ԫ�ڵ�
					SL->amount++;					//��������
		  }
}

void DCListInsertBackByPos(DCList* SL, int pos, ElemType e)		  //ѭ��˫������λ��β��
{
		  if (SL == NULL || SL->amount == 0)
{
					printf("����ĳ���Ϊ�գ��޷����в������\n");
					return;
		  }
		  if (pos <0 || pos>SL->amount)
		  {
					printf("�������Ҫ�����λ�÷Ƿ����޷����в������\n");
					return;
		  }
		  LinkNode* pcur = NULL;					  //��ǰ���
		  LinkNode* pnext = SL->first->next;	  //��̽��
		  int counter = 0;
		  while (pnext != SL->first && counter++ != pos)
		  {
					pcur = pnext;
					pnext = pnext->next;
		  }
		  LinkNode* s = CreateNode(e);
		  if (pnext == NULL)				//p����λ��Ϊ��
		  {
					pcur->next = s;
					s->prior = pcur;
					s->next = SL->first;		  //β���ڵ�next����ͷ������γ�ѭ���ṹ
					SL->last = s;
					SL->first->prior = SL->last;  //ͷ���ڵ�prior����β������γ�ѭ���ṹ
		  }
		  else
		  {
					pcur->next = s;
					s->next = pnext;
					pnext->prior = s;
					s->prior = pcur;
		  }
		  SL->amount++;					//��������
}

void DCListPopFront(DCList* SL)			//ѭ��˫�����ͷ��ɾ��
{
		  if (SL->amount == 0)					  //�����ڽڵ�
		  {
					printf("����ĳ���Ϊ�գ��޷�����ɾ������\n");
					return;
		  }
		  else
		  {
					LinkNode* p = SL->first->next;	//������Ԫ�ڵ�
					if (p->next == NULL)					//��Ԫ�ڵ㼴Ϊ���һ�����
					{
							  free(p);
							  SL->last = SL->first;			//β���ָ��ͷ���
							  SL->first->prior = SL->last;//ͷ���ڵ�prior����β������γ�ѭ���ṹ
							  SL->last->next = SL->first; //β���ڵ�next����ͷ������γ�ѭ���ṹ
					}
					else
					{
							  SL->first->next = p->next;	//������ǰ��Ԫ�ڵ�
							  p->next->prior = SL->first;			  //��Ԫ�ڵ��̵�ǰ��ָ��ͷ���
							  free(p);
					}
					SL->amount--;
		  }
}

void DCListPopBack(DCList* SL)		//ѭ��˫�����β��ɾ��
{
		  if (SL->amount == 0)					  //�����ڽڵ�
		  {
					printf("����ĳ���Ϊ�գ��޷�����ɾ������\n");
					return;
		  }
		  else
		  {
					LinkNode* pre = SL->last->prior;		//����������ǰ��
					if (SL->first->next == SL->last)					//ֻʣ��һ��ͷ�����
					{
							  free(SL->last);
							  SL->last = SL->first;			//β���ָ��ͷ���
							  SL->first->prior = SL->last;//ͷ���ڵ�prior����β������γ�ѭ���ṹ
							  SL->last->next = SL->first; //β���ڵ�next����ͷ������γ�ѭ���ṹ
					}
					else
					{
							  free(SL->last);
							  SL->last = pre;
							  SL->last->next = SL->first; //β���ڵ�next����ͷ������γ�ѭ���ṹ
							  SL->first->prior = SL->last;//ͷ���ڵ�prior����β������γ�ѭ���ṹ
					}
					SL->amount--;
		  }
}

BOOL DCListDeleteByPos(DCList* SL, int pos, ElemType* e)			//ѭ��˫�����ͨ��λ��ɾ��
{
		  if (SL == NULL || SL->amount == 0)
		  {
					printf("����ĳ���Ϊ�գ��޷�����ɾ������\n");
					return FALSE;
		  }
		  if (pos <0 || pos>SL->amount)
		  {
					printf("�������Ҫɾ����λ�÷Ƿ����޷�����ɾ������\n");
					return FALSE;
		  }
		  LinkNode* pcurr = SL->first->next;	  //��ǰ���
		  int counter = 1;
		  while (pcurr != SL->first && counter++ != pos)
		  {
					pcurr = pcurr->next;
		  }
		  if (pcurr != NULL)
		  {
					LinkNode* pnext = pcurr->next;		  //��̽ڵ�
					LinkNode* pre = pcurr->prior;		  //ǰ���ڵ�
					*e = pcurr->data;
					if (pnext == NULL)			  //��ɾ���Ľ��Ϊ���һ�����
					{
							  SL->last = pre;
							  SL->last->next = SL->first; //β���ڵ�next����ͷ������γ�ѭ���ṹ
							  SL->first->prior = SL->last;//ͷ���ڵ�prior����β������γ�ѭ���ṹ
					}
					else
					{
							  pre->next = pnext;
							  pnext->prior = pre;
					}
					free(pcurr);
					SL->amount--;
					return TRUE;
		  }
		  else
		  {
					return FALSE;
		  }
}

BOOL DCListDeleteByNum(DCList* SL, ElemType key, ElemType* e)		//ѭ��˫�����ͨ����ֵɾ��
{
		  if (SL == NULL || SL->amount == 0)
		  {
					printf("����ĳ���Ϊ�գ��޷�����ɾ������\n");
					return FALSE;
		  }
		  LinkNode* pcurr = LocateElemByNum(SL, key);
		  if (pcurr != NULL)
		  {
					*e = pcurr->data;
					LinkNode* pnext = pcurr->next;		  //��̽ڵ�
					LinkNode* pre = pcurr->prior;		  //ǰ���ڵ�
					if (pnext == NULL)			  //��ɾ���Ľ��Ϊ���һ�����
					{
							  SL->last = pre;
							  SL->last->next = SL->first; //β���ڵ�next����ͷ������γ�ѭ���ṹ
							  SL->first->prior = SL->last;//ͷ���ڵ�prior����β������γ�ѭ���ṹ
					}
					else
					{
							  pre->next = pnext;
							  pnext->prior = pre;
					}
					free(pcurr);
					SL->amount--;
					return TRUE;
		  }
		  else
		  {
					return FALSE;
		  }
}

void Swap(ElemType* a1, ElemType* a2)
{
		  ElemType temp = *a1;
		  *a1 = *a2;
		  *a2 = temp;
}

void  DCListSort(DCList* list, LinkNode* left, LinkNode* right)		//ѭ������
{
		  if (list == NULL)
		  {
					printf("ѭ������Ϊ�ձ�û��Ԫ�أ��޷�����ɾ��\n");
					return;
		  }
		  if (list->amount == 0 || list->amount == 1)
		  {
					return;
		  }
		  if (left != list->first && right != NULL)					  //��ʼ��left��㲻������ͷ���
		  {
					LinkNode* pre = NULL;					//��¼ǰ�����
					LinkNode* islow = left;		  //����ָ��
					LinkNode* jfast = islow->next;				//����ָ��
					while (jfast != list->first)			//������ѭ���������ѭ������ͣ����Ϊͷ���
					{
							  if (islow->data > jfast->data)
							  {
										pre = islow;
										islow = islow->next;
										Swap(&(islow->data), &(jfast->data));
							  }
							  jfast = jfast->next;
					}
					Swap(&(left->data), &(islow->data));
					DCListSort(list, left, pre);
					DCListSort(list, islow->next, right);
		  }
}

void DCListDistroy(DCList* SL)					  //ѭ������Ĵݻ�
{

}

void DCListClear(DCList* SL)	//ѭ����������
{

}

void DCListReverse(DCList* SL)	//ѭ������ķ�ת
{
		  if (SL == NULL)
		  {
					printf("˫����û�б�����������ʧ��\n");
					return;
		  }
		  if (SL->amount == 0 || SL->amount == 1)
		  {
					return;
		  }
		  LinkNode* p = SL->first->next;		  //��Ԫ�ڵ�
		  SL->last = p;					//��ʱ����Ԫ�ڵ�Ϊβ���
		  LinkNode* pnext = p->next;
		  while (pnext != SL->first)			  //pnext������ѭ�������ͷ���
		  {
					LinkNode* pcur = p;
					LinkNode* next = pnext;
					p = pnext;
					pnext = pnext->next;
					pcur->prior = next;			  //�ı�ڵ�˳��
					next->next = pcur;			  //�ı���˳��
		  }
		  SL->first->next = p;
		  SL->last->next = SL->first;//β���ڵ�next����ͷ������γ�ѭ���ṹ
		  SL->first->prior = SL->last;//ͷ���ڵ�prior����β������γ�ѭ���ṹ
}