#include <stdio.h>
#include <stdlib.h>
#define Status int
#define OK 1
#define ERROR 0

//��������Ԫ������
typedef char DATA;

// ����������������
typedef struct CBT{
    DATA data;//�������
    struct CBT *left;//������ָ��
    struct CBT *right;//������ָ��
} CBTType;

typedef CBTType* QElemType;

typedef struct QNode{
    QElemType pt;
    struct QNode *next;
} QNode;

typedef struct LinkQueue {
    QNode *head, *rear;
} *queuePtr;

/* ʵ�ֶ���������������
 * 1. ��ʼ�������������ҽ�㡢��ӽ��
 * 2. ��ȡ����������ȡ����������ʾ�������
 * 3. �����������ȡ���ն��������жϿ���
 * 4. ���������������㡢�������򡢺���
 */

/* ��ʼ����������������һ���ս�� */
CBTType *InitTree();
/* ����������Ϊdata�Ľ�� */
CBTType *TreeFindNode(CBTType *treeNode, DATA data);
/* �ڶ���������ӽ��Ĳ��� */
void AddTreeNode(CBTType *treeNode);
Status InsertNode(CBTType *root, DATA ch);

/* ��ȡ������ */
CBTType *TreeLeftNode(CBTType *treeNode);
/* ��ȡ������ */
CBTType *TreeRightNode(CBTType *treeNode);
/* ���p��ָ���������� */
void TreeNodeData(CBTType *p);

/* �������������� */
int TreeDepth(CBTType *root);
/* ��ն����� */
void ClearTree(CBTType *treeNode);
/* �ж��Ƿ�Ϊ���� */
int TreeIsEmpty(CBTType *treeNode);

/* ���л������� */
Status Enqueue(queuePtr, QElemType);
Status Dequeue(queuePtr, QElemType *);
Status Emptyqueue(queuePtr q);

/* �ֱ�Ϊ�������򡢺��򡢲������ */
void DLRTree(CBTType *treeNode, void(*TreeNodeData)(CBTType *p));
void LDRTree(CBTType *treeNode, void(*TreeNodeData)(CBTType *p));
void LRDTree(CBTType *treeNode, void(*TreeNodeData)(CBTType *p));
void LevelTree(CBTType *treeNode, void(*TreeNodeData)(CBTType *p));

