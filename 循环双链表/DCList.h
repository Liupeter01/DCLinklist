#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<Windows.h>
#include<memory.h>

#pragma warning(disable:6011)

#define ElemType int

typedef struct LinkNode
{
		  ElemType data;
		  struct	LinkNode* prior;	//ǰ�����
		  struct LinkNode* next;		//��̽ڵ�
}LinkNode;

typedef struct DCList
{
		  LinkNode* first;				//ͷ���
		  LinkNode* last;					//β���
		  int amount;
}DCList;

LinkNode* CreateNode(ElemType x);		//�ڵ㴴������
void DisplayLinkList(LinkNode* s);				  //ѭ��˫�����Ԫ�����
LinkNode* LocateElemByNum(DCList* SL, ElemType key);//����Ԫ��

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void InitDCList(DCList* SL);			//ѭ����ʼ��
void  DCListSort(DCList* list, LinkNode* left, LinkNode* right);			//ѭ������
void DCListDistroy(DCList* SL);					  //ѭ������Ĵݻ�
void DCListClear(DCList* SL);			//ѭ����������
void DCListReverse(DCList* SL);			//ѭ������ķ�ת

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DCListPushBack(DCList* SL);	//ѭ��˫�����β�巨
void DCListPushFront(DCList* SL);//ѭ��˫�����ͷ�巨
void DCListInsertBackByPos(DCList* SL, int pos, ElemType e);		  //ѭ��˫������λ��β��

//////////////////////////////////////////////////////////ɾ��ϵ��///////////////////////////////////////////////////
void DCListPopFront(DCList* SL);			//ѭ��˫�����ͷ��ɾ��
void DCListPopBack(DCList* SL);		//ѭ��˫�����β��ɾ��
BOOL DCListDeleteByPos(DCList* SL,int pos,ElemType *e);			//ѭ��˫�����ͨ��λ��ɾ��
BOOL DCListDeleteByNum(DCList* SL,ElemType key,ElemType *e);			//ѭ��˫�����ͨ����ֵɾ��