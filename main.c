#include "Plan.h"

int indegree[MAX_COURSE] = {0}; //初始化图结点入度集
int previsited[MAX_COURSE] = {0};   //初始化已访问并查集
int bacvisited[MAX_COURSE] = {0};   //初始化伪已访问并查集

int main()
{
    Graph1 *G = (Graph1 *)malloc(sizeof(Graph1));   //初始化图指针
    int term_num, course_num, rela_num, count_num1 = 0, count_num2 = 0;  //一些变量
    float  max_point;
    FILE *fpSca;    //指向外部导入数据的文件指针，数据录入文件中的数据以空格和回车作为分隔符
    FILE *fpPri;    //指向外部导出数据的文件指针

    ifnFile(&fpPri,&fpSca); //调用文件判断函数（需传递二级指针，否则返回 main 函数时两个文件指针指向不明，即未进行赋址）

    Scanf(G,&term_num,&max_point,&course_num,&rela_num,fpSca);    //调用数据录入函数

    int *Top = (int *)malloc(sizeof(int) * course_num); //拓扑序列动态数组初始化

    Topo(G,Top,&count_num1,&count_num2,term_num,max_point,fpPri);     //调用拓扑排序函数

    Model(Top,G,term_num,max_point,&count_num1,&count_num2,fpPri);    //调用教学编排模式函数

    free(G);    //释放图所占的内存
    free(Top);  //释放拓扑序列数组所占的内存
    free(course); //释放课程信息备份数组所占的内存
    fclose(fpSca);  //关闭数据导入文件
    fclose(fpPri);  //关闭数据导出文件
    puts("");   //换行美化
    system("pause");    //程序暂停

    return 0;   //程序结束
}
