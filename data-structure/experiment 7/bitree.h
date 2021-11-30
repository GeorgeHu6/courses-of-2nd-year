/* bitree.h 二叉树的顺序存储表示 */

#ifndef BITREE_H_INCLUDED
#define BITREE_H_INCLUDED


/* 常规头文件 */
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>

#define TElemType char
#define MAX_TREE_SIZE 100//二叉树的最大结点数

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0

//Status作为函数返回类型使用, 其值是函数结果状态代码（OK、ERROR）
typedef int Status;
typedef int Boolean;

typedef TElemType SqBiTree[MAX_TREE_SIZE];//0号单元存储根结点
typedef int QElemType;

/* 结点所在层level,及在本层中序号order，都是1-based (按满二叉树计算) */
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

/* 初始化二叉树 */
extern void InitBiTree(SqBiTree T);
/* 在顺序存储结构中，清空/销毁二叉树即将二叉树重新初始化 */
#define ClearBiTree InitBiTree
#define DestroyBiTree InitBiTree

/* 按层序次序输入, 构造二叉树T */
extern void CreateBiTree(SqBiTree T);


/* 判断T是否为空 */
extern Status BiTreeEmpty(const SqBiTree T);
/* 求T的深度 */
int BiTreeDepth(SqBiTree const T);
/* 求二叉树根结点的值 */
extern TElemType Root(SqBiTree T);


/* 获取T中位置e对应结点的值 */
extern TElemType Value(SqBiTree T, position e);
/* 修改T中位置e对应结点的值 */
extern Status Assign(SqBiTree T, position e, TElemType value);


/* 查找值为e的结点并返回其父结点的值 */
extern TElemType Parent(SqBiTree T, TElemType e);
/* 查找值为e的结点并返回其左子结点的值 */
extern TElemType LeftChild(SqBiTree T, TElemType e);
/* 查找值为e的结点并返回其右子结点的值 */
extern TElemType RightChild(SqBiTree T, TElemType e);
/* 查找值为e的右结点并返回其左兄弟结点的值 */
extern TElemType LeftSibling(SqBiTree T, TElemType e);
/* 查找值为e的左结点并返回其右兄弟结点的值 */
extern TElemType RightSibling(SqBiTree T, TElemType e);


/* 把二叉树Q以j为根结点的子树移至T的i结点上 */
void Move(SqBiTree Q, int j, SqBiTree T, int i);
/* 根据LR为0或1,p所指结点的原有左或右子树先成为C的右子树，再插入C为T中p所指结点的左或右子树 */
extern void InsertChild(SqBiTree T, TElemType p, int LR, SqBiTree c);
/* 根据LR为0或1,删除T中位置p结点的左或右子树*/
extern Status DeleteChild(SqBiTree T, position p, int LR);


/* 二叉树遍历相关函数 */
/* 访问节点并输出 */
void VisitFunc(TElemType e);
/* 先序递归遍历T */
extern void PreOrderTraverse(SqBiTree T);
/* 中序递归遍历T */
extern void InOrderTraverse(SqBiTree T);
/* 后序递归遍历T */
extern void PostOrderTraverse(SqBiTree T);
/* 层序递归遍历T */
extern void LevelOrderTraverse(SqBiTree T);
/* 层序递归遍历T,并分层输出 */
extern void Print(SqBiTree T);


/* 队列操作函数 */
/* 构造一个空队列Q */
extern Status InitQueue(LinkQueue &Q);
/* 销毁队列Q */
extern Status DestroyQueue(LinkQueue &Q);
/* 将e入队到Q中 */
extern Status EnQueue(LinkQueue &Q, QElemType e);
/* 若Q为空队列,则返回TRUE,否则返回FALSE */
extern Boolean QueueEmpty(LinkQueue Q);
/* 对Q进行出队操作，使用e保存出队的元素值 */
extern Status DeQueue(LinkQueue &Q, QElemType &e);

#endif // BITREE_H_INCLUDED