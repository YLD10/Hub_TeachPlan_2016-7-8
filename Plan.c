#include "Plan.h"

//判断文件是否能打开
void ifnFile(FILE **fpPri, FILE **fpSca) {
    if ((*fpSca = fopen("E:\\Data_Struct\\Project design\\Teach plan\\TestScanf.txt", "a+")) == NULL) {    //a+ 表示文件可读可写（文件路径请自定义）
        puts("Can not open the TestScanf.txt !");   //若无法打开数据录入文件，提示错误并退出程序
        puts("");   //换行美化
        system("pause");    //程序暂停
        exit(0);    //退出程序
    }

    if ((*fpPri = fopen("E:\\Data_Struct\\Project design\\Teach plan\\TestPrintf.txt", "a+")) == NULL) { //a+ 表示文件可读可写（文件路径请自定义）
        puts("Can not open the TestPrintf.txt !");  //若无法打开数据导出文件，提示错误并退出程序
        puts("");   //换行美化
        system("pause");    //程序暂停
        exit(0);    //退出程序
    }
}

//读取数据
void Scanf(Graph1 *G, int *term_num, float *max_point, int *course_num, int *rela_num, FILE *fpSca) {
    int i;  //计数器

    fscanf(fpSca, "%d%f%d", term_num, max_point, course_num);    //读取数据录入文件中的前三个数据，分别赋予学期总数（整型），学分上限（浮点型），总课程数（整型）
    do {
        printf("请输入学期总数：%d", *term_num);
        //scanf("%d", term_num);
        if (*term_num > MAX_TERM)   //防止学期总数溢出
            printf("\t学期总数不得超过%d！\n", MAX_TERM);
    }while (*term_num > MAX_TERM);  //若学期总数溢出则往上循环

    printf("\n请输入每个学期的学分上限：%.1f", *max_point);
    //scanf("%f", max_point);

    do {
        printf("\n请输入总课程数：%d", *course_num);
        //scanf("%d", course_num);
        if (*course_num > MAX_COURSE)   //防止总课程数溢出
            printf("\t课程总数不得超过%d！\n", MAX_COURSE);
    }while (*course_num > MAX_COURSE);  //若总课程数溢出则往上循环

    course = (Backup *)malloc(sizeof(Backup) * (*course_num));    //course 为指向课程信息备份动态数组的指针，现为其数组申请内存空间
    printf("\n请输入每个课程的课程号（不超过%d个字符）：", COURSE_ID_LENTH - 1);
    for (i = 0; i < *course_num; i ++) {
        fscanf(fpSca, "%s", course[i].id);  //循环从数据录入文件中依次把字符串类型的课程名称录入备份数组中
        //scanf("%s", course[i].id);
        printf("%s ", course[i].id);
    }

    printf("\n请输入以上课程对应的学分：");
    for (i = 0; i < *course_num; i ++) {
        fscanf(fpSca, "%f", &course[i].point);   //循环从数据录入文件中依次把浮点类型的学分录入备份数组中
        //scanf("%f", &course[i].point);
        printf("%.1f ", course[i].point);
    }

    printf("\n请输入以上课程之间的关系总数：");
    fscanf(fpSca, "%d", rela_num);  //从数据录入文件中读取一个整型数据赋予课程间的关系总数
    //scanf("%d", rela_num);
    printf("%d", *rela_num);

    Graph(G,*course_num,*rela_num,fpSca);   //调用图创建函数，并把数据录入文件的指针传进去
}
//创建图
void Graph(Graph1 *G, int course_num, int rela_num, FILE *fpSca) {
    InitGraph(G);   //初始化图
    CreateGraph(G,course_num,rela_num,fpSca);   //创建有向图的邻接矩阵
    PrintGraph(G);  //打印图结点与边
}

