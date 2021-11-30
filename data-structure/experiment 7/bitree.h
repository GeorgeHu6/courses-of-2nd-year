/* bitree.h ��������˳��洢��ʾ */

#ifndef BITREE_H_INCLUDED
#define BITREE_H_INCLUDED


/* ����ͷ�ļ� */
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>

#define TElemType char
#define MAX_TREE_SIZE 100//���������������

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0

//Status��Ϊ������������ʹ��, ��ֵ�Ǻ������״̬���루OK��ERROR��
typedef int Status;
typedef int Boolean;

typedef TElemType SqBiTree[MAX_TREE_SIZE];//0�ŵ�Ԫ�洢�����
typedef int QElemType;

/* ������ڲ�level,���ڱ��������order������1-based (��������������) */
typedef struct {
    int level, order;
} position;

typedef struct QNode {
    QElemType data;
    QNode *next;
} *QueuePtr;

struct LinkQueue {
    QueuePtr front, rear;
};

/* ��ʼ�������� */
extern void InitBiTree(SqBiTree T);
/* ��˳��洢�ṹ�У����/���ٶ������������������³�ʼ�� */
#define ClearBiTree InitBiTree
#define DestroyBiTree InitBiTree

/* �������������, ���������T */
extern void CreateBiTree(SqBiTree T);


/* �ж�T�Ƿ�Ϊ�� */
extern Status BiTreeEmpty(const SqBiTree T);
/* ��T����� */
int BiTreeDepth(SqBiTree const T);
/* �������������ֵ */
extern TElemType Root(SqBiTree T);


/* ��ȡT��λ��e��Ӧ����ֵ */
extern TElemType Value(SqBiTree T, position e);
/* �޸�T��λ��e��Ӧ����ֵ */
extern Status Assign(SqBiTree T, position e, TElemType value);


/* ����ֵΪe�Ľ�㲢�����丸����ֵ */
extern TElemType Parent(SqBiTree T, TElemType e);
/* ����ֵΪe�Ľ�㲢���������ӽ���ֵ */
extern TElemType LeftChild(SqBiTree T, TElemType e);
/* ����ֵΪe�Ľ�㲢���������ӽ���ֵ */
extern TElemType RightChild(SqBiTree T, TElemType e);
/* ����ֵΪe���ҽ�㲢���������ֵܽ���ֵ */
extern TElemType LeftSibling(SqBiTree T, TElemType e);
/* ����ֵΪe�����㲢���������ֵܽ���ֵ */
extern TElemType RightSibling(SqBiTree T, TElemType e);


/* �Ѷ�����Q��jΪ��������������T��i����� */
void Move(SqBiTree Q, int j, SqBiTree T, int i);
/* ����LRΪ0��1,p��ָ����ԭ������������ȳ�ΪC�����������ٲ���CΪT��p��ָ������������� */
extern void InsertChild(SqBiTree T, TElemType p, int LR, SqBiTree c);
/* ����LRΪ0��1,ɾ��T��λ��p�������������*/
extern Status DeleteChild(SqBiTree T, position p, int LR);


/* ������������غ��� */
/* ���ʽڵ㲢��� */
void VisitFunc(TElemType e);
/* ����ݹ����T */
extern void PreOrderTraverse(SqBiTree T);
/* ����ݹ����T */
extern void InOrderTraverse(SqBiTree T);
/* ����ݹ����T */
extern void PostOrderTraverse(SqBiTree T);
/* ����ݹ����T */
extern void LevelOrderTraverse(SqBiTree T);
/* ����ݹ����T,���ֲ���� */
extern void Print(SqBiTree T);


/* ���в������� */
/* ����һ���ն���Q */
extern Status InitQueue(LinkQueue &Q);
/* ���ٶ���Q */
extern Status DestroyQueue(LinkQueue &Q);
/* ��e��ӵ�Q�� */
extern Status EnQueue(LinkQueue &Q, QElemType e);
/* ��QΪ�ն���,�򷵻�TRUE,���򷵻�FALSE */
extern Boolean QueueEmpty(LinkQueue Q);
/* ��Q���г��Ӳ�����ʹ��e������ӵ�Ԫ��ֵ */
extern Status DeQueue(LinkQueue &Q, QElemType &e);

#endif // BITREE_H_INCLUDED