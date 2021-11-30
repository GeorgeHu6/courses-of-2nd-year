/* functions.cpp 二叉树的顺序存储(存储结构由bitree.h定义)的基本操作 */

#include "bitree.h"

/* 初始化顺序存储的二叉树 */
void InitBiTree(SqBiTree T) {
    for (int i = 0; i < MAX_TREE_SIZE; i++)
        T[i] = '\0';//初值设为空字符，方便后期调试观察
}

/* 按层序次序输入二叉树中结点的值(字符型), 构造顺序存储的二叉树T, 原数据将被置零 */
void CreateBiTree(SqBiTree T) {
    int l;
    char s[MAX_TREE_SIZE];
    char ch;
    memset(s, '\0', sizeof(s));
    InitBiTree(T);
    printf("请按层序输入结点的值(字符)，空格表示空结点，结点数≤%d:\n", MAX_TREE_SIZE);
    while ((ch = (char) getchar()) == '\r' || ch == '\n');//吃掉换行符
    gets(s);//读入字符串
    //存入第一个字符
    T[0] = ch;
    l = (int) strlen(s);//求字符串的长度
    //从输入的第二个字符开始循环
    for (int i = 1; i <= l; i++)//将字符串赋值给T
        T[i] = s[i - 1];
}

/* 假设二叉树T存在。若T为空二叉树，则返回TRUE，否则FALSE */
Boolean BiTreeEmpty(const SqBiTree T) {
    if (T[0] == '\0')//根结点为空字符，则树为空
        return TRUE;
    else
        return FALSE;
}

/* 假设二叉树T存在。返回T的深度 */
int BiTreeDepth(SqBiTree const T) {
    int i, j = -1;
    //找到最后一个结点
    for (i = MAX_TREE_SIZE - 1; i >= 0; i--)
        if (T[i] != NULL)
            break;
    i++;//便于计算
    do
        j++;
    while (i >= pow(2, j));//使用do-while循环配合j=-1的初始化计算层数
    return j;
}

/* 假设二叉树T存在。当T不空，返回T根的值，否则返回ERROR */
TElemType Root(SqBiTree T) {
    if (BiTreeEmpty(T))//虽然保证T存在，但T仍有可能为空
        return ERROR;
    else
        return T[0];
}

/* 假设二叉树T存在。e是T中某个结点的位置，返回对应结点的值 */
TElemType Value(SqBiTree T, position e) {
    //计算之前所有层的结点数
    int pre_node = (int) pow(2, e.level - 1) - 1;
    return T[pre_node + e.order - 1];
}

/* 假设二叉树T存在。将T中e位置的结点赋新值value */
Status Assign(SqBiTree T, position e, TElemType value) {
    //根据e计算T中对应下标
    int i = (int) pow(2, e.level - 1) + e.order - 2;
    //特判修改根结点值的操作
    if (i == 0) {
        if (T[i] == '\0')
            return ERROR;
        else {
            T[i] = value;
            return OK;
        }
    }
    if (value != '\0' && T[(i + 1) / 2 - 1] == '\0')//不允许给无父结点的叶结点赋非空值
        return ERROR;
    if (value == '\0' && (T[i * 2 + 1] != '\0' || T[i * 2 + 2] != '\0'))//不允许给有子结点的父节点赋空值
        return ERROR;
    T[i] = value;
    return OK;
}

/* 假设二叉树T存在。按层序找到第一个值为e的结点（根结点除外）并返回其父结点的值；否则返回“空” */
TElemType Parent(SqBiTree T, TElemType e) {
    int i;
    if (T[0] == '\0')//空树直接返回“空”
        return '\0';
    for (i = 1; i <= MAX_TREE_SIZE - 1; i++)//直接从存在父结点的下标1开始
        if (T[i] == e)//找到e，直接返回其父结点的值
            return T[(i + 1) / 2 - 1];
    return '\0';//未找到e，返回“空”
}

/* 假设二叉树T存在。按层序找到第一个值为e的结点（根结点除外）并返回其左子结点的值；否则返回“空” */
TElemType LeftChild(SqBiTree T, TElemType e) {
    int i;
    if (T[0] == '\0')//空树直接返回“空”
        return '\0';
    for (i = 0; i <= MAX_TREE_SIZE - 1; i++)
        if (T[i] == e)//找到e，直接返回其左子结点的值
            return T[i * 2 + 1];
    return '\0';//未找到e，返回“空”
}

/* 假设二叉树T存在。按层序找到第一个值为e的结点（根结点除外）并返回其右子结点的值；否则返回“空” */
TElemType RightChild(SqBiTree T, TElemType e) {
    int i;
    if (T[0] == '\0')//空树直接返回“空”
        return '\0';
    for (i = 0; i <= MAX_TREE_SIZE - 1; i++)
        if (T[i] == e)//找到e，直接返回其右子结点的值
            return T[i * 2 + 2];
    return '\0';//未找到e，返回“空”
}

