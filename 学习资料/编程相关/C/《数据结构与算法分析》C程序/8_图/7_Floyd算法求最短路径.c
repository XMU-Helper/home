#include <stdio.h>
#define MAXN 100      // 定义最大顶点数
#define INFINITE 9999 // 用 9999 表示 ∞

typedef int MAT[MAXN][MAXN];

// Floyd 算法求每对顶点之间的最短路径
void floyd(MAT cost, MAT a, MAT path, int n)
{
    int i, j, k;
    for (i = 1; i <= n; i++) // 初始化矩阵 a 和 path
        for (j = 1; j <= n; j++)
        {
            a[i][j] = cost[i][j];
            path[i][j] = 0;
        }
    for (k = 1; k <= n; k++)     // 求 a(k)
        for (i = 1; i <= n; i++) // 计算递推公式
            for (j = 1; j <= n; j++)
                if (a[i][k] + a[k][j] < a[i][j])
                {
                    a[i][j] = a[i][k] + a[k][j];
                    path[i][j] = k;
                }
}

// 输出从 i 到 j 的最短路径的所有中间顶点
void print_path(MAT path, int i, int j)
{
    int k;
    k = path[i][j];
    if (k == 0)
        return;
    print_path(path, i, k);
    printf("%d,", k);
    print_path(path, k, j);
}

// 输出所有最短路径
void print_all_path(MAT a, MAT path, int n)
{
    int i, j;
    for (i = 1; i <= n; i++)
        for (j = 1; j <= n; j++)
            if (a[i][j] < INFINITE)
            {
                if (i != j)
                {
                    printf("顶点%d到%d的路径为", i, j);
                    printf("<%d,", i);
                    print_path(path, i, j);
                    printf("%d>", j);
                    printf("，其长度为%d;\n", a[i][j]);
                }
            }
            else
                printf("顶点 %d 到 %d 没路径!\n", i, j);
}

int main() // 以图17为例
{
    int n = 4;
    MAT path = {0}, a = {0};
    MAT cost = {{0, 0, 0, 0}, // 下标为 0 的行和列不使用
                {0, 0, 1, INFINITE, 4},
                {0, INFINITE, 0, 9, 2},
                {0, 3, 5, 0, 8},
                {0, INFINITE, INFINITE, 6, 0}};

    floyd(cost, a, path, n);
    print_all_path(a, path, n); // 输出所有最短路径
}
