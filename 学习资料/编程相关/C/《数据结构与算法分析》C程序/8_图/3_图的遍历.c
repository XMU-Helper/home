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
    // int EG[MAXN][2]={1,2,1,3,2,4,3,2, 4,6,5,1,6,3,6,4,6,5,0,0};		// 有向图 G2
    // int EG[MAXN][2]={1,2,1,3,1,5,5,6,3,6,2,6,4, 2};					// 无向图 G1
    int EG[MAXN][2] = {1, 2, 1, 3, 2, 3, 5, 6}; // 非连通无向图 G6
                                                //int EG[MAXN][2]={1,2,1,5,2,6,3,2,4,1,4,2,5,2,5,4,5,6,6,3};		// 非连通有向图 G7

    E_NODE *p;
    for (j = 1; j <= n; j++) // 顶点结点初始化, 信息设为编号
    {
        head[j].link = NULL;
        head[j].vertex = j;
    }

    while ((v > 0) && (w > 0))
    { // printf("输入第%d条边的(起点,终点):", i);
        // scanf("%d,%d", &v, &w);
        v = EG[i - 1][0];
        w = EG[i - 1][1];
        if ((v > n) || (w > n))
        {
            printf("顶点编号>%d! 请重输。", n);
            continue;
        }
        if ((v > 0) && (w > 0))
        {
            p = (E_NODE *)malloc(sizeof(E_NODE)); // 存 w
            p->adjvex = w;                        // 终点为 w 的边结点链到第 v 个链表
            p->next = head[v].link;
            head[v].link = p;
            if (t == 1) // 若为无向图
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
void prn_adj_list(V_NODE head[], int n, int t) // 输出邻接表
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
            if (t == 2 || t == 1 && w > v)
                printf("(v%d,v%d)\n", v, w); // 输出一条边
            p = p->next;
        }
    }
}

// 深度优先搜索遍历
void dfs(int v, int visit[], V_NODE head[])
{
    E_NODE *p;
    visit[v] = 1;
    printf("V%d, ", v);
    p = head[v].link;
    while (p != NULL)
    {
        if (visit[p->adjvex] == 0)
            dfs(p->adjvex, visit, head);
        p = p->next;
    }
}

// 广度优先搜索遍历
void bfs(int v, int visit[], V_NODE head[])
{
    E_NODE *p;
    int queue[MAXN];            //  存放队列的数组
    int front = 0, rear = 0, w; // 队列头尾指针初始化,置空
    printf("v%d, ", v);         // 访问初始点 v
    visit[v] = 1;               // 置 v 已被访问的标志
    queue[rear++] = v;          // 让 v 进队
    while (front != rear)       // 若队列不空
    {
        w = queue[front++]; // 队首的顶点出队并送 w
        p = head[w].link;   // 找与顶点w 邻接的顶点
        while (p != NULL)
        {
            if (visit[p->adjvex] == 0) // 若邻接顶点未被访问
            {
                visit[p->adjvex] = 1;       // 置已被访问的标志
                printf("v%d, ", p->adjvex); // 访问该顶点
                queue[rear++] = p->adjvex;  // 该顶点进队
            }
            p = p->next; // 找下一个邻接顶点
        }
    }
}

/* main( )   // 连通图的遍历
	{ V_NODE head[MAXN]; 
      int n,t, visit1[MAXN]={0},visit2[MAXN]={0};				// 访问标志数组初始化 
      n=6;  t=1;												// G1 无向图结点数
      
      creat_adj_list(head, n, t);								// 创建一个无向图的邻接表
      printf( t==1? "无向图的边为:\n": "有向图的边为:\n");
	  prn_adj_list(head, n,1);									// 显示邻接表
      
	  printf("\n深度优先搜索DFS遍历:");
	  dfs(1, visit1, head);										// 从顶点 1 出发进行遍历
       
	  printf("\n\n广度优先搜索BFS遍历:");
	  bfs(1, visit2, head);
      
	  printf("\n\n");
	}

*/

int main() // 非连通图的遍历
{
    V_NODE head[MAXN];
    int i, n, t, visit[MAXN] = {0}; // 访问标志数组初始化
    n = 6, t = 1;                   // G6 非连通无向图结点数

    creat_adj_list(head, n, t); // 创建一个有向图的邻接表
    printf(t == 1 ? "无向图的边为:\n" : "有向图的边为:\n");
    prn_adj_list(head, n, t);

    printf("\n\n非连通图广度优先搜索BFS遍历:\n");
    for (i = 1; i < n; i++)
        if (visit[i] == 0)
        {
            bfs(i, visit, head);
            printf("\n");
        }
    printf("\n");
}