/*拓扑排序开始*/
void Topo(Graph1 *G, int *Top, int *count_num1, int *count_num2, int term_num, int max_point, FILE *fpPri) {
    int i, j, k, v; //一些计数器变量
    int *indegree_copy = (int *)malloc(G->V * sizeof(int)); //初始化图结点入度拷贝数组
    int *Top_copy = (int *)malloc(G->V * sizeof(int));  //初始化拓扑序列拷贝数组

    for (i = 0; i < G->V; i ++) {   //循环进行两个数组的备份
        indegree_copy[i] = indegree[i];
        Top_copy[i] = Top[i];
    }
    srand((int)time(NULL)); //调用C语言提供的函数初始化随机数种子

    for (i = 0; i < G->V; i ++) //循环图结点个数次，每次找出一个入度为0的图结点录入拓扑序列数组
        for (j = 0; j < MAX_COURSE * (G->V); j ++) { //循环足够多次以便能够产生0~图结点-1之间的全部数字
            v = rand() % G->V;  //调用C语言提供的随机数函数产生0~图结点数-1之间的随机数
            if (indegree_copy[v] == 0) { //寻找入度为0的图结点
                indegree_copy[v] --;  //把该图结点的入度置为-1，防止该图结点在此被二次遍历

                Top[i] = v; //入度为0的图结点编号，也就是课程编号录入拓扑序列数组

                for (k = 0; k < G->V; k ++)
                    if (G->adjMatrix[v][k])  //v 与 K 有关系则进 if
                        indegree_copy[k] --;  //与该图结点关联的顶点的入度递减

                break;  //一旦拓扑序列数组增加了新成员，就退出本层循环
            }
        }
    for (i = 0; i < G->V; i ++)
        if (indegree_copy[i] != -1) {   //如果有图结点入度不为-1，即未入拓扑序列，则证明图中有环，原理自己去百度
            printf("\n\t有环!\n");
            fputs("\n\t有环!\n", fpPri);
            free(G);    //释放图所占的内存
            free(Top);  //释放拓扑序列数组所占的内存
            free(course); //释放课程信息备份数组所占的内存
            free(indegree_copy); //释放入度拷贝数组所占的内存
            free(Top_copy); //释放拓扑序列拷贝数组所占的内存
            fclose(fpPri);  //关闭数据导出文件
            puts("");   //换行美化
            system("pause");    //程序暂停
            exit(0);    //退出程序
    }

    if (!*count_num1 && !*count_num2) { //count_num1,count_num2分别为排课模式1和排课模式2的优化次数。若优化次数均为0，则开始第一次拓扑序列打印
            printf("\n拓扑序列：");
            for (i = 0; i < G->V; i ++) //循环打印拓扑序列
                if (i != G->V - 1)
                    printf("%s ", course[Top[i]].id);   //Top[i] 即为课程编号。课程编号与课程信息备份数组的下标一一对应
                else
                    printf("%s\n", course[Top[i]].id);  //当 i 等于 G->V - 1 ，即要打印拓扑序列最后一个数时，加上换行符
    }
    else {  //排课模式1和排课模式2的优化次数不全为0，即有某个排课模式开始优化了
        for (i = 0; i < G->V; i ++) //循环比较原拓扑序列拷贝数组与更新后的拓扑序列
            if (Top_copy[i] != Top[i])
                break;  //若两个数组的同一位置的元素不相同即两个数组不完全相同则跳出循环，此时 i 不等于 G->V

        if (i == G->V) {    //若上述循环中途未被打破，说明两个数组的元素完全相同，则 i 等于 G->V
            (*count_num1) ++;   //两个优化计数器都加一
            (*count_num2) ++;
            if (*count_num1 < MAX_COURSE * (G->V) * (G->V) && *count_num2 < MAX_COURSE * ( G->V) * (G->V)) { //两个优化计数器均未超过所限优化次数
                free(indegree_copy);    //释放图结点入度拷贝数组所占的内存
                free(Top_copy); //释放拓扑序列拷贝数组所占的内存
                Topo(G,Top,count_num1,count_num2,term_num,max_point,fpPri);   //递归调用自己，直到创造出与原拓扑序列不同的新拓扑序列
            }
            else {  //某个优化计数器超过所限优化次数，即在限定的优化次数内未能找出可行的拓扑序列
                printf("\n\n********** 优化失败！**********\n");
                fputs("\n********** 优化失败！**********\n", fpPri);
                free(G);    //释放图所占的内存
                free(Top);  //释放拓扑序列数组所占的内存
                free(course); //释放课程信息备份数组所占的内存
                free(indegree_copy); //释放入度拷贝数组所占的内存
                free(Top_copy); //释放原拓扑序列拷贝数组所占的内存
                fclose(fpPri);  //关闭数据导出文件
                puts("");   //换行美化
                system("pause");    //程序暂停
                exit(0);    //退出程序
            }
        }
        else {  //若上述循环中途被打破，说明两个数组的元素不完全相同，则 i 不等于 G->V
            printf("\n拓扑序列：");
            for (i = 0; i < G->V; i ++) //循环打印拓扑序列
                if (i != G->V - 1)
                    printf("%s ", course[Top[i]].id);   //Top[i] 即为课程编号。课程编号与课程信息备份数组的下标一一对应
                else
                    printf("%s\n", course[Top[i]].id);  //当 i 等于 G->V - 1 ，即要打印拓扑序列最后一个数时，加上换行符
        }
    }
}
/*拓扑排序结束*/


