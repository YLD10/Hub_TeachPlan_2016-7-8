#include "Plan.h"

/*邻接矩阵开始*/

//图初始化
void InitGraph(Graph1 *G) {
    int i, j;   //计数器

    G->V = 0;   //图结点数置零
    G->E = 0;   //图边数置零
    for (i = 0; i < MAX_GRAPH; i++) //初始化为零图
        for (j = 0; j < MAX_GRAPH; j++)
            G->adjMatrix[i][j] = 0;
}

//创建有向图
void CreateGraph(Graph1 *G, int v_num, int e_num, FILE *fpSca) {
    int i, j, a = MAX_COURSE, b = MAX_COURSE; //i、j为计数器，a、b为课程最大数
    char v[COURSE_ID_LENTH], u[COURSE_ID_LENTH];    //课程名存储

    G->V = v_num;   //记录图结点数
    G->E = e_num;   //记录图边数

    puts("\n请输入每个课程之间的先修关系：\n");
    for (i = 0; i < G->E; i ++) {   //循环录入两图结点间的有向边
        fscanf(fpSca, "%s%s", v, u);    //从数据录入文件中读取图结点之间的关系即有向边数据赋予 v 和 u， v->u
        printf("%s %s\n", v, u);
        //scanf("%s%s", v, u);
        for (j = 0; j < G->V; j ++) {
            if (strcmp(v,course[j].id) == 0)     //循环比较，找出 v 所对应的课程编号，即课程备份数组中的下标
                a = j;
            if (strcmp(u,course[j].id) == 0)    //循环比较，找出 u 所对应的课程编号，即课程备份数组中的下标
                b = j;
        }
        if (a == MAX_COURSE) { //若 a 值不被上述循环所改变仍为 MAX_COURSE ，则说明找不到此课程
            printf("\nError！%s课程不在本专业开设的课程中！\n", v);
            free(course);   //释放课程信息备份数组所占的内存
            exit(0);    //退出程序
        }
        if (b == MAX_COURSE) { //若 b 值不被上述循环所改变仍为 MAX_COURSE ，则说明找不到此课程
            printf("\nError！%s课程不在本专业开设的课程中！\n", u);
            free(course);   //释放课程信息备份数组所占的内存
            exit(0);    //退出程序
        }

        G->adjMatrix[a][b] = 1; //给有先修关系的两个图结点构建有向边 a->b
        indegree[b] ++; //b 所代表的图结点入度加一
    }
    fclose(fpSca);  //关闭数据录入文件
}

//打印图结点和边
void PrintGraph(Graph1 *G) {
    int i, j;   //计数器

    printf("\na graph with %d verteies and %d edges\n\n", G->V, G->E);
    for (i = 0; i < G->V; i ++) //两层循环打印邻接矩阵存储的有向边
        for (j = 0; j < G->V; j ++)
            if (G->adjMatrix[i][j]) //有边则 G->adjMatrix[i][j] 为1
                printf("%s -- %s\n", course[i].id, course[j].id);   //邻接矩阵的某行某列所代表的图结点与课程信息备份数组的下标一一对应
}

/*邻接矩阵结束*/
