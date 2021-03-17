#include <stdio.h>
#define MAXE 20

struct edge
{
    int u;
    int v;
    int w;
}; // 边的三元组结构
typedef struct edge EDGE;

int seeks(int set[], int v) // 求连通分量后一个顶点
{
    int i = v;
    while (set[i] > 0)
        i = set[i];
    return (i);
}

void kruskal(EDGE E[MAXE], int n, int e) //边从小到大排列
{
    int v1, v2, i, j;
    int set[MAXE] = {0};   // 每个顶点都是一连通分量
    i = 0;                 // 选取的边在 E[ ]中的下标，初值为 0
    j = 0;                 // T 中已生成的边记数，初值为 0
    while (j < n && i < e) // 逐条检查选取的边是否加入到 T 中
    {
        v1 = seeks(set, E[i].u); // 确定顶点所在的连通分量
        v2 = seeks(set, E[i].v);
        if (v1 != v2) // 选取边的两个端点在同一连通分量
        {
            printf("  (%d,%d)\n", E[i].u, E[i].v); // 边加入 T 中
            set[v1] = v2;                          // 两个连通分量合并成一个连通分量
            j++;                                   // T 的边数加1
        }
        i++; // 选取的 E[ ] 中下一条边
    }
}

int main()
{
    EDGE E[] = {{1, 3, 2}, {2, 7, 3}, {4, 6, 4}, {5, 7, 5}, {3, 4, 6}, {2, 5, 7}, {1, 4, 8}, {4, 7, 11}, {3, 6, 12}, {6, 7, 14}, {1, 2, 15}, {2, 4, 18}}; // 图14 的三元组

    printf("用克鲁斯卡尔算法构造最小生成树的边:\n");
    kruskal(E, 7, 12);
    printf("\n");
}