/*教学编排开始*/

//教学编排模式选择
void Model(int Top[], Graph1 *G, int term_num, float max_point, int *count_num1, int *count_num2, FILE *fpPri) {
    int select; //声明变量

    printf("\n\n请选择排课模式：\n\n");
    puts("\t1.在各学期中的学习负担尽量均匀");
    puts("\t2.课程尽可能地集中在前几个学期");
    printf("\n请输入选择：");
    scanf("%d", &select);   //存储用户选择

    switch (select) {
        case 1: //教学编排模式1
            Sort1(Top,G,term_num,max_point,count_num1,count_num2,fpPri); break;
        case 2: //教学编排模式2
            Sort2(Top,G,term_num,max_point,count_num1,count_num2,fpPri); break;
    }
}

//第一种教学编排模式
void Sort1(int Top[], Graph1 *G, int term_num, float max_point, int *count_num1, int *count_num2, FILE *fpPri) {
    int i, j, k, ave, remain, count = 0, plus, maintain;    //一些变量，其中 count 为记录取余课程数中被选修了的课程数
    float point_sum;    //声明学分和变量

    ave = G->V / term_num;  //课程平均数等于课程总数除以学期总数，不能整除时的结果被计算机默认取整
    remain = G->V % term_num;   //取余课程数等于课程总数整除取余学期总数，课程有余是由课程平均数取整造成的
    plus = ave + 1 ;    //课程平均数未由整除得出，则会出现某些学期所修的课程数比计算机取整后的课程平均数大1
    maintain = ave; //无论课程平均数是否由整除得出，均有一些学期所修的课程数与计算机取整后的课程平均数相同
    memset(previsited,0,sizeof(previsited));    //调用C语言提供的初始化函数初始化已访问幷查集，全置为0。只有在刚进去函数时，已访问幷查集才会被初始化

    if (!*count_num1)   //若优化计数器1为0，则往数据导出文件里打印分割线
        fputs("\n\n——————————————————————————————", fpPri);
    fputs("\n在各学期中的学习负担尽量均匀\n", fpPri); //往数据导出文件里写入数据

    for (i = 0; i < term_num; i ++) {    //循环打印每个学期的课程安排
        k = 0;  //每次进循环都把控制课程平均分配的计数器置为0
        point_sum = 0;  //每次进循环都把学分和置为0
        memset(bacvisited,0,sizeof(bacvisited));    //调用C语言提供的初始化函数初始化伪已访问幷查集，全置为0。每一次进入循环，伪已访问幷查集都会被初始化。
                                                    //注意：在 i 大于0情况下执行此代码时，伪已访问幷查集归零，已访问幷查集不归零。
        printf("\n第%d学期的课程安排：", i+1);
        fputs("\n第", fpPri);    //往数据导出文件里写入数据
        fprintf(fpPri, "%d", i+1);  //往数据导出文件里写入数据
        fputs("学期的课程安排：", fpPri);   //往数据导出文件里写入数据

        for (j = 0; j < G->V; j ++) {   //在拓扑序列中遍历查找符合条件的课程
            if (count < remain) ave = plus; //（因 count 初始化为0，所以若 ave 不是由整除得出的，那么前期 ave 均会是 plus）若已被选修了的取余课程的数目小于初始的取余课程数，让课程平均数加一
            else ave = maintain;    //否则说明初始的取余课程都被选修了，此时取余课程数为0，课程平均数不变

            if (k < ave) {  //若平均数计数器小于课程平均数
                if (!previsited[Top[j]] && !bacvisited[Top[j]]) {   //若 Top[j] 所指的课程未被已访问幷查集和伪已访问幷查集染色，则此课程可成为该学期的教学安排的候选
                    if (course[Top[j]].point > max_point) { //若 Top[j] 所指的课程的学分为大于所给的学分上限
                        printf("\n\nError! 学分上限过低，请修改学分上限！\n");  //报错
                        free(G);    //释放图所占的内存
                        free(Top);  //释放拓扑序列数组所占的内存
                        free(course); //释放课程信息备份数组所占的内存
                        fclose(fpPri);  //关闭数据导出文件
                        puts("");   //换行美化
                        system("pause");    //程序暂停
                        exit(0);    //退出程序
                    }
                    point_sum += course[Top[j]].point;  //候选的课程的学分求和
                    if (point_sum <= max_point) {   //若学分和小于等于所给的学分上限，则该课程可正式入选该学期的课程安排
                        printf("%s ", course[Top[j]].id);
                        fprintf(fpPri, "%s  ", course[Top[j]].id);  //往数据导出文件里写入数据
                        previsited[Top[j]] = 1; //对已被选中的课程进行染色，即已访问幷查集染色
                        Color(G,Top[j]);    //调用染色函数对已被选中的课程的后修课程进行染色，即伪已访问幷查集染色
                        k ++;   //平均数计数器加一
                    }
                }
            }
            else {  //平均数计数器等于课程平均数且前期 ave 均等于 plus,所以此时平均数计数器等于 plus，即取余课程数减一了
                count ++;   //取余课程中被选修了的课程数目加一
                break;  //跳出本层循环
            }
        }
    }
    puts("");   //换行
    for (i = 0; i < G->V; i ++)
        if (!previsited[i]) {   //遍历所有图结点，查看是否有未被已访问幷查集染色的
            fputs("\n\nError! 课程安排不下!\n", fpPri);    //往数据导出文件里写入数据
            printf("\nError! 课程安排不下!\n");
            break;  //打断循环
        }

    Opti1(G,Top,i,term_num,max_point,count_num1,count_num2,fpPri);    //调用优化函数1，传递参数 i 进去。若上述循环被中途打断，则 i 不等于 G->V
}