/* 假设二叉树T存在。按层序找到第一个值为e的右结点（根结点除外）并返回其左兄弟结点的值；否则返回“空” */
TElemType LeftSibling(SqBiTree T, TElemType e) {
    int i;
    if (T[0] == '\0')//空树直接返回“空”
        return '\0';
    for (i = 1; i <= MAX_TREE_SIZE - 1; i++)
        if (T[i] == e && i % 2 == 0)//找到e，其序号为偶数，即右孩子
            return T[i - 1];
    return '\0';//未找到e，返回“空”
}

/* 假设二叉树T存在。按层序找到第一个值为e的左结点（根结点除外）并返回其右兄弟结点的值；否则返回“空” */
TElemType RightSibling(SqBiTree T, TElemType e) {
    int i;
    if (T[0] == '\0')//空树直接返回“空”
        return '\0';
    for (i = 1; i <= MAX_TREE_SIZE - 1; i++)
        if (T[i] == e && i % 2)//找到e，其序号为奇数，即左孩子
            return T[i + 1];
    return '\0';//未找到e，返回“空”
}

/* 把从q的j结点开始（包括j结点本身）的子树移为从T的i结点开始的子树 */
void Move(SqBiTree Q, int j, SqBiTree T, int i) {
    //若q的左子树不空，把q的j结点的左子树移为T的i结点的左子树
    if (2 * j + 1 < MAX_TREE_SIZE && Q[2 * j + 1] != '\0')
        Move(Q, (2 * j + 1), T, (2 * i + 1));
    //若q的右子树不空，把q的j结点的右子树移为T的i结点的右子树
    if (2 * j + 2 < MAX_TREE_SIZE && Q[2 * j + 2] != '\0')
        Move(Q, (2 * j + 2), T, (2 * i + 2));
    //把q的j结点移为T的i结点
    T[i] = Q[j];
    //把q的j结点置空
    Q[j] = '\0';
}

/* 假设二叉树T存在，p是T中某个结点的值，LR为0或1，非空二叉树C与T不相交，C的右子树为空。根据LR为0或1,将C作为T中p结点的左或右子树；若p结点的原来有左或右子树，则先将该子树作为C的右子树 */
void InsertChild(SqBiTree T, TElemType p, int LR, SqBiTree C) {
    int j, k, i = 0;
    //查找p的下标
    for (j = 0; j < (int) pow(2, BiTreeDepth(T)) - 1; j++)
        if (T[j] == p)//找到了p的下标j
            break;
    k = 2 * j + 1 + LR;//T中将要被C替换掉的地方
    if (T[k] != '\0') //T中以k为根的子树不是空树
        Move(T, k, T, 2 * k + 2);//把从T的k结点开始的子树移至k的右结点开始的子树
    Move(C, i, T, k); //把从C的i结点开始的子树移至T的k结点上
}

/* 设队列元素类型为整型(序号) */

/* 假设二叉树T存在，p指向T中某个结点，LR为1或0。根据LR为0或1，删除T中p所指结点的左或右子树 */
Status DeleteChild(SqBiTree T, position p, int LR) {
    int i;
    Boolean flag = TRUE;//队列不空的标志
    LinkQueue q;
    InitQueue(q);//初始化队列，用于存放待删除的结点
    i = (int) pow(2, p.level - 1) + p.order - 2;//将位置p转换为下标
    if (T[i] == '\0')//T为空树
        return ERROR;
    i = i * 2 + 1 + LR;//待删除子树的根结点的下标
    while (flag) {
        if (2 * i + 1 < MAX_TREE_SIZE && T[2 * i + 1] != '\0')//左结点不空
            EnQueue(q, 2 * i + 1);//入队左结点的下标
        if (2 * i + 2 < MAX_TREE_SIZE && T[2 * i + 2] != '\0')//右结点不空
            EnQueue(q, 2 * i + 2);//入队右结点的下标
        T[i] = '\0';//删除当前结点
        flag = DeQueue(q, i);//获取队列中下一个结点下标并获取队列是否为空
    }
    return OK;
}

/* 输出除了空格和空字符之外的字符 */
void VisitFunc(TElemType e) {
    if (e != ' ' && e != '\0')
        printf("%c", e);
}

/* 先序遍历的递归调用函数 */
void PreTraverse(SqBiTree T, int e) {
    //访问当前根结点
    VisitFunc(T[e]);
    //左子树不空，则遍历之
    if (2 * e + 1 < MAX_TREE_SIZE && T[2 * e + 1] != '\0')
        PreTraverse(T, 2 * e + 1);
    //右子树不空，则遍历之
    if (2 * e + 2 < MAX_TREE_SIZE && T[2 * e + 2] != '\0')
        PreTraverse(T, 2 * e + 2);
}

