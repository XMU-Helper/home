#include <stdio.h>
#include <stdlib.h>
#define MAXN 50 // 最大顶点数

struct e_node
{
    int adjvex; // 定义边结点的结构
    int weight; // 若不是带权图,该域可省
    struct e_node *next;
};
typedef struct e_node E_NODE; // 定义边结点的数据类型

struct v_node
{
    int vertex;
    E_NODE *link;
}; // 定义顶点结点的结构

typedef struct v_node V_NODE; // 定义顶点结点的数据类型

// 生成邻接表
void creat_adj_list(V_NODE head[], int n, int t)
{
    int i = 1, w = 1, v = 1, j;
    E_NODE *p;
    for (j = 1; j <= n; j++) // 顶点结点初始化, 信息设为编号
    {
        head[j].link = NULL;
        head[j].vertex = j;
    }

    while ((v > 0) && (w > 0))
    {
        printf("输入第%d条边的(起点,终点):", i);
        scanf("%d,%d", &v, &w);
        if ((v > n) || (w > n))
        {
            printf("顶点编号>%d! 请重输。", n);
            continue;
        }
        if ((v > 0) && (w > 0))
        {
            p = (E_NODE *)malloc(sizeof(E_NODE)); // 存w
            p->adjvex = w;                        // 终点为 w 的边结点链到第 v 个链表
            p->next = head[v].link;
            head[v].link = p;
            if (t == 0) // 若为无向图
            {
                p = (E_NODE *)malloc(sizeof(E_NODE)); // 存 v
                p->adjvex = v;                        // 终点为 v 的边结点链到第w 个链表
                p->next = head[w].link;
                head[w].link = p;
            }
            i++;
        }
    }
}

// 输出邻接表各条边
void prn_adj_list(V_NODE head[], int n)
{
    int i, v, w;
    E_NODE *p;
    for (i = 1; i <= n; i++)
    {
        p = head[i].link;
        v = head[i].vertex;
        while (p != NULL)
        {
            w = p->adjvex;
            printf("(v%d,v%d)\n", v, w);
            p = p->next;
        }
    }
}

int main()
{
    V_NODE head[MAXN]; // 在 main 里定义顶点结点的数组
    int n = 6;

    creat_adj_list(head, n, 1);
    prn_adj_list(head, n);
}