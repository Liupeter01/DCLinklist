#include"DCList.h"

LinkNode* CreateNode(ElemType x)		//节点创建方法
{
		  LinkNode* s = (LinkNode*)malloc(sizeof(LinkNode));
		  assert(s != NULL);
		  s->data = x;
		  s->next = s->prior = NULL;
		  return s;
}

void DisplayLinkList(LinkNode* s)			  //循环双链表的元素输出
{
		  LinkNode* p = s->next;	  //跳过头结点
		  while (p != s)
		  {
					printf("%d<--->", p->data);
					p = p->next;
		  }
		  printf("END\n");
}

LinkNode* LocateElemByNum(DCList* SL, ElemType key)//查找元素
{
		  LinkNode* p = SL->first->next;
		  while (p != SL->first && p->data != key)					  //不为头结点
		  {
					p = p->next;
		  }
		  return ((p == SL->first) ? NULL : p); //到达了头结点没有找到
}

void InitDCList(DCList* SL)			//循环初始化
{
		  SL->last = SL->first = (LinkNode*)malloc(sizeof(LinkNode));			//初始化头结点
		  assert(SL->first != NULL);
		  SL->last->next = SL->first;			  //last的下一个结点指向头结点
		  SL->first->prior = SL->first;			  //first的头结点要指向头
		  SL->amount = 0;	  //大小为0
}

void DCListPushBack(DCList* SL)	//循环双链表的尾插法
{
		  if (SL == NULL)					//该链表没有被初始化
		  {
					InitDCList(SL);
		  }
		  ElemType item = 0;
		  printf("请输入需要通过尾插法插入的数据(-1结束输入):>");
		  while (scanf("%d", &item) && item != -1)
		  {
					LinkNode* s = CreateNode(item);
					s->next = SL->last->next;		  //尾部节点next链接头部结点形成循环结构
					SL->first->prior = s;
					s->prior = SL->last;
					SL->last->next = s;
					SL->last = s;				  //s作为最后一个结点
					SL->amount++;					//结点数增加了
		  }
}

void DCListPushFront(DCList* SL)//循环双链表的头插法
{
		  if (SL == NULL)					//该链表没有被初始化
		  {
					InitDCList(SL);
		  }
		  printf("请输入需要通过头插法插入的数据(-1结束输入):>");
		  ElemType item = 0;
		  while (scanf("%d", &item) && item != -1)
		  {
					LinkNode* s = CreateNode(item);
					if (SL->first->next == NULL && SL->amount == 0)			  //没有首元节点
					{
							  SL->last = s;	//如果只有一个首元结点，则当前首元节点为尾结点
							  SL->last->prior = SL->first;			//s结点的前驱结点为头结点
							  SL->last->next = SL->first;			  //尾部节点next链接头部结点形成循环结构
							  SL->first->prior = SL->last;			//头部节点prior链接尾部结点形成循环结构
					}
					else									//有首元节点
					{
							  SL->first->next->prior = s;			//首元节点的前驱结点为s
							  s->next = SL->first->next;	//原先的首元结点为s的后继结点
							  s->prior = SL->first;
					}
					SL->first->next = s;					  //s为新的首元节点
					SL->amount++;					//数量自增
		  }
}

void DCListInsertBackByPos(DCList* SL, int pos, ElemType e)		  //循环双链表按照位序尾插
{
		  if (SL == NULL || SL->amount == 0)
{
					printf("链表的长度为空，无法进行插入操作\n");
					return;
		  }
		  if (pos <0 || pos>SL->amount)
		  {
					printf("输入的需要插入的位置非法，无法进行插入操作\n");
					return;
		  }
		  LinkNode* pcur = NULL;					  //当前结点
		  LinkNode* pnext = SL->first->next;	  //后继结点
		  int counter = 0;
		  while (pnext != SL->first && counter++ != pos)
		  {
					pcur = pnext;
					pnext = pnext->next;
		  }
		  LinkNode* s = CreateNode(e);
		  if (pnext == NULL)				//p所在位置为空
		  {
					pcur->next = s;
					s->prior = pcur;
					s->next = SL->first;		  //尾部节点next链接头部结点形成循环结构
					SL->last = s;
					SL->first->prior = SL->last;  //头部节点prior链接尾部结点形成循环结构
		  }
		  else
		  {
					pcur->next = s;
					s->next = pnext;
					pnext->prior = s;
					s->prior = pcur;
		  }
		  SL->amount++;					//数量自增
}

void DCListPopFront(DCList* SL)			//循环双链表的头部删除
{
		  if (SL->amount == 0)					  //不存在节点
		  {
					printf("链表的长度为空，无法进行删除操作\n");
					return;
		  }
		  else
		  {
					LinkNode* p = SL->first->next;	//保存首元节点
					if (p->next == NULL)					//首元节点即为最后一个结点
					{
							  free(p);
							  SL->last = SL->first;			//尾结点指向头结点
							  SL->first->prior = SL->last;//头部节点prior链接尾部结点形成循环结构
							  SL->last->next = SL->first; //尾部节点next链接头部结点形成循环结构
					}
					else
					{
							  SL->first->next = p->next;	//跳过当前首元节点
							  p->next->prior = SL->first;			  //首元节点后继的前键指向头结点
							  free(p);
					}
					SL->amount--;
		  }
}

