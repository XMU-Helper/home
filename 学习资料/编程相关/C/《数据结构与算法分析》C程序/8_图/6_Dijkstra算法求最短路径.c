#include <stdio.h>
#define MAXVEX 50      // 定义最大顶点数
#define INFINITE 32767 // 用 32767 表示 ∞

// Dijkstra 算法求最短路径
void shortest_path(cost, dist, path, n, v0) int cost[][MAXVEX], dist[], path[], n, v0;
{
    int s[MAXVEX], i, j, k, min;
    for (i = 1; i <= n; i++) // 初始化
    {
        dist[i] = cost[v0][i];
        s[i] = 0; // 距离初始化,S 置空
        if (cost[v0][i] < INFINITE)
            path[i] = v0; // 路径初始化
        else
            path[i] = 0;
    }
    path[v0] = 0;
    s[v0] = 1; // 源点 v0 放在 S 中

    for (i = 1; i <= n; i++) // 重复直到所有顶点的最短路径都求出
    {
        min = INFINITE;
        k = 0;
        for (j = 1; j <= n; j++)
            if (s[j] == 0 && dist[j] < min) // 选取不在S中且具有最小距离的顶点 k
            {
                min = dist[j];
                k = j;
            }
        s[k] = 1;                // 把顶点 k 加入 S 中
        for (j = 1; j <= n; j++) // 修改不在 S 中的顶点的距离
            if (s[j] == 0)
                if (cost[k][j] < INFINITE && dist[k] + cost[k][j] < dist[j])
                {
                    dist[j] = dist[k] + cost[k][j];
                    path[j] = k;
                }
    }
}

// 输出最短路径
void print_path(int dist[], int path[], int n, int v0)
{
    int i, k;
    for (i = 1; i <= n; i++)
    {
        printf("%d到%d的最短路径为：", v0, i);
        k = i;
        while (k != v0)
        {
            printf("%d<-", k);
            k = path[k];
        }
        printf("%d", k);
        printf(", 长度为: %d\n", dist[i]);
    }
}

// 输出邻接矩阵
void print_cost(int cost[][MAXVEX], int n)
{
    int i, j;
    for (i = 1; i <= n; i++)
    {
        for (j = 1; j <= n; j++)
            if (cost[i][j] == INFINITE)
                printf("  ∞");
            else
                printf("%4d", cost[i][j]);
        printf("\n");
    }
}

int main() // 以图 15为例
{
    int dist[MAXVEX], path[MAXVEX], n = 7;
    int cost[][MAXVEX] = {{0}, // 下标为0 的行和列不用
                          {0, 0, 15, INFINITE, 4, INFINITE, INFINITE, INFINITE},
                          {0, INFINITE, 0, INFINITE, INFINITE, 2, INFINITE, 8},
                          {0, 9, INFINITE, 0, INFINITE, INFINITE, INFINITE, INFINITE},
                          {0, INFINITE, 5, INFINITE, 0, INFINITE, 6, INFINITE},
                          {0, INFINITE, INFINITE, INFINITE, INFINITE, 0, INFINITE, 3},
                          {0, INFINITE, INFINITE, 12, INFINITE, INFINITE, 0, 16},
                          {0, INFINITE, INFINITE, INFINITE, 11, INFINITE, INFINITE, 0}};
    print_cost(cost, n);
    shortest_path(cost, dist, path, n, 1);
    print_path(dist, path, n, 1); // 输出最短路径
}
