#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

#define MAX_VERTEX_NUM 20
#define TRUE 1
#define FALSE 0
#define colorA 1
#define colorB 2

typedef int Boolean;
//分别为有向图、有向网、无向图、无向网
typedef enum {
    DG, DN, UDG, UDN
} GraphKind;
//表示顶点关系的类型
typedef int VRType;
//表示边信息的类型
typedef char InfoType;

//图/网中的顶点类型
typedef int VertexType;

//邻接表中普通元素的类型
typedef struct ArcNode {
    int adjvex;//边或弧所依附的顶点的位置，即边或弧的终点
    struct ArcNode *nextarc;//指向下一条依附顶点的边或弧的指针
    InfoType *info;//边或弧的相关信息指针
} ArcNode;

//邻接表中头结点类型
typedef struct {
    VertexType data;//顶点信息
    ArcNode *firstarc;//指向第一条依附本顶点的边或弧的指针
    int color, colorStatus;//color为当前结点的颜色，colorStatus为当前结点邻接点的填色情况
} VNode, AdjList[MAX_VERTEX_NUM];

//邻接表本身的类型
typedef struct {
    AdjList vertices;//图的头结点数组
    int vexnum, arcnum;//图的顶点数和边或弧数
} ALGraph;

void initALGraph(ALGraph *graph) {
    for (int i = 0; i < MAX_VERTEX_NUM; i++) {
        graph->vertices[i].color = 0;
        graph->vertices[i].colorStatus = 0;
        graph->vertices[i].firstarc = NULL;
        graph->vertices[i].data = i;
    }
}

/* 构建无向图 */
Boolean constructUDG(ALGraph *graph);
/* 广度优先给图填色 */
Boolean bfsFilling(ALGraph *graph);
/* 输出填色情况 */
void printColor(ALGraph graph);

int main() {
    ALGraph graph;
    Boolean res;
    initALGraph(&graph);

    printf("构建无向图\n");
    constructUDG(&graph);

    res = bfsFilling(&graph);
    if (res == FALSE) {
        printf("该图无法填色");
    } else {
        printf("------------------------\n");
        printf("填色成功，填色情况如下\n");
        printColor(graph);
    }

    printf("\n");

    system("pause");
    return 0;
}

void printColor(ALGraph graph) {
    for (int i = 0; i < graph.vexnum; i++) {
        if (graph.vertices[i].color == colorA)
            printf("%d：colorA\n", i);
        else if(graph.vertices[i].color == colorB)
            printf("%d：colorB\n", i);
        else
            printf("%d：未填色\n", i);
    }
}

Boolean constructUDG(ALGraph *graph) {
    int start, end;
    ArcNode *newNode;
    ArcNode *pt;
    printf("-----------------\n");
    printf("开始构造无向图\n");
    printf("请输入顶点数（不能超过20）：\n");
    scanf("%d", &graph->vexnum);
    printf("请输入边数：\n");
    scanf("%d", &graph->arcnum);
    printf("请输入各条边的起点和终点（起点终点之间以空格隔开）：\n");
    //读入各条边
    for (int i = 0; i < graph->arcnum; i++) {
        scanf("%d %d", &start, &end);
        if (start >= graph->vexnum || start < 0 ||
            end >= graph->vexnum || end < 0) {
            printf("该条边输入错误，请重新输入当前弧：\n");
            i--;
            continue;
        }
        newNode = (ArcNode *) malloc(sizeof(ArcNode));
        //无向图，头插法将边插入邻接表
        newNode->adjvex = end;
        newNode->info = (char *) malloc(sizeof(char)*15);
        sprintf(newNode->info, "%d->%d", start, end);
        newNode->nextarc = graph->vertices[start].firstarc;
        graph->vertices[start].firstarc = newNode;
        //另一方向
        newNode = (ArcNode *) malloc(sizeof(ArcNode));
        newNode->adjvex = start;
        newNode->info = (char *) malloc(sizeof(char)*15);
        sprintf(newNode->info, "%d->%d", end, start);
        newNode->nextarc = graph->vertices[end].firstarc;
        graph->vertices[end].firstarc = newNode;
    }
    printf("--------邻接表预览--------\n");
    for (int i = 0; i < graph->vexnum; i++) {
        printf("%d：", graph->vertices[i].data);
        pt = graph->vertices[i].firstarc;
        while (pt != NULL) {
            printf("%s  ", pt->info);
            pt = pt->nextarc;
        }
        printf("\n");
    }

    return TRUE;
}

Boolean bfsFilling(ALGraph *graph) {
    ArcNode *pt;
    QElemType cur;
    LinkQueue queue;
    Initqueue(&queue);

    //从下标为0的顶点开始，将其入队
    Enqueue(&queue, 0);
    while (!Emptyqueue(queue)) {
        //出队一个元素
        Dequeue(&queue, &cur);
        //未填色过则根据情况填色
        if (graph->vertices[cur].color == 0) {
            //cur的邻接点中已经填有colorA和colorB，说明无法填色
            if (graph->vertices[cur].colorStatus == 3) {
                return FALSE;
            } else if ((graph->vertices[cur].colorStatus & colorA) == colorA) {//cur邻接点中已经填有colorA，则填colorB并更新所有邻接点
                graph->vertices[cur].color = colorB;
                pt = graph->vertices[cur].firstarc;
                while (pt != NULL) {
                    graph->vertices[pt->adjvex].colorStatus |= colorB;
                    pt = pt->nextarc;
                }
            } else if ((graph->vertices[cur].color & colorB) == colorB) {//cur邻接点中已经填有colorB，则天colorA并更新所有邻接点
                graph->vertices[cur].color = colorA;
                pt = graph->vertices[cur].firstarc;
                while (pt != NULL) {
                    graph->vertices[pt->adjvex].colorStatus |= colorA;
                    pt = pt->nextarc;
                }
            } else {//cur的邻接点中还没有填色过，就填colorA
                graph->vertices[cur].color = colorA;
                pt = graph->vertices[cur].firstarc;
                while (pt != NULL) {
                    graph->vertices[pt->adjvex].colorStatus |= colorA;
                    pt = pt->nextarc;
                }
            }
            pt = graph->vertices[cur].firstarc;
            //访问cur的所有邻接点
            while (pt != NULL) {
                //将当前顶点的未填色邻接点入队
                if (graph->vertices[pt->adjvex].color == 0) {
                    Enqueue(&queue, pt->adjvex);
                }
                pt = pt->nextarc;
            }
        }
        //处理非连通图
        if (Emptyqueue(queue)) {
            for (int i = 0; i < graph->vexnum; i++) {
                if (graph->vertices[i].color == 0) {
                    Enqueue(&queue, i);
                    break;
                }
            }
        }
    }
}
