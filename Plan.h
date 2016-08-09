#ifndef PLAN_H
#define PLAN_H

#include <stdio.h>  //标准头文件
#include <stdlib.h> //标准头文件
#include <string.h> //用于课程名称的比较
#include <time.h>   //用于随机数的产生
#include "Graph.h"  //用于图的相关操作
#define MAX_COURSE 100  //课程数最大为100
#define MAX_TERM 12 //学期数最大为12
#define COURSE_ID_LENTH 4   //课程名称长度最大为3，定义为4是因为数组最后还有个'\0'

extern int indegree[MAX_COURSE];    //图结点入度集
extern int previsited[MAX_COURSE];  //已访问并查集
extern int bacvisited[MAX_COURSE];  //伪已访问并查集

typedef struct {
    char id[COURSE_ID_LENTH];   //课程名称长度
    float point;  //课程学分
} Backup;   //课程信息备份结构体

Backup *course; //课程信息备份动态数组指针

void ifnFile(FILE **fpPri, FILE **fpSca); //判断文件是否可以打开
void Scanf(Graph1 *G, int *term_num, float *max_point, int *course_num, int *rela_num, FILE *fpSca);   //读取信息函数（文件读取或键盘读取）
void Graph(Graph1 *G, int course_num, int rela_num, FILE *fpSca);   //建图函数
void Topo(Graph1 *G, int *Top, int *count_num1, int *count_num2,int term_num, int max_point, FILE *fpPri); //拓扑排序函数
void Model(int Top[], Graph1 *G, int term_num, float max_point, int *count_num1, int *count_num2, FILE *fpPri);  //教学编排模式函数
void Sort1(int Top[], Graph1 *G, int term_num, float max_point, int *count_num1, int *count_num2, FILE *fpPri);  //编排模式1
void Sort2(int Top[], Graph1 *G, int term_num, float max_point, int *count_num1, int *count_num2, FILE *fpPri);  //编排模式2
void Color(Graph1 *G, int v);   //并查集染色函数
void Opti1(Graph1 *G,int Top[], int i, int term_num, float max_point, int *count_num1, int *count_num2, FILE *fpPri);   //优化函数1
void Opti2(Graph1 *G,int Top[], int i, int term_num, float max_point, int *count_num1, int *count_num2, FILE *fpPri);   //优化函数2

#endif // PLAN_H
