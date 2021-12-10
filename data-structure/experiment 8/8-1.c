#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

#define INFINITY INT_MAX
#define MAX_VERTEX_NUM 20
#define TRUE 1
#define FALSE 0

typedef int Boolean;
//分别为有向图、有向网、无向图、无向网
typedef enum {
    DG, DN, UDG, UDN
} GraphKind;
//表示顶点关系的类型
typedef int VRType;
//表示边信息的类型
typedef char *InfoType;

//图/网中的顶点类型
typedef int VertexType;

//邻接矩阵中元素的类型
typedef struct ArcCell {
    VRType adj;//顶点关系，为1/0表示是否相邻或表示权值
    InfoType *info;//边或弧的相关信息指针
} ArcCell, AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
/* 邻接矩阵中元素的Setter */
void setArcCell(ArcCell *cell, VRType value, InfoType *infoPt) {
    cell->adj = value;
    cell->info = infoPt;
}
/* 把n*n的邻接矩阵matrix中的初始化，顶点关系为value */
Boolean initAdjMat(AdjMatrix matrix, int n, int value) {
    if (n > MAX_VERTEX_NUM)
        return FALSE;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            setArcCell(&matrix[i][j], value, NULL);
    return TRUE;
}

//邻接矩阵的类型
typedef struct {
    VertexType vexs[MAX_VERTEX_NUM];
    AdjMatrix arcs;//邻接矩阵
    int vexnum, arcnum;//顶点数、边/弧数
    GraphKind kind;
} Mgraph;

/* 构建有向图 */
Boolean constructDG(Mgraph *mgraph);
/* 构建有向网 */
Boolean constructDN(Mgraph *mgraph);
/* 构建无向图 */
Boolean constructUDG(Mgraph *mgraph);
/* 构建无向网 */
Boolean constructUDN(Mgraph *mgraph);
/* 深度优先遍历图 */
void deepTraverseMap(Mgraph mgraph);
/* 广度优先遍历图 */
void breadthTraverseMap(Mgraph mgraph);