int main() {
    CBTType *root = NULL;//����rootΪָ�������ָ��
    CBTType *tmp;
    DATA ch;
    char menuSel;
    void (*Visit)();//ָ������ָ��
    Visit = TreeNodeData;//ָ����庯��

    root = InitTree();//��ʼ��������

    //��ӽ��
    do {
        printf("��ѡ��˵���Ӷ��������\n");
        printf("0.�˳�\t");
        printf("1.��ӽ��\n");
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

    //����������
    do {
        printf("��ѡ��˵�����������������0�˳�\n");
        printf("1.DLR�������\n");
        printf("2.LDR�������\n");
        printf("3.LRD�������\n");
        printf("4.�������\n");
        while ((menuSel = (char) getchar())=='\n' || menuSel == '\r');
        switch (menuSel) {
            case '0':
                break;
            case '1':
                printf("\n����������������Ϊ��");
                DLRTree(root, Visit);
                printf("\n");
                break;
            case '2':
                printf("\n����������������Ϊ��");
                LDRTree(root, Visit);
                printf("\n");
                break;
            case '3':
                printf("\n����������������Ϊ��");
                LRDTree(root, Visit);
                printf("\n");
                break;
            case '4':
                printf("\n����������������Ϊ��");
                LevelTree(root, Visit);
                printf("\n");
                break;
            default:;
        }
    } while (menuSel != '0');

    printf("������Ҫ���ҵ����ݣ�\n");
    while ((ch = (char) getchar())=='\n' || ch == '\r');
    tmp = TreeFindNode(root, ch);
    if (tmp != NULL)
        printf("�������д���'%c'", tmp->data);
    else
        printf("�������в�����'%c'", ch);


    printf("\n���������Ϊ��%d\n", TreeDepth(root));

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
    printf("�����㣬������Ҫ����Ľ��ֵ�������ַ�����\n");
    while ((chr = (char) getchar()) == '\n' || chr == '\r');
    //���⴦���һ�β���Ľ�㣨��Ϊ������ֵ��
    if (TreeIsEmpty(treeNode))
        treeNode->data = chr;
    else
        InsertNode(treeNode, chr);
}

Status InsertNode(CBTType *treeNode, DATA ch) {
    int leftDepth= TreeDepth(treeNode->left);
    int rightDepth = TreeDepth(treeNode->right);
    //����ָ���´����Ŀս��
    CBTType *newNode;

    //��/������Ϊ�գ�ֱ�Ӳ���
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
        //������������Ϊ�գ�������Ƚ�С�������ϣ�ʹ����������ƽ��
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
    //���ڶ�������ͷ���ģ��Գ��Ӻ��Ϊ�ն��е���������⴦��
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
    //���ʵ�ǰ�����
    TreeNodeData(treeNode);
    //��������Ϊ�գ������������
    if (treeNode->left != NULL)
        DLRTree(treeNode->left, TreeNodeData);
    //��������Ϊ�գ������������
    if (treeNode->right != NULL)
        DLRTree(treeNode->right, TreeNodeData);
}

void LDRTree(CBTType *treeNode, void TreeNodeData(CBTType *p)) {
    //��������Ϊ�գ������������
    if (treeNode->left != NULL)
        LDRTree(treeNode->left, TreeNodeData);
    //���ʵ�ǰ�����
    TreeNodeData(treeNode);
    //��������Ϊ�գ������������
    if (treeNode->right != NULL)
        LDRTree(treeNode->right, TreeNodeData);
}

void LRDTree(CBTType *treeNode, void TreeNodeData(CBTType *p)) {
    //��������Ϊ�գ������������
    if (treeNode->left != NULL)
        LRDTree(treeNode->left, TreeNodeData);
    //��������Ϊ�գ������������
    if (treeNode->right != NULL)
        LRDTree(treeNode->right, TreeNodeData);
    //���ʵ�ǰ�����
    TreeNodeData(treeNode);
}

void LevelTree(CBTType *treeNode, void TreeNodeData(CBTType *p)) {
    //��ʼ���������Ҫʹ�õĶ���
    queuePtr queue = (queuePtr) malloc(sizeof(struct LinkQueue));
    queue->rear = queue->head = (QNode *) malloc(sizeof(QNode));
    queue->head->pt = NULL, queue->head->next = NULL;

    QElemType tmp;
    Enqueue(queue, treeNode);

    while (Emptyqueue(queue) != OK) {
        //����һ��Ԫ�أ�ָ���������ĳ������ָ�룩
        Dequeue(queue, &tmp);
        TreeNodeData(tmp);//���ʵ�ǰ���
        //��������Ϊ�գ�����������
        if (tmp->left != NULL)
            Enqueue(queue, tmp->left);
        //��������Ϊ�գ����ҽ������
        if (tmp->right != NULL)
            Enqueue(queue, tmp->right);
    }
}

CBTType *TreeFindNode(CBTType *treeNode, DATA data) {
    CBTType *pointer=NULL;
    //��ǰ��������������data��ֱ�ӷ���
    if (treeNode->data == data)
        return treeNode;
    else {
        //������������
        if (treeNode->left != NULL) {
            pointer = TreeFindNode(treeNode->left, data);
            //�����������ҵ��ˣ���ֱ�ӷ���
            if (pointer != NULL)
                return pointer;
        }
        //������������
        if (treeNode->right != NULL) {
            pointer = TreeFindNode(treeNode->right, data);
            //�����������ҵ��ˣ���ֱ�ӷ���
            if (pointer != NULL)
                return pointer;
        }
    }
    //���϶�û�з��أ�˵����ǰ����㡢�����������������Ҳ���
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