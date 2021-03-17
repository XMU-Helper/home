#include <stdio.h>
#include <stdlib.h>
#define MAXN 50  // 最大顶点数
#define MAXM 100 // 最大边数

typedef struct e_node // 定义边结点的数据类型
{
    int adjvex;
    struct e_node *next;
} E_NODE;
typedef struct // 定义顶点结点的数据类型
{
    int count;
    E_NODE *link;
} V_NODE;

// 用交互形式产生有向图的邻接表
int creat_adj_list(V_NODE adj[], int n)
{
    E_NODE *p;
    int i, u, v;

    int E[][2] = {1, 3, 1, 8, 2, 5, 2, 3, 3, 4, 4, 7, 4, 6, 5, 6, 5, 4, 8, 9, 9, 7, 0, 0}; // XXXXXX 图19 的边

    for (i = 1; i <= n; i++)
    {
        adj[i].count = 0;
        adj[i].link = NULL;
    }

    for (i = 1; i < MAXM; i++)
    {
        printf("输入第%d条边:", i);
        // scanf("%d%d",&u,&v);
        u = E[i - 1][0];
        v = E[i - 1][1];
        printf("%d, %d\n", u, v); // XXX

        if (u <= 0 || v <= 0)
            break; // 起点或终点为 0 结束输入
        p = (E_NODE *)malloc(sizeof(E_NODE));
        p->adjvex = v;
        p->next = adj[u].link;
        adj[u].link = p;
        (adj[v].count)++;
    }
    return (i - 1); // 返回边数
}

// 拓扑排序
int topol_order(V_NODE adj[], int n, int tpv[])
{
    int i, j, k;
    int top = 0; // top 为入度为 0 的顶点栈顶指针
    E_NODE *t;
    for (i = 1; i <= n; i++) // 建立入度为 0 的顶点的堆栈
        if (adj[i].count == 0)
        {
            adj[i].count = top;
            top = i;
        }
    i = 0;
    while (top != 0)
    {
        j = top;              // 取得栈顶的顶点 j
        top = adj[top].count; // 度数为 0 的顶点出栈操作
        tpv[++i] = j;         // 输出顶点 j
        t = adj[j].link;      // 取邻接表的第 j 个链表表头结点
        while (t != NULL)
        {
            k = t->adjvex;             // 取顶点值
            if (--(adj[k].count) == 0) // 顶点 k 的入度减 1 后为 0
            {
                adj[k].count = top;
                top = k;
            }            // 顶点 k 进栈
            t = t->next; // 顶点 j 的下一个后继结点
        }
    }
    return (i); // 返回顶点数
}

// 以图19 为例
int main()
{
    V_NODE head[MAXN];          // 定义顶点结点的表头数组
    int n, i, count, tpv[MAXN]; // 数组 tpv 存放拓扑序列

    //  printf ("输入顶点数目 n=");  scanf("%d", &n);
    n = 9;

    creat_adj_list(head, n);
    count = topol_order(head, n, tpv);
    if (count < n)
        printf("图中存在回路！\n");
    else
    {
        printf("拓扑序列为：");
        for (i = 1; i <= n; i++)
            printf("%4d", tpv[i]);
        printf("\n");
    }
}