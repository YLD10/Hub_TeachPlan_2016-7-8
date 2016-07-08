#include "Plan.h"

int indegree[MAX_COURSE] = {0}; //初始化图结点入度集
int previsited[MAX_COURSE] = {0};   //初始化已访问并查集
int bacvisited[MAX_COURSE] = {0};   //初始化伪已访问并查集

int main()
{
    Graph1 *G = (Graph1 *)malloc(sizeof(Graph1));   //初始化图指针
    int term_num, course_num, rela_num, count_num1 = 0, count_num2 = 0;  //一些变量
    float  max_point;

    Scanf(G,&term_num,&max_point,&course_num,&rela_num);    //调用数据录入函数

    int *Top = (int *)malloc((course_num)*sizeof(int)); //拓扑序列动态数组初始化

    Topo(G,Top,&count_num1,&count_num2,term_num,max_point);     //调用拓扑排序函数

    Model(Top,G,term_num,max_point,&count_num1,&count_num2);    //调用教学编排模式函数

    free(G);    //释放图所占的内存
    free(Top);  //释放拓扑序列数组所占的内存
    free(course); //释放课程信息备份数组所占的内存

    return 0;   //程序结束
}
