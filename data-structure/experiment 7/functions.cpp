/* functions.cpp ��������˳��洢(�洢�ṹ��bitree.h����)�Ļ������� */

#include "bitree.h"

/* ��ʼ��˳��洢�Ķ����� */
void InitBiTree(SqBiTree T) {
    for (int i = 0; i < MAX_TREE_SIZE; i++)
        T[i] = '\0';//��ֵ��Ϊ���ַ���������ڵ��Թ۲�
}

/* �������������������н���ֵ(�ַ���), ����˳��洢�Ķ�����T, ԭ���ݽ������� */
void CreateBiTree(SqBiTree T) {
    int l;
    char s[MAX_TREE_SIZE];
    char ch;
    memset(s, '\0', sizeof(s));
    InitBiTree(T);
    printf("�밴�����������ֵ(�ַ�)���ո��ʾ�ս�㣬�������%d:\n", MAX_TREE_SIZE);
    while ((ch = (char) getchar()) == '\r' || ch == '\n');//�Ե����з�
    gets(s);//�����ַ���
    //�����һ���ַ�
    T[0] = ch;
    l = (int) strlen(s);//���ַ����ĳ���
    //������ĵڶ����ַ���ʼѭ��
    for (int i = 1; i <= l; i++)//���ַ�����ֵ��T
        T[i] = s[i - 1];
}

/* ���������T���ڡ���TΪ�ն��������򷵻�TRUE������FALSE */
Boolean BiTreeEmpty(const SqBiTree T) {
    if (T[0] == '\0')//�����Ϊ���ַ�������Ϊ��
        return TRUE;
    else
        return FALSE;
}

/* ���������T���ڡ�����T����� */
int BiTreeDepth(SqBiTree const T) {
    int i, j = -1;
    //�ҵ����һ�����
    for (i = MAX_TREE_SIZE - 1; i >= 0; i--)
        if (T[i] != NULL)
            break;
    i++;//���ڼ���
    do
        j++;
    while (i >= pow(2, j));//ʹ��do-whileѭ�����j=-1�ĳ�ʼ���������
    return j;
}

/* ���������T���ڡ���T���գ�����T����ֵ�����򷵻�ERROR */
TElemType Root(SqBiTree T) {
    if (BiTreeEmpty(T))//��Ȼ��֤T���ڣ���T���п���Ϊ��
        return ERROR;
    else
        return T[0];
}

/* ���������T���ڡ�e��T��ĳ������λ�ã����ض�Ӧ����ֵ */
TElemType Value(SqBiTree T, position e) {
    //����֮ǰ���в�Ľ����
    int pre_node = (int) pow(2, e.level - 1) - 1;
    return T[pre_node + e.order - 1];
}

/* ���������T���ڡ���T��eλ�õĽ�㸳��ֵvalue */
Status Assign(SqBiTree T, position e, TElemType value) {
    //����e����T�ж�Ӧ�±�
    int i = (int) pow(2, e.level - 1) + e.order - 2;
    //�����޸ĸ����ֵ�Ĳ���
    if (i == 0) {
        if (T[i] == '\0')
            return ERROR;
        else {
            T[i] = value;
            return OK;
        }
    }
    if (value != '\0' && T[(i + 1) / 2 - 1] == '\0')//��������޸�����Ҷ��㸳�ǿ�ֵ
        return ERROR;
    if (value == '\0' && (T[i * 2 + 1] != '\0' || T[i * 2 + 2] != '\0'))//����������ӽ��ĸ��ڵ㸳��ֵ
        return ERROR;
    T[i] = value;
    return OK;
}

