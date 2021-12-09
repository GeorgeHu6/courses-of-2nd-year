#include <stdio.h>
#include <stdlib.h>
#define Status int
#define OK 1
#define ERROR 0

//定义数据元素类型
typedef char DATA;

// 定义二叉树结点类型
typedef struct CBT{
    DATA data;//结点数据
    struct CBT *left;//左子树指针
    struct CBT *right;//右子树指针
} CBTType;

typedef CBTType* QElemType;

typedef struct QNode{
    QElemType pt;
    struct QNode *next;
} QNode;

typedef struct LinkQueue {
    QNode *head, *rear;
} *queuePtr;

/* 实现二叉树基本操作：
 * 1. 初始化二叉树、查找结点、添加结点
 * 2. 获取左子树、获取右子树、显示结点数据
 * 3. 计算二叉树深度、清空二叉树、判断空树
 * 4. 遍历二叉树（按层、先序、中序、后序）
 */

/* 初始化二叉树，即返回一个空结点 */
CBTType *InitTree();
/* 查找数据域为data的结点 */
CBTType *TreeFindNode(CBTType *treeNode, DATA data);
/* 在二叉树中添加结点的操作 */
void AddTreeNode(CBTType *treeNode);
Status InsertNode(CBTType *root, DATA ch);

/* 获取左子树 */
CBTType *TreeLeftNode(CBTType *treeNode);
/* 获取右子树 */
CBTType *TreeRightNode(CBTType *treeNode);
/* 输出p所指结点的数据域 */
void TreeNodeData(CBTType *p);

/* 计算二叉树的深度 */
int TreeDepth(CBTType *root);
/* 清空二叉树 */
void ClearTree(CBTType *treeNode);
/* 判断是否为空树 */
int TreeIsEmpty(CBTType *treeNode);

/* 队列基本操作 */
Status Enqueue(queuePtr, QElemType);
Status Dequeue(queuePtr, QElemType *);
Status Emptyqueue(queuePtr q);

/* 分别为先序、中序、后序、层序遍历 */
void DLRTree(CBTType *treeNode, void(*TreeNodeData)(CBTType *p));
void LDRTree(CBTType *treeNode, void(*TreeNodeData)(CBTType *p));
void LRDTree(CBTType *treeNode, void(*TreeNodeData)(CBTType *p));
void LevelTree(CBTType *treeNode, void(*TreeNodeData)(CBTType *p));

int main() {
    CBTType *root = NULL;//定义root为指向根结点的指针
    CBTType *tmp;
    DATA ch;
    char menuSel;
    void (*Visit)();//指向函数的指针
    Visit = TreeNodeData;//指向具体函数

    root = InitTree();//初始化二叉树

    //添加结点
    do {
        printf("请选择菜单添加二叉树结点\n");
        printf("0.退出\t");
        printf("1.添加结点\n");
        while ((menuSel = (char) getchar())=='\n' || menuSel == '\r');
        switch (menuSel) {
            case '1':
                AddTreeNode(root);
                break;
            case '0':
                break;
            default:;
        }
    } while (menuSel != '0');

    //遍历二叉树
    do {
        printf("请选择菜单遍历二叉树，输入0退出\n");
        printf("1.DLR先序遍历\n");
        printf("2.LDR中序遍历\n");
        printf("3.LRD后序遍历\n");
        printf("4.按层遍历\n");
        while ((menuSel = (char) getchar())=='\n' || menuSel == '\r');
        switch (menuSel) {
            case '0':
                break;
            case '1':
                printf("\n先序遍历二叉树结果为：");
                DLRTree(root, Visit);
                printf("\n");
                break;
            case '2':
                printf("\n中序遍历二叉树结果为：");
                LDRTree(root, Visit);
                printf("\n");
                break;
            case '3':
                printf("\n后序遍历二叉树结果为：");
                LRDTree(root, Visit);
                printf("\n");
                break;
            case '4':
                printf("\n按层遍历二叉树结果为：");
                LevelTree(root, Visit);
                printf("\n");
                break;
            default:;
        }
    } while (menuSel != '0');

    printf("请输入要查找的数据：\n");
    while ((ch = (char) getchar())=='\n' || ch == '\r');
    tmp = TreeFindNode(root, ch);
    if (tmp != NULL)
        printf("二叉树中存在'%c'", tmp->data);
    else
        printf("二叉树中不存在'%c'", ch);


    printf("\n二叉树深度为：%d\n", TreeDepth(root));

    ClearTree(root);
    root = NULL;

    system("pause");

    return 0;
}

void TreeNodeData(CBTType *p) {
    printf("%c ", p->data);
}

CBTType *InitTree() {
    CBTType *tmp = malloc(sizeof(CBTType));
    tmp->data = '\0';
    tmp->left = tmp->right = NULL;
    return tmp;
}

void AddTreeNode(CBTType *treeNode) {
    DATA chr;
    printf("插入结点，请输入要插入的结点值（单个字符）：\n");
    while ((chr = (char) getchar()) == '\n' || chr == '\r');
    //特殊处理第一次插入的结点（作为根结点的值）
    if (TreeIsEmpty(treeNode))
        treeNode->data = chr;
    else
        InsertNode(treeNode, chr);
}

