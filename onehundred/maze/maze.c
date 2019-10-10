#include "maze.h"

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#define MA_LINE 21
#define MA_ROW 21
#define END_X 19
#define END_Y 19

struct Node {
    int bit;
    PtrToNode next;
} ;

void feri_error(const char *string, int line)
{
    printf("%s, line is %d\n", string, line);
}

int is_empty(Stack S)
{
    return S->next == NULL ? 1 : 0;
}

void pop(Stack S)
{
    if (is_empty(S)) {
        feri_error("the stack is is_empty\n", __LINE__);
    } else {
        PtrToNode tmp = S->next;
        S->next = tmp->next;
        free(tmp);
    }
}

void push(Stack S, int bit)
{
    PtrToNode tmp = (PtrToNode)malloc(sizeof(struct Node));
    if (tmp == NULL) {
        feri_error("malloc tmp was failed\n", __LINE__);
    } else {
        tmp->bit = bit;
        tmp->next = S->next;
        S->next = tmp;
    }
}

void make_empty(Stack S)
{
    if (S == NULL) {
        feri_error("make empty S was failed , because the dummy is null\n", __LINE__);
    } else {
        while (!is_empty(S)) {
            pop(S);
        }
    }
}

Stack create_stack(void)
{
    Stack dummy = (Stack)malloc(sizeof(struct Node));
    if (dummy == NULL) {
        feri_error("malloc dummy out of space", __LINE__);
    }
    dummy->next = NULL;
    make_empty(dummy);
    return dummy;
}

int **book_init()
{
     int **book = (int **)malloc(MA_LINE*sizeof(int *));                                                                                                        
      for (int i = 0; i < MA_LINE; i++) {
          book[i] = (int *)malloc(MA_ROW*sizeof(int));
      }   
      for (int i = 0; i < MA_LINE; i++) {   
          for (int j = 0; j < MA_ROW; j++) {
              book[i][j] = 0;                
          }                                  
      }                                      
      return book;
}

char **maze_init()
{
    char **maze = (char **)malloc(MA_LINE*sizeof(char *));
    for (int i = 0; i < MA_LINE; i++) {
        maze[i] = (char *)malloc(MA_ROW*sizeof(char));
    }
    for (int i = 0; i < MA_LINE; i++) {
        if (i%2 == 0) {
            for (int j = 0; j < MA_ROW; j++) {
                maze[i][j] = '#';
            }
        } else {
            for (int j = 0; j < MA_ROW; j++) {
                if (j%2 == 0) {
                    maze[i][j] = '#';
                } else {
                    maze[i][j] = ' ';
                }
            }
        }
    }
    return maze;
}

void maze_output(char **maze)             
{                                         
    for (int i = 0; i < MA_LINE ; i++) {  
        for (int j = 0; j < MA_ROW; j++) {
            printf("%c ", maze[i][j]);    
        }                                 
        printf("\n");                     
    }                                     
}                                         

void maze_output_way(char **maze, int **book)             
{                                         
    for (int i = 0; i < MA_LINE ; i++) {  
        for (int j = 0; j < MA_ROW; j++) {
            printf("%c ", maze[i][j]);    
            if (book[i][j] == 1) {
                maze[i][j] = '*';
                printf("%c", maze[i][j]);
            }
        }                                 
        printf("\n");                     
    }                                     
}                                         


char **maze_dfs_create(char **maze, int **book, Stack dummy, int start_x, int start_y)
{
    push(dummy, 1);
    book[start_x][start_y] = 1;
    while (!is_empty(dummy)) {
        int direction[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
        int loop = 1;
        int sx_r, sy_r, sx_d, sy_d, sx_l, sy_l, sx_u, sy_u, r = 0, l = 0, d = 0, u = 0;
        int nextx, nexty, wallx, wally;
        sx_r = start_x + 0;
        sy_r = start_y + 2;
        sx_d = start_x + 2;
        sy_d = start_y + 0;
        sx_l = start_x + 0;
        sy_l = start_y - 2;
        sx_u = start_x - 2;
        sy_u = start_y + 0;
        if (sy_r == MA_ROW) {
            r = 1;
        } else if (sy_r != MA_ROW && book[sx_r][sy_r] == 1) {
            r = 1;
        }
        if (sx_d == MA_LINE) {                                
            d = 1;                                           
        } else if (sx_d != MA_LINE && book[sx_d][sy_d] == 1) {
            d = 1;                                           
        }                                                    
        if (sy_l == -1) {
            l = 1;
        } else if (sy_l != -1 && book[sx_l][sy_l] == 1) {
            l = 1;
        }
        if (sx_u == -1) {
            u = 1;
        } else if (sx_u != -1 && book[sx_u][sy_u] == 1) {
            u = 1;
        }
        while (loop) {
            if (r == 1 && d == 1 && l == 1 && u == 1) {
                pop(dummy);
                return maze;
            } 
            //srand((int)time(NULL));
            int ne = rand()%4;
            nextx = start_x + 2*direction[ne][0];
            nexty = start_y + 2*direction[ne][1];
            wallx = start_x + direction[ne][0];  
            wally = start_y + direction[ne][1];  
                //printf("%d, %d\n", nextx, nexty);
            if (nextx == -1 || nextx == MA_ROW || nexty == -1 || nexty == MA_LINE) {
                continue;
            } else {
                loop = 0;
                maze[wallx][wally] = ' ';
                maze_dfs_create(maze, book, dummy, nextx, nexty);
            }
        }
    }
    return maze;
}

int **maze_best_way(char **maze, int **book, int startx, int starty, long long int *min ,long long int step, int *lo)
{
    int direction[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    int nex, ney;
    if (startx == END_X && starty == END_Y) {
        if (step < *min) {
            *min = step;
        }
        //*lo = *lo + 1;
        return book;
    }
    for (int i = 0; i < 4; i++) {
        nex = startx + direction[i][0];
        ney = starty + direction[i][1];
        if (nex == 0 || nex == MA_LINE || ney == 0 || ney == MA_ROW) {
            continue;
        }
        if (maze[nex][ney] != '#' && book[nex][ney] == 0) {
            book[nex][ney] = *lo;
            maze_best_way(maze, book, nex, ney, min, step+1, lo);
            book[nex][ney] = 0;
        }
    }
    return book;
}

int main(void)
{
    int **book = book_init();
    char **maze = maze_init();
    Stack dummy = create_stack();
    maze_dfs_create(maze, book, dummy, 1, 1);
    maze_output(maze);
    int **booka = book_init();
    long long int min = 1000000000000000000;
    int lo = 1;
    booka = maze_best_way(maze, booka, 1, 1, &min, 0, &lo);
    printf("至少需要走%lld 步\n", min);
    return 0;
}