/* ���������T���ڡ��������ҵ���һ��ֵΪe�Ľ�㣨�������⣩�������丸����ֵ�����򷵻ء��ա� */
TElemType Parent(SqBiTree T, TElemType e) {
    int i;
    if (T[0] == '\0')//����ֱ�ӷ��ء��ա�
        return '\0';
    for (i = 1; i <= MAX_TREE_SIZE - 1; i++)//ֱ�ӴӴ��ڸ������±�1��ʼ
        if (T[i] == e)//�ҵ�e��ֱ�ӷ����丸����ֵ
            return T[(i + 1) / 2 - 1];
    return '\0';//δ�ҵ�e�����ء��ա�
}

/* ���������T���ڡ��������ҵ���һ��ֵΪe�Ľ�㣨�������⣩�����������ӽ���ֵ�����򷵻ء��ա� */
TElemType LeftChild(SqBiTree T, TElemType e) {
    int i;
    if (T[0] == '\0')//����ֱ�ӷ��ء��ա�
        return '\0';
    for (i = 0; i <= MAX_TREE_SIZE - 1; i++)
        if (T[i] == e)//�ҵ�e��ֱ�ӷ��������ӽ���ֵ
            return T[i * 2 + 1];
    return '\0';//δ�ҵ�e�����ء��ա�
}

/* ���������T���ڡ��������ҵ���һ��ֵΪe�Ľ�㣨�������⣩�����������ӽ���ֵ�����򷵻ء��ա� */
TElemType RightChild(SqBiTree T, TElemType e) {
    int i;
    if (T[0] == '\0')//����ֱ�ӷ��ء��ա�
        return '\0';
    for (i = 0; i <= MAX_TREE_SIZE - 1; i++)
        if (T[i] == e)//�ҵ�e��ֱ�ӷ��������ӽ���ֵ
            return T[i * 2 + 2];
    return '\0';//δ�ҵ�e�����ء��ա�
}

/* ���������T���ڡ��������ҵ���һ��ֵΪe���ҽ�㣨�������⣩�����������ֵܽ���ֵ�����򷵻ء��ա� */
TElemType LeftSibling(SqBiTree T, TElemType e) {
    int i;
    if (T[0] == '\0')//����ֱ�ӷ��ء��ա�
        return '\0';
    for (i = 1; i <= MAX_TREE_SIZE - 1; i++)
        if (T[i] == e && i % 2 == 0)//�ҵ�e�������Ϊż�������Һ���
            return T[i - 1];
    return '\0';//δ�ҵ�e�����ء��ա�
}

/* ���������T���ڡ��������ҵ���һ��ֵΪe�����㣨�������⣩�����������ֵܽ���ֵ�����򷵻ء��ա� */
TElemType RightSibling(SqBiTree T, TElemType e) {
    int i;
    if (T[0] == '\0')//����ֱ�ӷ��ء��ա�
        return '\0';
    for (i = 1; i <= MAX_TREE_SIZE - 1; i++)
        if (T[i] == e && i % 2)//�ҵ�e�������Ϊ������������
            return T[i + 1];
    return '\0';//δ�ҵ�e�����ء��ա�
}

/* �Ѵ�q��j��㿪ʼ������j��㱾����������Ϊ��T��i��㿪ʼ������ */
void Move(SqBiTree Q, int j, SqBiTree T, int i) {
    //��q�����������գ���q��j������������ΪT��i����������
    if (2 * j + 1 < MAX_TREE_SIZE && Q[2 * j + 1] != '\0')
        Move(Q, (2 * j + 1), T, (2 * i + 1));
    //��q�����������գ���q��j������������ΪT��i����������
    if (2 * j + 2 < MAX_TREE_SIZE && Q[2 * j + 2] != '\0')
        Move(Q, (2 * j + 2), T, (2 * i + 2));
    //��q��j�����ΪT��i���
    T[i] = Q[j];
    //��q��j����ÿ�
    Q[j] = '\0';
}