int main() {
    Mgraph graph;
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

Boolean constructDG(Mgraph *mgraph) {
    int start, end;
    printf("-----------------\n");
    printf("开始构造有向图\n");
    printf("请输入顶点数（不能超过20）：\n");
    scanf("%d", &mgraph->vexnum);
    initAdjMat(mgraph->arcs, mgraph->vexnum, 0);
    printf("请输入弧数：\n");
    scanf("%d", &mgraph->arcnum);
    printf("请输入各条弧的起点和终点（起点终点之间以空格隔开）：\n");
    //读入各条弧
    for (int i = 0; i < mgraph->arcnum; i++) {
        scanf("%d %d", &start, &end);
        if (start >= mgraph->vexnum || start < 0 ||
            end >= mgraph->vexnum || end < 0) {
            printf("该条弧输入错误，请重新输入当前弧：\n");
            i--;
            continue;
        }
        setArcCell(&mgraph->arcs[start][end], 1, NULL);
    }
    printf("--------邻接矩阵预览--------\n");
    for (int i = 0; i < mgraph->vexnum; i++) {
        for (int j = 0; j < mgraph->vexnum; j++)
            printf("%6d", mgraph->arcs[i][j].adj);
        printf("\n");
    }

    return TRUE;
}

Boolean constructDN(Mgraph *mgraph) {
    int start, end, weight;
    printf("-----------------\n");
    printf("开始构造有向网\n");
    printf("请输入顶点数（不能超过20）：\n");
    scanf("%d", &mgraph->vexnum);
    initAdjMat(mgraph->arcs, mgraph->vexnum, INFINITY);
    printf("请输入弧数：\n");
    scanf("%d", &mgraph->arcnum);
    printf("请输入各条弧的起点、终点与权值（以空格隔开）：\n");
    //读入各条弧
    for (int i = 0; i < mgraph->arcnum; i++) {
        scanf("%d %d %d", &start, &end, &weight);
        if (start >= mgraph->vexnum || start < 0 ||
            end >= mgraph->vexnum || end < 0) {
            printf("该条弧输入错误，请重新输入当前弧：\n");
            i--;
            continue;
        }
        setArcCell(&mgraph->arcs[start][end], weight, NULL);
    }
    printf("--------邻接矩阵预览--------\n");
    for (int i = 0; i < mgraph->vexnum; i++) {
        for (int j = 0; j < mgraph->vexnum; j++) {
            if (mgraph->arcs[i][j].adj != INFINITY)
                printf("%6d", mgraph->arcs[i][j].adj);
            else
                printf("   INF");
        }

        printf("\n");
    }

    return TRUE;
}

Boolean constructUDG(Mgraph *mgraph) {
    int start, end;
    printf("-----------------\n");
    printf("开始构造无向图\n");
    printf("请输入顶点数（不能超过20）：\n");
    scanf("%d", &mgraph->vexnum);
    initAdjMat(mgraph->arcs, mgraph->vexnum, 0);
    printf("请输入边数：\n");
    scanf("%d", &mgraph->arcnum);
    printf("请输入各条边的起点和终点（起点终点之间以空格隔开）：\n");
    //读入各条边
    for (int i = 0; i < mgraph->arcnum; i++) {
        scanf("%d %d", &start, &end);
        if (start >= mgraph->vexnum || start < 0 ||
            end >= mgraph->vexnum || end < 0) {
            printf("该条边输入错误，请重新输入当前弧：\n");
            i--;
            continue;
        }
        //无向图，构建对称的邻接矩阵
        setArcCell(&mgraph->arcs[start][end], 1, NULL);
        setArcCell(&mgraph->arcs[end][start], 1, NULL);
    }
    printf("--------邻接矩阵预览--------\n");
    for (int i = 0; i < mgraph->vexnum; i++) {
        for (int j = 0; j < mgraph->vexnum; j++)
            printf("%6d", mgraph->arcs[i][j].adj);
        printf("\n");
    }

    return TRUE;
}

Boolean constructUDN(Mgraph *mgraph) {
    int start, end, weight;
    printf("-----------------\n");
    printf("开始构造无向网\n");
    printf("请输入顶点数（不能超过20）：\n");
    scanf("%d", &mgraph->vexnum);
    initAdjMat(mgraph->arcs, mgraph->vexnum, INFINITY);
    printf("请输入边数：\n");
    scanf("%d", &mgraph->arcnum);
    printf("请输入各条边的起点、终点与权值（以空格隔开）：\n");
    //读入各条边
    for (int i = 0; i < mgraph->arcnum; i++) {
        scanf("%d %d %d", &start, &end, &weight);
        if (start >= mgraph->vexnum || start < 0 ||
            end >= mgraph->vexnum || end < 0) {
            printf("该条边输入错误，请重新输入当前弧：\n");
            i--;
            continue;
        }
        //无向图，构建对称的邻接矩阵
        setArcCell(&mgraph->arcs[start][end], weight, NULL);
        setArcCell(&mgraph->arcs[end][start], weight, NULL);
    }
    printf("--------邻接矩阵预览--------\n");
    for (int i = 0; i < mgraph->vexnum; i++) {
        for (int j = 0; j < mgraph->vexnum; j++) {
            if (mgraph->arcs[i][j].adj != INFINITY)
                printf("%6d", mgraph->arcs[i][j].adj);
            else
                printf("   INF");
        }

        printf("\n");
    }

    return TRUE;
}

void dfs(Boolean visited[], Mgraph mgraph, int index) {
    //访问当前顶点
    visited[index] = TRUE;
    printf("%d ", index);
    //访问邻接点
    for (int i = 0; i < mgraph.vexnum; i++) {
        //邻接点未访问则访问
        if (visited[i] == FALSE && (
                ((mgraph.kind == DG || mgraph.kind == UDG) && mgraph.arcs[index][i].adj != 0) ||
                ((mgraph.kind == DN || mgraph.kind == UDN) && mgraph.arcs[index][i].adj != INFINITY))) {
            dfs(visited, mgraph, i);
        }
    }
}

void deepTraverseMap(Mgraph mgraph) {
    Boolean visited[MAX_VERTEX_NUM]={0,};
    //使遍历同时适用于非连通图
    printf("-------------\n深度优先遍历：");
    for (int i = 0; i < mgraph.vexnum; i++) {
        if (visited[i] == FALSE)
            dfs(visited, mgraph, i);
    }
    printf("\n");
}

void breadthTraverseMap(Mgraph mgraph) {
    Boolean visited[MAX_VERTEX_NUM]={0,};
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
            for (int i = 0; i < mgraph.vexnum; i++) {
                //将当前顶点的未访问邻接点入队
                if (visited[i] == FALSE && (
                        ((mgraph.kind == DG || mgraph.kind == UDG) && mgraph.arcs[cur][i].adj != 0) ||
                        ((mgraph.kind == DN || mgraph.kind == UDN) && mgraph.arcs[cur][i].adj != INFINITY))) {
                    Enqueue(&queue, i);
                }
            }
        }
        //处理非连通图
        if (Emptyqueue(queue)) {
            for (int i = 0; i < mgraph.vexnum; i++) {
                if (!visited[i]) {
                    Enqueue(&queue, i);
                    break;
                }
            }
        }
    }
    printf("\n");

}