//第二种教学编排模式
void Sort2(int Top[], Graph1 *G, int term_num, float max_point, int *count_num1, int *count_num2, FILE *fpPri) {
    int i, j;   //声明计数器
    float point_sum;    //声明学分和变量

    memset(previsited,0,sizeof(previsited));     //调用C语言提供的初始化函数初始化已访问幷查集，全置为0

    if (!*count_num2)   //若优化计数器2为0，则往数据导出文件里打印分割线
        fputs("\n\n——————————————————————————————", fpPri);
    fputs("\n课程尽可能地集中在前几个学期\n", fpPri); //往数据导出文件里写入数据

    for (i = 0; i< term_num; i ++) {
        point_sum = 0;  //每次进入循环，学分和置为0
        memset(bacvisited,0,sizeof(bacvisited));    //调用C语言提供的初始化函数初始化伪已访问幷查集，全置为0。每一次进入循环，伪已访问幷查集都会被初始化。
                                                    //注意：在 i 大于0情况下执行此代码时，伪已访问幷查集归零，已访问幷查集不归零。
        printf("\n第%d学期的课程安排：", i+1);
        fputs("\n第", fpPri);    //往数据导出文件里写入数据
        fprintf(fpPri, "%d", i+1);  //往数据导出文件里写入数据
        fputs("学期的课程安排：", fpPri);   //往数据导出文件里写入数据

        for (j = 0; j < G->V; j ++) { //在拓扑序列中遍历查找符合条件的课程
            if (!previsited[Top[j]] && !bacvisited[Top[j]]) {  //若 Top[j] 所指的课程未被已访问幷查集和伪已访问幷查集染色，则此课程可成为该学期的教学安排的候选
                if (course[Top[j]].point > max_point) { //若 Top[j] 所指的课程的学分为大于所给的学分上限
                    printf("\nError!学分上限过低，请修改学分上限！");  //报错
                    free(G);    //释放图所占的内存
                    free(Top);  //释放拓扑序列数组所占的内存
                    free(course); //释放课程信息备份数组所占的内存
                    fclose(fpPri);  //关闭数据导出文件
                    puts("");   //换行美化
                    system("pause");    //程序暂停
                    exit(0);    //退出程序
                }
                point_sum += course[Top[j]].point;  //候选的课程的学分求和
                if(point_sum <= max_point) {     //若学分和小于等于所给的学分上限，则该课程可正式入选该学期的课程安排
                    printf("%s  ", course[Top[j]].id);
                    fprintf(fpPri, "%s  ", course[Top[j]].id);  //往数据导出文件里写入数据
                    previsited[Top[j]] = 1; //对已被选中的课程进行染色，即已访问幷查集染色
                    Color(G,Top[j]);    //调用染色函数对已被选中的课程的后修课程进行染色，即伪已访问幷查集染色
                }
            }
        }
    }
    puts("");   //换行
    for (i = 0; i < G->V; i ++)
        if (!previsited[i]) {   //遍历所有图结点，查看是否有未被已访问幷查集染色的
            fputs("\n\nError! 课程安排不下!\n", fpPri);    //往数据导出文件里写入数据
            printf("\nError! 课程安排不下!\n");
            break;  //打断循环
        }

    Opti2(G,Top,i,term_num,max_point,count_num1,count_num2,fpPri);    //调用优化函数2，传递参数 i 进去。若上述循环被中途打断，则 i 不等于 G->V
}