/* ���������T���ڣ�p��T��ĳ������ֵ��LRΪ0��1���ǿն�����C��T���ཻ��C��������Ϊ�ա�����LRΪ0��1,��C��ΪT��p�����������������p����ԭ������������������Ƚ���������ΪC�������� */
void InsertChild(SqBiTree T, TElemType p, int LR, SqBiTree C) {
    int j, k, i = 0;
    //����p���±�
    for (j = 0; j < (int) pow(2, BiTreeDepth(T)) - 1; j++)
        if (T[j] == p)//�ҵ���p���±�j
            break;
    k = 2 * j + 1 + LR;//T�н�Ҫ��C�滻���ĵط�
    if (T[k] != '\0') //T����kΪ�����������ǿ���
        Move(T, k, T, 2 * k + 2);//�Ѵ�T��k��㿪ʼ����������k���ҽ�㿪ʼ������
    Move(C, i, T, k); //�Ѵ�C��i��㿪ʼ����������T��k�����
}

/* �����Ԫ������Ϊ����(���) */

/* ���������T���ڣ�pָ��T��ĳ����㣬LRΪ1��0������LRΪ0��1��ɾ��T��p��ָ������������� */
Status DeleteChild(SqBiTree T, position p, int LR) {
    int i;
    Boolean flag = TRUE;//���в��յı�־
    LinkQueue q;
    InitQueue(q);//��ʼ�����У����ڴ�Ŵ�ɾ���Ľ��
    i = (int) pow(2, p.level - 1) + p.order - 2;//��λ��pת��Ϊ�±�
    if (T[i] == '\0')//TΪ����
        return ERROR;
    i = i * 2 + 1 + LR;//��ɾ�������ĸ������±�
    while (flag) {
        if (2 * i + 1 < MAX_TREE_SIZE && T[2 * i + 1] != '\0')//���㲻��
            EnQueue(q, 2 * i + 1);//���������±�
        if (2 * i + 2 < MAX_TREE_SIZE && T[2 * i + 2] != '\0')//�ҽ�㲻��
            EnQueue(q, 2 * i + 2);//����ҽ����±�
        T[i] = '\0';//ɾ����ǰ���
        flag = DeQueue(q, i);//��ȡ��������һ������±겢��ȡ�����Ƿ�Ϊ��
    }
    return OK;
}

/* ������˿ո�Ϳ��ַ�֮����ַ� */
void VisitFunc(TElemType e) {
    if (e != ' ' && e != '\0')
        printf("%c", e);
}

/* ��������ĵݹ���ú��� */
void PreTraverse(SqBiTree T, int e) {
    //���ʵ�ǰ�����
    VisitFunc(T[e]);
    //���������գ������֮
    if (2 * e + 1 < MAX_TREE_SIZE && T[2 * e + 1] != '\0')
        PreTraverse(T, 2 * e + 1);
    //���������գ������֮
    if (2 * e + 2 < MAX_TREE_SIZE && T[2 * e + 2] != '\0')
        PreTraverse(T, 2 * e + 2);
}

/* �������������T */
void PreOrderTraverse(SqBiTree T) {
    if (!BiTreeEmpty(T))//�ж�����Ϊ��
        PreTraverse(T, 0);
    printf("\n");
}

/* ��������ĵݹ���ú��� */
void InTraverse(SqBiTree T, int e) {
    if (2 * e + 1 < MAX_TREE_SIZE && T[2 * e + 1] != '\0')//���������գ������֮
        InTraverse(T, 2 * e + 1);
    //���ʵ�ǰ�����
    VisitFunc(T[e]);
    if (2 * e + 2 < MAX_TREE_SIZE && T[2 * e + 2] != '\0')//���������գ������֮
        InTraverse(T, 2 * e + 2);
}

/* �������������T */
void InOrderTraverse(SqBiTree T) {
    if (!BiTreeEmpty(T))//�ж�����Ϊ��
        InTraverse(T, 0);
    printf("\n");
}

