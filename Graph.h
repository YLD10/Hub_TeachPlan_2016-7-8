#ifndef GRAPH_H
#define GRAPH_H

#define MAX_GRAPH 100

typedef struct {
  int V;  // 结点的数目
  int E;  // 边的数目
  int adjMatrix[MAX_GRAPH][MAX_GRAPH];  // 邻接矩阵二维数组
} Graph1;   //图结构体

void InitGraph(Graph1 *G);  //图初始化函数
void CreateGraph(Graph1 *G, int v_num, int e_num, FILE *fpSca); //建图函数
void PrintGraph(Graph1 *G); //图打印函数

#endif
