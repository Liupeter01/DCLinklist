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
		  struct	LinkNode* prior;	//前驱结点
		  struct LinkNode* next;		//后继节点
}LinkNode;

typedef struct DCList
{
		  LinkNode* first;				//头结点
		  LinkNode* last;					//尾结点
		  int amount;
}DCList;

LinkNode* CreateNode(ElemType x);		//节点创建方法
void DisplayLinkList(LinkNode* s);				  //循环双链表的元素输出
LinkNode* LocateElemByNum(DCList* SL, ElemType key);//查找元素

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void InitDCList(DCList* SL);			//循环初始化
void  DCListSort(DCList* list, LinkNode* left, LinkNode* right);			//循环排序
void DCListDistroy(DCList* SL);					  //循环链表的摧毁
void DCListClear(DCList* SL);			//循环链表的清空
void DCListReverse(DCList* SL);			//循环链表的反转

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DCListPushBack(DCList* SL);	//循环双链表的尾插法
void DCListPushFront(DCList* SL);//循环双链表的头插法
void DCListInsertBackByPos(DCList* SL, int pos, ElemType e);		  //循环双链表按照位序尾插

//////////////////////////////////////////////////////////删除系列///////////////////////////////////////////////////
void DCListPopFront(DCList* SL);			//循环双链表的头部删除
void DCListPopBack(DCList* SL);		//循环双链表的尾部删除
BOOL DCListDeleteByPos(DCList* SL,int pos,ElemType *e);			//循环双链表的通过位序删除
BOOL DCListDeleteByNum(DCList* SL,ElemType key,ElemType *e);			//循环双链表的通过数值删除