/* 先序遍历二叉树T */
void PreOrderTraverse(SqBiTree T) {
    if (!BiTreeEmpty(T))//判断树不为空
        PreTraverse(T, 0);
    printf("\n");
}

/* 中序遍历的递归调用函数 */
void InTraverse(SqBiTree T, int e) {
    if (2 * e + 1 < MAX_TREE_SIZE && T[2 * e + 1] != '\0')//左子树不空，则遍历之
        InTraverse(T, 2 * e + 1);
    //访问当前根结点
    VisitFunc(T[e]);
    if (2 * e + 2 < MAX_TREE_SIZE && T[2 * e + 2] != '\0')//右子树不空，则遍历之
        InTraverse(T, 2 * e + 2);
}

/* 中序遍历二叉树T */
void InOrderTraverse(SqBiTree T) {
    if (!BiTreeEmpty(T))//判断树不为空
        InTraverse(T, 0);
    printf("\n");
}

/* 后序遍历的递归调用函数 */
void PostTraverse(SqBiTree T, int e) {
    if (2 * e + 1 < MAX_TREE_SIZE && T[2 * e + 1] != '\0')//左子树不空，则遍历之
        PostTraverse(T, 2 * e + 1);
    if (2 * e + 2 < MAX_TREE_SIZE && T[2 * e + 2] != '\0')//右子树不空，则遍历之
        PostTraverse(T, 2 * e + 2);
    //访问当前根结点
    VisitFunc(T[e]);
}

/* 后序遍历二叉树T */
void PostOrderTraverse(SqBiTree T) {
    if (!BiTreeEmpty(T))//判断树不为空
        PostTraverse(T, 0);
    printf("\n");
}

/* 层序遍历二叉树 */
void LevelOrderTraverse(SqBiTree T) {
    int i = MAX_TREE_SIZE - 1, j;
    //找到最后一个非空结点的序号
    while (T[i] == '\0')
        i--;
    //从根结点起，按层序遍历二叉树
    for (j = 0; j <= i; j++)
        //跳过空结点
        if (T[j] != '\0')
            VisitFunc(T[j]);
    printf("\n");
}

/* 逐层，每层从左到右输出二叉树 */
void Print(SqBiTree T) {
    int j, k;
    position p;
    TElemType e;
    //外层循环每一层
    for (j = 1; j <= BiTreeDepth(T); j++) {
        printf("第%d层: ", j);
        //内层从左向右循环第j层
        for (k = 1; k <= pow(2, j - 1); k++) {
            p.level = j;
            p.order = k;
            //调用Value得到T中处于p位置结点的值
            e = Value(T, p);
            if (e != '\0')
                printf("%c", e);
        }
        printf("\n");
    }
}


/* 队列操作函数 */
/* 队列初始化，即构造一个空队列*/
Status InitQueue(LinkQueue &Q) {
    //存储空间分配失败
    if (!(Q.front = Q.rear = (QueuePtr) malloc(sizeof(QNode))))
        return ERROR;
    Q.front->next = NULL;
    return OK;
}

/* 销毁队列，同时释放各个元素所占空间 */
Status DestroyQueue(LinkQueue &Q) {
    while (Q.front) {
        //将队尾指针始终指向要删除的元素的下一个
        Q.rear = Q.front->next;
        free(Q.front);
        Q.front = Q.rear;
    }
    return OK;
}

/* 插入元素e为Q的新的队尾元素 */
Status EnQueue(LinkQueue &Q, QElemType e) {
    QueuePtr p;
    //存储空间分配失败
    if (!(p = (QueuePtr) malloc(sizeof(QNode))))
        return ERROR;
    p->data = e;
    //新元素的next应为NULL
    p->next = NULL;
    Q.rear->next = p;
    //队尾变为新入队的元素
    Q.rear = p;
    return OK;
}

/* 判断队列Q是否为空，空返回TRUE，非空返回FALSE */
Status QueueEmpty(LinkQueue Q) {
    //带有头指针的队列判空方法
    if (Q.front == Q.rear)
        return TRUE;
    else
        return FALSE;
}

/* 从Q中将出列一个元素，用e保存出列元素的值。出列失败，返回ERROR；出列成功，返回OK */
Status DeQueue(LinkQueue &Q, QElemType &e) {
    QueuePtr p;
    //先判断队列Q是否为空
    if (QueueEmpty(Q) == TRUE)
        return ERROR;
    p = Q.front->next;
    e = p->data;
    Q.front->next = p->next;
    //带头结点的队列变为空时的特殊处理
    if (Q.rear == p)
        Q.rear = Q.front;
    free(p);
    return OK;
}
