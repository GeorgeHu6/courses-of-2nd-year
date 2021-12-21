#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

#define MAX_VERTEX_NUM 20
#define TRUE 1
#define FALSE 0

typedef int Boolean;
//分别为有向图、有向网、无向图、无向网
typedef enum {
    DG, DN, UDG, UDN
} GraphKind;
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
} VNode, AdjList[MAX_VERTEX_NUM];

//邻接表本身的类型
typedef struct {
    AdjList vertices;//图的头结点数组
    int vexnum, arcnum;//图的顶点数和边或弧数
    int kind;//图的类型
} ALGraph;

void initALGraph(ALGraph *graph) {
    for (int i = 0; i < MAX_VERTEX_NUM; i++) {
        graph->vertices[i].firstarc = NULL;
        graph->vertices[i].data = i;
    }
}

/* 构建有向图 */
Boolean constructDG(ALGraph *graph);
/* 构建有向网 */
Boolean constructDN(ALGraph *graph);
/* 构建无向图 */
Boolean constructUDG(ALGraph *graph);
/* 构建无向网 */
Boolean constructUDN(ALGraph *graph);
/* 深度优先遍历图 */
void deepTraverseMap(ALGraph graph);
/* 广度优先遍历图 */
void breadthTraverseMap(ALGraph graph);


int main() {
    ALGraph graph;
    initALGraph(&graph);
    int code;

    //读入要构造的图的类型
    while (1) {
        printf("-------------\n");
        printf("0：有向图\n1：有向网\n2：无向图\n3：无向网\n-1：退出\n请选择要构造的类型\n");
        scanf("%d", &code);
        if (code == -1) {
            system("pause");
            return 0;
        } else if (code < -1 || code > 3) {
            printf("输入错误，请重新输入\n");
        } else {
            graph.kind = code;
            break;
        }
    }
    //根据不同图类型调用相应的构造函数
    if (graph.kind == DG) {
        constructDG(&graph);
    } else if (graph.kind == DN) {
        constructDN(&graph);
    } else if (graph.kind == UDG) {
        constructUDG(&graph);
    } else if (graph.kind == UDN) {
        constructUDN(&graph);
    }

    deepTraverseMap(graph);//深度优先遍历图graph
    breadthTraverseMap(graph);//广度优先遍历图graph

    printf("\n");

    system("pause");
    return 0;
}

Boolean constructDG(ALGraph *graph) {
    int start, end;
    ArcNode *newNode;
    ArcNode *pt;
    printf("-----------------\n");
    printf("开始构造有向图\n");
    printf("请输入顶点数（不能超过20）：\n");
    scanf("%d", &graph->vexnum);
    printf("请输入弧数：\n");
    scanf("%d", &graph->arcnum);
    printf("请输入各条弧的起点和终点（起点终点之间以空格隔开）：\n");
    //读入各条弧
    for (int i = 0; i < graph->arcnum; i++) {
        scanf("%d %d", &start, &end);
        if (start >= graph->vexnum || start < 0 ||
            end >= graph->vexnum || end < 0) {
            printf("该条弧输入错误，请重新输入当前弧：\n");
            i--;
            continue;
        }
        //使用头插法将边插入到邻接表中
        newNode = (ArcNode *) malloc(sizeof(ArcNode));
        newNode->adjvex = end;
        newNode->info = (char *) malloc(sizeof(char)*15);
        sprintf(newNode->info, "%d->%d", start, end);
        newNode->nextarc = graph->vertices[start].firstarc;
        graph->vertices[start].firstarc = newNode;
    }
    printf("--------邻接表预览--------\n");
    for (int i = 0; i < graph->vexnum; i++) {
        printf("%d：", graph->vertices[i].data);
        pt = graph->vertices[i].firstarc;
        while (pt != NULL) {
            printf("%s ", pt->info);
            pt = pt->nextarc;
        }
        printf("\n");
    }

    return TRUE;
}


