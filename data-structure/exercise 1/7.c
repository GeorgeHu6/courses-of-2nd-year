#include <stdio.h>
#include <stdlib.h>
//define the relative location of east, west, south and north
#define EAST  MAZE[x][y+1]
#define WEST  MAZE[x][y-1]
#define SOUTH MAZE[x+1][y]
#define NORTH MAZE[x-1][y]

struct list {
    int x, y;
    struct list *next;
};

typedef struct list node;
typedef node *link;
//2-dimension array to define map of maze
int MAZE[10][12] = {1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1,
                    1, 2, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1,
                    1, 1, 1, 0, 1, 1, 0, 0, 0, 0, 1, 1,
                    1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1,
                    1, 1, 1, 0, 0, 0, 0, 1, 1, 0, 1, 1,
                    1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1,
                    1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1,
                    1, 1, 1, 0, 1, 1, 0, 0, 1, 0, 1, 1,
                    1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 3, 1,
                    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
//int MAZE[6][5] = {1, 1, 1, 0, 1,
//                  1, 0, 2, 1, 1,
//                  1, 0, 0, 0, 1,
//                  1, 0, 1, 3, 1,
//                  1, 0, 0, 0, 1,
//                  1, 1, 1, 1, 1};

link push(link stack, int x, int y) {
    link newnode;
    newnode = (link) malloc(sizeof(node));
    if (!newnode) {
        printf("Memory Error!");
        return NULL;
    }
    newnode->x = x;
    newnode->y = y;
    newnode->next = stack;
    return newnode;
}

//enhance the logic of pop
link pop(link stack, int *x, int *y) {
    link top = stack;
    //back to last step
    stack = stack->next;
    if (stack != NULL) {
        *x = stack->x;
        *y = stack->y;
        free(top);
    } else {
        //back to the beginning, means no way to exit
        *x = -1;
    }
    return stack;
}

//rewrite the logic of chkExit
//able to reach exit from (x,y) directly
int chkExit(int x, int y) {
    return SOUTH == 3 || WEST == 3 || NORTH == 3 || EAST == 3;
}

int main() {
    int i, j, x, y;
    int m, n;
    //flag used for main loop
    int flag = 0;
    link path = NULL;
    //initial entrance coordinate
    x = 1, y = 1;
    //initial the size of MAZE
    m = 10, n = 12;
    printf("MAZE map (1 for wall, 0 for road, 2 for entrance, 3 for exit):\n");
    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++)
            printf("%2d", MAZE[i][j]);
        printf("\n");
    }

    while (flag != 1) {
        //walk to north, south, west and east in sequence
        if (NORTH == 0) {
            x -= 1;
            path = push(path, x, y);
        } else if (SOUTH == 0) {
            x += 1;
            path = push(path, x, y);
        } else if (WEST == 0) {
            y -= 1;
            path = push(path, x, y);
        } else if (EAST == 0) {
            y += 1;
            path = push(path, x, y);
        } else if (chkExit(x, y) != 0) {
            //set flag to 1 if reach the exit
            flag = 1;
        } else {
            //use 2 to mark the road to dead end
            MAZE[x][y] = 2;
            //dead end, get back to previous position
            path = pop(path, &x, &y);
            //unreachable maze, mark to quit the loop
            if (x == -1)
                flag = 1;
        }
        //use 6 to mark passed road
        MAZE[x][y] = 6;
    }

    //distinguish unreachable maze
    if (path == NULL) {
        printf("No chance to get out of the maze :(");
    } else {
        //display the map with trace 6
        printf("---------------------------\n");
        printf("6 for the passed road.\n");
        printf("---------------------------\n");
        for (i = 0; i < m; i++) {
            for (j = 0; j < n; j++)
                printf("%2d", MAZE[i][j]);
            printf("\n");
        }
    }

    system("pause");
    return 0;
}