void DCListPopBack(DCList* SL)		//循环双链表的尾部删除
{
		  if (SL->amount == 0)					  //不存在节点
		  {
					printf("链表的长度为空，无法进行删除操作\n");
					return;
		  }
		  else
		  {
					LinkNode* pre = SL->last->prior;		//保存最后结点的前驱
					if (SL->first->next == SL->last)					//只剩下一个头结点了
					{
							  free(SL->last);
							  SL->last = SL->first;			//尾结点指向头结点
							  SL->first->prior = SL->last;//头部节点prior链接尾部结点形成循环结构
							  SL->last->next = SL->first; //尾部节点next链接头部结点形成循环结构
					}
					else
					{
							  free(SL->last);
							  SL->last = pre;
							  SL->last->next = SL->first; //尾部节点next链接头部结点形成循环结构
							  SL->first->prior = SL->last;//头部节点prior链接尾部结点形成循环结构
					}
					SL->amount--;
		  }
}

BOOL DCListDeleteByPos(DCList* SL, int pos, ElemType* e)			//循环双链表的通过位序删除
{
		  if (SL == NULL || SL->amount == 0)
		  {
					printf("链表的长度为空，无法进行删除操作\n");
					return FALSE;
		  }
		  if (pos <0 || pos>SL->amount)
		  {
					printf("输入的需要删除的位置非法，无法进行删除操作\n");
					return FALSE;
		  }
		  LinkNode* pcurr = SL->first->next;	  //当前结点
		  int counter = 1;
		  while (pcurr != SL->first && counter++ != pos)
		  {
					pcurr = pcurr->next;
		  }
		  if (pcurr != NULL)
		  {
					LinkNode* pnext = pcurr->next;		  //后继节点
					LinkNode* pre = pcurr->prior;		  //前驱节点
					*e = pcurr->data;
					if (pnext == NULL)			  //该删除的结点为最后一个结点
					{
							  SL->last = pre;
							  SL->last->next = SL->first; //尾部节点next链接头部结点形成循环结构
							  SL->first->prior = SL->last;//头部节点prior链接尾部结点形成循环结构
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

BOOL DCListDeleteByNum(DCList* SL, ElemType key, ElemType* e)		//循环双链表的通过数值删除
{
		  if (SL == NULL || SL->amount == 0)
		  {
					printf("链表的长度为空，无法进行删除操作\n");
					return FALSE;
		  }
		  LinkNode* pcurr = LocateElemByNum(SL, key);
		  if (pcurr != NULL)
		  {
					*e = pcurr->data;
					LinkNode* pnext = pcurr->next;		  //后继节点
					LinkNode* pre = pcurr->prior;		  //前驱节点
					if (pnext == NULL)			  //该删除的结点为最后一个结点
					{
							  SL->last = pre;
							  SL->last->next = SL->first; //尾部节点next链接头部结点形成循环结构
							  SL->first->prior = SL->last;//头部节点prior链接尾部结点形成循环结构
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

void  DCListSort(DCList* list, LinkNode* left, LinkNode* right)		//循环排序
{
		  if (list == NULL)
		  {
					printf("循环链表为空表，没有元素，无法进行删除\n");
					return;
		  }
		  if (list->amount == 0 || list->amount == 1)
		  {
					return;
		  }
		  if (left != list->first && right != NULL)					  //开始的left结点不允许是头结点
		  {
					LinkNode* pre = NULL;					//记录前驱结点
					LinkNode* islow = left;		  //慢速指针
					LinkNode* jfast = islow->next;				//快速指针
					while (jfast != list->first)			//由于是循环链表因此循环的暂停条件为头结点
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

void DCListDistroy(DCList* SL)					  //循环链表的摧毁
{
		  if (SL == NULL)
		  {
					printf("双链表没有被创建，操作失败\n");
					return;
		  }
		  LinkNode* p = SL->first->next;
		  while (p != SL->first)
		  {
					LinkNode* ptemp = p;
					p = p->next;
					free(ptemp);
		  }
		  free(SL->first);				//删除头结点
		  SL->amount = 0;
}

void DCListClear(DCList* SL)	//循环链表的清空不需要删除头结点
{
		  if (SL == NULL)
		  {
					printf("双链表没有被创建，操作失败\n");
					return;
		  }
		  LinkNode* p = SL->first->next;
		  while (p != SL->first)
		  {
					LinkNode* ptemp = p;
					p = p->next;
					free(ptemp);
		  }
		  SL->amount = 0;
}

void DCListReverse(DCList* SL)	//循环链表的反转
{
		  if (SL == NULL)
		  {
					printf("双链表没有被创建，操作失败\n");
					return;
		  }
		  if (SL->amount == 0 || SL->amount == 1)
		  {
					return;
		  }
		  LinkNode* p = SL->first->next;		  //首元节点
		  SL->last = p;					//此时的首元节点为尾结点
		  LinkNode* pnext = p->next;
		  while (pnext != SL->first)			  //pnext不到达循环链表的头结点
		  {
					LinkNode* pcur = p;
					LinkNode* next = pnext;
					p = pnext;
					pnext = pnext->next;
					pcur->prior = next;			  //改变节点顺序
					next->next = pcur;			  //改变结点顺序
		  }
		  SL->first->next = p;
		  SL->last->next = SL->first;//尾部节点next链接头部结点形成循环结构
		  SL->first->prior = SL->last;//头部节点prior链接尾部结点形成循环结构
}