//幷查集染色
void Color(Graph1 *G, int v) {
    int i;  //计数器

    for (i = 0; i < G->V; i ++) //遍历所有图结点
        if (G->adjMatrix[v][i]) {   //若 v->i 有边
            bacvisited[i] = 1;  //把 i 所指的图结点记录到伪已访问幷查集中，即伪已访问幷查集染色
            Color(G,i); //递归调用染色函数，以 i 为起点，把 i 的后修课程也进行染色
        }
}

//教学编排优化1
void Opti1(Graph1 *G, int Top[], int i, int term_num, float max_point, int *count_num1, int *count_num2, FILE *fpPri) {
    if (i != G->V) {    //若 i 不等于 G->V ，说明在教学编排模式1函数中已报告课程安排不下，此时需进行优化
        (*count_num1) ++;   //优化计数器1加一
        if (*count_num1 < MAX_COURSE * (G->V) * (G->V)) {   //若优化计数器1小于所给定的优化次数上限
            printf("\n优化中......\n");
            fputs("\n优化中......\n", fpPri);
            Topo(G,Top,count_num1,count_num2,term_num,max_point,fpPri);   //调用拓扑排序函数更新拓扑序列
            Sort1(Top,G,term_num,max_point,count_num1,count_num2,fpPri);  //调用教学编排模式1函数，以新拓扑序列为基础进行教学编排
        }
    }
}

//教学编排优化2
void Opti2(Graph1 *G, int Top[], int i, int term_num, float max_point, int *count_num1, int *count_num2, FILE *fpPri) {
    if (i != G->V) {    //若 i 不等于 G->V ，说明在教学编排模式1函数中已报告课程安排不下，此时需进行优化
        (*count_num2) ++;   //优化计数器2加一
        if (*count_num2 < MAX_COURSE * (G->V) * (G->V)) {   //若优化计数器2小于所给定的优化次数上限
            printf("\n优化中......\n");
            fputs("\n优化中......\n", fpPri);
            Topo(G,Top,count_num1,count_num2,term_num,max_point,fpPri);   //调用拓扑排序函数更新拓扑序列
            Sort2(Top,G,term_num,max_point,count_num1,count_num2,fpPri);  //调用教学编排模式2函数，以新拓扑序列为基础进行教学编排
        }
    }
}

/*教学编排结束*/
