#include <stdlib.h>
#include <stdio.h>
#define MAXN 50
#define MAXM 100

typedef struct e_node
{
    int adjvex;
    int dur;
    int act;
    struct e_node *next;
} E_NODE;

typedef struct
{
    int count;
    E_NODE *link;
} V_NODE;

// 创建AOE 网的邻接表
int creat_adj_list(V_NODE adj[], int n)
{
    int i, u, v, dur, act; // 用交互形式产生有向图的邻接表
    int E[MAXN][4] = {
        // 图 23 AOE 网的边
        {1, 3, 2, 2},
        {1, 2, 3, 1},
        {2, 5, 8, 5}, //*****
        {2, 4, 6, 3},
        {3, 6, 7, 8},
        {3, 4, 3, 4}, //*****
        {4, 6, 2, 7},
        {4, 5, 4, 6},
        {5, 7, 6, 10}, //*****
        {5, 8, 4, 9},
        {6, 9, 6, 12},
        {6, 7, 9, 11}, //*****
        {7, 10, 5, 13},
        {8, 10, 4, 14},
        {9, 10, 8, 15}, //*****
        {0}             // 边结束 ****
    };

    E_NODE *p;
    for (i = 1; i <= n; i++)
    {
        adj[i].count = 0;
        adj[i].link = NULL;
    }
    for (i = 1; i < MAXM; i++)
    {
        printf("输入第%d条边(起点,终点,活动,权值):", i);
        // scanf("%d,%d,%d,%d", &u, &v, &act, &dur);

        u = E[i - 1][0];
        v = E[i - 1][1];
        dur = E[i - 1][2];
        act = E[i - 1][3];                       //   ****
        printf("%d,%d,%d,%d\n", u, v, dur, act); //   ****

        if (u <= 0 || v <= 0)
            break; // 起点或终点为 0 结束输入
        p = (E_NODE *)malloc(sizeof(E_NODE));
        p->adjvex = v;
        p->dur = dur;
        p->act = act;
        p->next = adj[u].link;
        adj[u].link = p;
        (adj[v].count)++;
    }
    return (i - 1); // 返回边数
}

// 输出 AOE 网的邻接表
void prn_adj_list(V_NODE head[], int n)
{
    int i, w;
    E_NODE *p;
    printf("\n AOE 网的边为：\n  ");
    for (i = 1; i <= n; i++) // 对于每个顶点结点
    {
        p = head[i].link;

        while (p != NULL)
        {
            w = p->adjvex;
            printf("(v%d,v%d,a%d=%d), ", i, p->adjvex, p->act, p->dur);
            p = p->next;
        }
        printf("\n  ");
    }
}

// 计算事件的最早发生时间 ee
int calculate_ee(V_NODE adj[], int tpv[], int ee[], int n)
{
    E_NODE *t;
    int i, j, k, top;
    for (i = 1; i <= n; i++)
        ee[i] = 0;

    top = 0;
    for (i = 1; i <= n; i++)
        if (adj[i].count == 0)
        {
            adj[i].count = top;
            top = i;
        }
    i = 0;
    while (top != 0)
    {
        j = top;
        top = adj[top].count;
        tpv[++i] = j;
        t = adj[j].link;
        while (t != NULL)
        {
            k = t->adjvex; // 插入求 ee(k) 的语句
            if (ee[k] < ee[j] + t->dur)
                ee[k] = ee[j] + t->dur;
            if (--(adj[k].count) == 0)
            {
                adj[k].count = top;
                top = k;
            }
            t = t->next;
        }
    }
    return (i);
}

// 计算 le
void calculate_le(adj, tpv, le, path_len, n)
    V_NODE adj[];
int le[], tpv[], n, path_len;
{
    int i, j, k;
    E_NODE *t;
    for (i = 1; i <= n; i++)
        le[i] = path_len;       // le[i] 赋初值为ee[n]
    for (i = n - 1; i > 0; i--) // 按拓扑序列逆序进行处理
    {
        k = tpv[i];
        t = adj[k].link; // 取边的开始顶点
        while (t != NULL)
        {
            j = t->adjvex; // 取边的结束顶点
            if (le[k] > le[j] - (t->dur))
                le[k] = le[j] - (t->dur);
            t = t->next;
        }
    }
}

// 计算活动的最早开始时间 e
void calculate_e(adj, ee, e, n)
    V_NODE adj[];
int n, ee[], e[];
{
    int i, j;
    E_NODE *t;
    for (j = 1; j < n; j++)
    {
        t = adj[j].link;
        while (t != NULL)
        {
            i = t->act;
            e[i] = ee[j];
            t = t->next;
        }
    }
}

// 计算活动的最迟开始时间 l
void calculate_l(adj, le, l, n)
    V_NODE adj[];
int n, le[], l[];
{
    int i, j, k;
    E_NODE *t;
    for (k = 1; k <= n; k++)
    {
        t = adj[k].link;
        while (t != NULL)
        {
            j = t->adjvex;
            i = t->act;              // 取边的终点、活动编号
            l[i] = le[j] - (t->dur); // 按公式计算 l[i]
            t = t->next;
        }
    }
}

// 以图 23 AOE 网为例
int main()
{
    V_NODE head[MAXN];
    int n = 10, count, m, l[MAXM], e[MAXM],
        ee[MAXN], le[MAXN], tpv[MAXN], i;
    m = creat_adj_list(head, n); // 产生邻接表,并返输入的边数
    prn_adj_list(head, n);

    count = calculate_ee(head, tpv, ee, n);
    if (count < n)
        printf("AOE网中存在环路!\n");
    else
    {
        printf("\n 事件的最早发生时间 ee 为：");
        for (i = 1; i <= n; i++)
            printf("%d,", ee[i]);

        calculate_le(head, tpv, le, ee[n], n);
        printf("\n\n 事件的最迟发生时间 le 为：");
        for (i = 1; i <= n; i++)
            printf("%d,", le[i]);

        calculate_e(head, ee, e, n);
        printf("\n\n 活动的最早开始时间  e 为：");
        for (i = 1; i <= m; i++)
            printf("%d,", e[i]);

        calculate_l(head, le, l, n);
        printf("\n\n 活动的最迟开始时间  l 为：");
        for (i = 1; i <= m; i++)
            printf("%d,", l[i]);

        printf("\n\n 活动的余量  l[i]-e[i] 为：");
        for (i = 1; i <= m; i++)
            printf("%d,", l[i] - e[i]);

        printf("\n\n 关键活动为：");
        for (i = 1; i <= m; i++)
            if (e[i] == l[i])
                printf("a%d,", i);
        printf("\n\n ");
    }
}