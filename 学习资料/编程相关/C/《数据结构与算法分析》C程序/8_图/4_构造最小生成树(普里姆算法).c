#define MAXE 20
#include <stdio.h>
#include <stdlib.h>
#define INFINITE 9999 // 用 9999 表示 ∞
#define MAXN 100

void prim(int cost[][MAXN], int n, int v)
{
    int lowcost[MAXN], min, closest[MAXN], i, j, k;
    for (i = 1; i <= n; i++) // 从顶点 v 开始
    {
        lowcost[i] = cost[v][i];
        closest[i] = v;
    } // 见图13(a)
    for (i = 1; i < n; i++)
    {
        min = INFINITE;
        for (j = 1; j <= n; j++) // 在V-U中找出离 U 最近的顶点
            if ((lowcost[j] != 0) && (lowcost[j] < min))
            {
                min = lowcost[j];
                k = j;
            }
        printf("  边:(%d, %d), 权:%d\n", closest[k], k, min);
        lowcost[k] = 0;          // 标记 k 已经加入 U
        for (j = 1; j <= n; j++) // 修改数组 lowcost 和 closest
            if ((cost[k][j] != 0) && (cost[k][j] < lowcost[j]))
            {
                lowcost[j] = cost[k][j];
                closest[j] = k;
            }
    }
}

int main()
{
    int cost[][MAXN] = {{0},
                        {0, 0, 5, 2, 20, INFINITE, 15, INFINITE},
                        {0, 5, 0, INFINITE, 3, 8, INFINITE, 6},
                        {0, 2, INFINITE, 0, INFINITE, INFINITE, 25, INFINITE},
                        {0, 20, 3, INFINITE, 0, INFINITE, 14, 16},
                        {0, INFINITE, 8, INFINITE, INFINITE, 0, INFINITE, 12},
                        {0, 15, INFINITE, 25, 14, INFINITE, 0, 10},
                        {0, INFINITE, 6, INFINITE, 16, 12, 10, 0}}; // 图12 的邻接矩阵

    printf("用普里姆算法构造最小生成树的边:\n");
    prim(cost, 7, 1);
    printf("\n");
}