Boolean constructDN(ALGraph *graph) {
    int start, end, weight;
    ArcNode *newNode;
    ArcNode *pt;
    printf("-----------------\n");
    printf("开始构造有向网\n");
    printf("请输入顶点数（不能超过20）：\n");
    scanf("%d", &graph->vexnum);
    printf("请输入弧数：\n");
    scanf("%d", &graph->arcnum);
    printf("请输入各条弧的起点、终点与权值（以空格隔开）：\n");
    //读入各条弧
    for (int i = 0; i < graph->arcnum; i++) {
        scanf("%d %d %d", &start, &end, &weight);
        if (start >= graph->vexnum || start < 0 ||
            end >= graph->vexnum || end < 0) {
            printf("该条弧输入错误，请重新输入当前弧：\n");
            i--;
            continue;
        }
        //使用头插法将边插入到邻接表中
        newNode = (ArcNode *) malloc(sizeof(ArcNode));
        newNode->adjvex = end;
        newNode->info = (char *) malloc(sizeof(char)*50);
        sprintf(newNode->info, "%d--%d-->%d", start, weight, end);
        newNode->nextarc = graph->vertices[start].firstarc;
        graph->vertices[start].firstarc = newNode;
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
        //无向图，使用头插法将边插入到邻接表中
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

Boolean constructUDN(ALGraph *graph) {
    int start, end, weight;
    ArcNode *newNode;
    ArcNode *pt;
    printf("-----------------\n");
    printf("开始构造无向网\n");
    printf("请输入顶点数（不能超过20）：\n");
    scanf("%d", &graph->vexnum);
    printf("请输入边数：\n");
    scanf("%d", &graph->arcnum);
    printf("请输入各条边的起点、终点与权值（以空格隔开）：\n");
    //读入各条边
    for (int i = 0; i < graph->arcnum; i++) {
        scanf("%d %d %d", &start, &end, &weight);
        if (start >= graph->vexnum || start < 0 ||
            end >= graph->vexnum || end < 0) {
            printf("该条边输入错误，请重新输入当前弧：\n");
            i--;
            continue;
        }
        newNode = (ArcNode *) malloc(sizeof(ArcNode));
        //无向图，使用头插法将边插入到邻接表中
        newNode->adjvex = end;
        newNode->info = (char *) malloc(sizeof(char)*50);
        sprintf(newNode->info, "%d--%d-->%d", start, weight, end);
        newNode->nextarc = graph->vertices[start].firstarc;
        graph->vertices[start].firstarc = newNode;
        //另一方向
        newNode = (ArcNode *) malloc(sizeof(ArcNode));
        newNode->adjvex = start;
        newNode->info = (char *) malloc(sizeof(char)*50);
        sprintf(newNode->info, "%d--%d-->%d", end, weight, start);
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

void dfs(Boolean visited[], ALGraph graph, int index) {
    ArcNode *pt=graph.vertices[index].firstarc;
    //访问当前顶点
    visited[index] = TRUE;
    printf("%d ", index);
    //循环index结点的所有邻接点
    while (pt != NULL) {
        //找index的第一个未访问的邻接点
        while (pt != NULL && visited[pt->adjvex] == TRUE)
            pt = pt->nextarc;
        //找到则访问
        if (pt != NULL)
            dfs(visited, graph, pt->adjvex);
    }
}

void deepTraverseMap(ALGraph graph) {
    Boolean visited[MAX_VERTEX_NUM]={0,};
    //使遍历同时适用于非连通图
    printf("-------------\n深度优先遍历：");
    for (int i = 0; i < graph.vexnum; i++) {
        if (visited[i] == FALSE)
            dfs(visited, graph, i);
    }
    printf("\n");
}

void breadthTraverseMap(ALGraph graph) {
    Boolean visited[MAX_VERTEX_NUM]={0,};
    ArcNode *pt;
    QElemType cur;
    LinkQueue queue;
    Initqueue(&queue);
    printf("-------------\n广度优先遍历：");

    //从下标为0的顶点开始，将其入队
    Enqueue(&queue, 0);
    while (!Emptyqueue(queue)) {
        Dequeue(&queue, &cur);
        //访问过就不再访问，未访问过就访问
        if (!visited[cur]) {
            visited[cur] = TRUE;
            printf("%d ", cur);
            pt = graph.vertices[cur].firstarc;
            //访问cur的所有邻接点
            while (pt != NULL) {
                //将当前顶点的未访问邻接点入队
                if (visited[pt->adjvex] == FALSE) {
                    Enqueue(&queue, pt->adjvex);
                }
                pt = pt->nextarc;
            }
        }
        //处理非连通图
        if (Emptyqueue(queue)) {
            for (int i = 0; i < graph.vexnum; i++) {
                if (!visited[i]) {
                    Enqueue(&queue, i);
                    break;
                }
            }
        }
    }
    printf("\n");

}