/* ��������ĵݹ���ú��� */
void PostTraverse(SqBiTree T, int e) {
    if (2 * e + 1 < MAX_TREE_SIZE && T[2 * e + 1] != '\0')//���������գ������֮
        PostTraverse(T, 2 * e + 1);
    if (2 * e + 2 < MAX_TREE_SIZE && T[2 * e + 2] != '\0')//���������գ������֮
        PostTraverse(T, 2 * e + 2);
    //���ʵ�ǰ�����
    VisitFunc(T[e]);
}

/* �������������T */
void PostOrderTraverse(SqBiTree T) {
    if (!BiTreeEmpty(T))//�ж�����Ϊ��
        PostTraverse(T, 0);
    printf("\n");
}

/* ������������� */
void LevelOrderTraverse(SqBiTree T) {
    int i = MAX_TREE_SIZE - 1, j;
    //�ҵ����һ���ǿս������
    while (T[i] == '\0')
        i--;
    //�Ӹ�����𣬰��������������
    for (j = 0; j <= i; j++)
        //�����ս��
        if (T[j] != '\0')
            VisitFunc(T[j]);
    printf("\n");
}

/* ��㣬ÿ���������������� */
void Print(SqBiTree T) {
    int j, k;
    position p;
    TElemType e;
    //���ѭ��ÿһ��
    for (j = 1; j <= BiTreeDepth(T); j++) {
        printf("��%d��: ", j);
        //�ڲ��������ѭ����j��
        for (k = 1; k <= pow(2, j - 1); k++) {
            p.level = j;
            p.order = k;
            //����Value�õ�T�д���pλ�ý���ֵ
            e = Value(T, p);
            if (e != '\0')
                printf("%c", e);
        }
        printf("\n");
    }
}


/* ���в������� */
/* ���г�ʼ����������һ���ն���*/
Status InitQueue(LinkQueue &Q) {
    //�洢�ռ����ʧ��
    if (!(Q.front = Q.rear = (QueuePtr) malloc(sizeof(QNode))))
        return ERROR;
    Q.front->next = NULL;
    return OK;
}

/* ���ٶ��У�ͬʱ�ͷŸ���Ԫ����ռ�ռ� */
Status DestroyQueue(LinkQueue &Q) {
    while (Q.front) {
        //����βָ��ʼ��ָ��Ҫɾ����Ԫ�ص���һ��
        Q.rear = Q.front->next;
        free(Q.front);
        Q.front = Q.rear;
    }
    return OK;
}

/* ����Ԫ��eΪQ���µĶ�βԪ�� */
Status EnQueue(LinkQueue &Q, QElemType e) {
    QueuePtr p;
    //�洢�ռ����ʧ��
    if (!(p = (QueuePtr) malloc(sizeof(QNode))))
        return ERROR;
    p->data = e;
    //��Ԫ�ص�nextӦΪNULL
    p->next = NULL;
    Q.rear->next = p;
    //��β��Ϊ����ӵ�Ԫ��
    Q.rear = p;
    return OK;
}

/* �ж϶���Q�Ƿ�Ϊ�գ��շ���TRUE���ǿշ���FALSE */
Status QueueEmpty(LinkQueue Q) {
    //����ͷָ��Ķ����пշ���
    if (Q.front == Q.rear)
        return TRUE;
    else
        return FALSE;
}

/* ��Q�н�����һ��Ԫ�أ���e�������Ԫ�ص�ֵ������ʧ�ܣ�����ERROR�����гɹ�������OK */
Status DeQueue(LinkQueue &Q, QElemType &e) {
    QueuePtr p;
    //���ж϶���Q�Ƿ�Ϊ��
    if (QueueEmpty(Q) == TRUE)
        return ERROR;
    p = Q.front->next;
    e = p->data;
    Q.front->next = p->next;
    //��ͷ���Ķ��б�Ϊ��ʱ�����⴦��
    if (Q.rear == p)
        Q.rear = Q.front;
    free(p);
    return OK;
}