Status InsertNode(CBTType *treeNode, DATA ch) {
    int leftDepth= TreeDepth(treeNode->left);
    int rightDepth = TreeDepth(treeNode->right);
    //用于指向新创建的空结点
    CBTType *newNode;

    //左/右子树为空，直接插入
    if (leftDepth == 0) {
        newNode = (CBTType *) malloc(sizeof(CBTType));
        newNode->left = newNode->right = NULL;
        newNode->data = ch;
        treeNode->left = newNode;
    } else if (rightDepth == 0) {
        newNode = (CBTType *) malloc(sizeof(CBTType));
        newNode->left = newNode->right = NULL;
        newNode->data = ch;
        treeNode->right = newNode;
    } else {
        //左右子树都不为空，插在深度较小的子树上，使二叉树尽量平衡
        if (leftDepth <= rightDepth) {
            InsertNode(treeNode->left, ch);
        } else {
            InsertNode(treeNode->right, ch);
        }
    }

    return OK;
}

Status Enqueue(queuePtr q, QElemType elem) {
    QNode* tmp = (QNode *) malloc(sizeof(QNode));
    if (tmp == NULL)
        return ERROR;
    tmp->pt = elem;
    tmp->next = NULL;

    q->rear->next = tmp;
    q->rear = tmp;
    return OK;
}

Status Dequeue(queuePtr q, QElemType *out) {
    if (Emptyqueue(q) == OK)
        return ERROR;
    QNode *tmp=q->head->next;
    *out = q->head->next->pt;
    q->head->next = tmp->next;
    //由于队列是有头结点的，对出队后变为空队列的情况做特殊处理
    if (q->head->next == NULL)
        q->rear = q->head;
    free(tmp);

    return OK;
}

Status Emptyqueue(queuePtr q) {
    if (q->head->next == NULL)
        return OK;
    return ERROR;
}

int TreeDepth(CBTType *root) {
    int leftDepth = 0, rightDepth = 0;
    if (root == NULL)
        return 0;
    else {
        leftDepth = TreeDepth(root->left);
        rightDepth = TreeDepth(root->right);
        return 1 + (leftDepth > rightDepth ? leftDepth : rightDepth);
    }
}

Status TreeIsEmpty(CBTType *treeNode) {
    if (treeNode->data == '\0')
        return OK;
    else
        return ERROR;
}

void DLRTree(CBTType *treeNode, void TreeNodeData(CBTType *p)) {
    //访问当前根结点
    TreeNodeData(treeNode);
    //左子树不为空，则遍历左子树
    if (treeNode->left != NULL)
        DLRTree(treeNode->left, TreeNodeData);
    //右子树不为空，则遍历右子树
    if (treeNode->right != NULL)
        DLRTree(treeNode->right, TreeNodeData);
}

void LDRTree(CBTType *treeNode, void TreeNodeData(CBTType *p)) {
    //左子树不为空，则遍历左子树
    if (treeNode->left != NULL)
        LDRTree(treeNode->left, TreeNodeData);
    //访问当前根结点
    TreeNodeData(treeNode);
    //右子树不为空，则遍历右子树
    if (treeNode->right != NULL)
        LDRTree(treeNode->right, TreeNodeData);
}

void LRDTree(CBTType *treeNode, void TreeNodeData(CBTType *p)) {
    //左子树不为空，则遍历左子树
    if (treeNode->left != NULL)
        LRDTree(treeNode->left, TreeNodeData);
    //右子树不为空，则遍历右子树
    if (treeNode->right != NULL)
        LRDTree(treeNode->right, TreeNodeData);
    //访问当前根结点
    TreeNodeData(treeNode);
}

void LevelTree(CBTType *treeNode, void TreeNodeData(CBTType *p)) {
    //初始化层序遍历要使用的队列
    queuePtr queue = (queuePtr) malloc(sizeof(struct LinkQueue));
    queue->rear = queue->head = (QNode *) malloc(sizeof(QNode));
    queue->head->pt = NULL, queue->head->next = NULL;

    QElemType tmp;
    Enqueue(queue, treeNode);

    while (Emptyqueue(queue) != OK) {
        //出队一个元素（指向二叉树中某个结点的指针）
        Dequeue(queue, &tmp);
        TreeNodeData(tmp);//访问当前结点
        //左子树不为空，将左结点入列
        if (tmp->left != NULL)
            Enqueue(queue, tmp->left);
        //右子树不为空，将右结点入列
        if (tmp->right != NULL)
            Enqueue(queue, tmp->right);
    }
}

CBTType *TreeFindNode(CBTType *treeNode, DATA data) {
    CBTType *pointer=NULL;
    //当前根结点数据域就是data，直接返回
    if (treeNode->data == data)
        return treeNode;
    else {
        //在左子树中找
        if (treeNode->left != NULL) {
            pointer = TreeFindNode(treeNode->left, data);
            //在左子树中找到了，就直接返回
            if (pointer != NULL)
                return pointer;
        }
        //在右子树中找
        if (treeNode->right != NULL) {
            pointer = TreeFindNode(treeNode->right, data);
            //在右子树中找到了，就直接返回
            if (pointer != NULL)
                return pointer;
        }
    }
    //以上都没有返回，说明当前根结点、左子树、右子树都找不到
    return NULL;
}

void delete(CBTType *node) {
    free(node);
}

void ClearTree(CBTType *treeNode) {
    LRDTree(treeNode, delete);
}

CBTType *TreeLeftNode(CBTType *treeNode) {
    return treeNode->left;
}

CBTType *TreeRightNode(CBTType *treeNode) {
    return treeNode->right;
}