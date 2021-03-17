#define INFINITE 1000 // 定义一个足够大的数
#include <stdio.h>
#include <stdlib.h>

struct node
{
    int row, col; // 定义结点结构
    struct node *right, *down;
    union
    {
        int val;           // 非零元素结点用 val 域
        struct node *next; // 表头结点用 next 域
    } tag;
};
typedef struct node NODE;

// 建立具有 m 行 n 列的零矩阵的十字链表(如上图)
NODE *creat_null_mat(int m, int n)
{
    NODE *h, *p, *q;
    int i, s;
    h = (NODE *)malloc(sizeof(NODE)); // 建立表头结点-
    h->row = m;
    h->col = n; // -链表的头结点
    h->tag.next = h;
    p = h;
    s = m > n ? m : n;
    for (i = 0; i < s; i++)
    {
        q = (NODE *)malloc(sizeof(NODE));
        q->col = INFINITE;
        q->row = INFINITE; // 填上 ∞
        q->right = q;
        q->down = q;               // 行、列链表置空
        q->tag.next = p->tag.next; // 把表头结点链成循环链表
        p->tag.next = q;
        p = q;
    }
    return (h);
}

// 找第 i 行的链表的最后一个结点
NODE *search_row_last(NODE *a, int i)
{
    NODE *p = a, *h;
    int k;
    for (k = 1; k <= i; k++) // 找第 i 行的链表的表头结点
        p = p->tag.next;
    h = p;
    while (p->right != h) // 找第 i 行的链表的最后一个结点
        p = p->right;
    return (p);
}

// 找第 j 列的链表的最后一个结点
NODE *search_col_last(NODE *a, int j)
{
    NODE *p = a, *h;
    int k;
    for (k = 1; k <= j; k++) // 找第 j 列的链表的表头结点
        p = p->tag.next;
    h = p;
    while (p->down != h) // 找第 j 列的链表的最后一个结点
        p = p->down;
    return (p);
}

// 插入一个结点
void insert_node(a, row, col, value)
    NODE *a;
int row, col, value;
{
    NODE *p, *q, *r;
    p = search_row_last(a, row); // 找到插入的位置
    q = search_col_last(a, col);
    r = (NODE *)malloc(sizeof(NODE));
    r->row = row;
    r->col = col;
    r->tag.val = value;
    r->right = p->right;
    p->right = r; // 插入到行链表中
    r->down = q->down;
    q->down = r; // 插入到列链表中
}

// 建立十字链表, 输入为三元组数组
NODE *creat_mat(int a[][3]) //NODE *creat_mat()
{
    int m, n, t, r, c, k, v;
    NODE *h;
    printf("\n输入三元组：\n");
    printf("输入行数，列数和非零元素个数：");
    m = a[0][0];
    n = a[0][1];
    t = a[0][2];                   //   scanf("%d,%d,%d",&m,&n,&t);	// 输入
    printf("%d,%d,%d\n", m, n, t); // XX
    h = creat_null_mat(m, n);      //建立零矩阵的十字链表
    for (k = 1; k <= t; k++)
    {
        printf("输入第%d个三元组：", k);
        r = a[k][0];
        c = a[k][1];
        v = a[k][2];                   // scanf("%d,%d,%d",&r,&c,&v);		// 输入非零元素
        printf("%d,%d,%d\n", r, c, v); // XX
        if ((r <= m) && (r > 0) && (c <= n) && (c > 0))
            insert_node(h, r, c, v); // 插入一个结点
        else
        {
            printf("行号%d或列号%d超界错位！\n", r, c);
            k--; // 输入错位,重新输入
        }
    }
    return (h);
}

// 按三元组表示方法输出十字链表 a
void prn_mat(NODE *a)
{
    NODE *p, *q;
    printf("\n 十字链表为:　 %d×%d \n", a->row, a->col);
    p = a->tag.next;
    while (p != a)
    {
        q = p->right;
        while (p != q)
        {
            printf("%d,%d,%d\n", q->row, q->col, q->tag.val);
            q = q->right;
        }
        p = p->tag.next;
    }
}

// 十字链表元素查找
int locat_mat(NODE *a, int x, int *r, int *c)
{
    NODE *p, *q;
    p = a->tag.next;
    while (p != a) // 对于每一行
    {
        q = p->right;
        while (q != p) // 扫描当前行
        {
            if (q->tag.val == x) // 找到值为 x 的结点
            {
                *r = q->row;
                *c = q->col;
                return (0);
            }
            q = q->right; // 找当前行的下一个结点
        }
        p = p->tag.next; // 找下一行
    }
    return (1); // 找不到值为x的结点
}

//十字链表相加
NODE *mat_add(NODE *a, NODE *b)
{
    NODE *c, *pa, *ha, *pb, *hb;
    int v;
    c = creat_null_mat(a->row, a->col); //  零矩阵存放结果
    ha = a->tag.next;                   //  ha 取 a 第一行的头结点
    hb = b->tag.next;
    while (ha != a) // 对于十字链表中的每一行
    {
        pa = ha->right;              // pa 指向 a 当前行第一个结点
        pb = hb->right;              // pb 指向 b 当前行第一个结点
        while (pa != ha || pb != hb) // 对于当前行的所有结点
        {
            if (pa->col == pb->col) // 列号相同
            {
                if ((v = pa->tag.val + pb->tag.val) != 0) // 和 ≠ 0
                {
                    insert_node(c, pa->row, pa->col, v); // 插入
                    pa = pa->right;                      // pa 指向 a 当前行下一个结点
                    pb = pb->right;                      // pb 指向 b 当前行下一个结点
                }
            }
            else if (pa->col < pb->col) // pa列号< pb列号
            {
                insert_node(c, pa->row, pa->col, pa->tag.val);
                pa = pa->right; // pa 指向 a 当前行下一个结点
            }
            else // pa 列号 > pb 列号
            {
                insert_node(c, pb->row, pb->col, pb->tag.val);
                pb = pb->right; // pb 指向 b 当前行下一个结点
            }
        }
        ha = ha->tag.next;
        hb = hb->tag.next; // 取下一行头结点
    }
    return (c); // 返回结果矩阵的十字链表
}

// 主函数：创建十字链表并输出, 再查找
/*
main( )	
	{ int a[50][3]={6,7,8, 1,2,24, 2,4,-35, 2,7,81, 3,1,8, 4,4,15, 5,2,-57, 5,6,62, 6,4,96};
	  int i, j, x =1;
	  NODE *h;
      h=creat_mat(a);  //h=creat_mat( );
      prn_mat(h); 

      printf("\n 输入要查找的值：");
      scanf("%d", &x);
      if  ( locat_mat(h,x,&i,&j)==0)
           printf(" A[%d,%d]=%d\n", i, j, x);
      else printf("找不到 %d!\n",x);
   }
*/

// 主函数：十字链表相加
int main()
{
    NODE *a, *b, *c;
    int aa[50][3] = {6, 7, 8, 1, 2, 24, 2, 4, -35, 2, 7, 81, 3, 1, 8, 4, 4, 15, 5, 2, -57, 5, 6, 62, 6, 4, 96};
    int bb[50][3] = {6, 7, 8, 1, 2, 24, 2, 4, -35, 2, 7, 81, 3, 2, 7, 4, 4, 15, 5, 2, -57, 5, 6, 62, 6, 4, 96};
    a = creat_mat(aa);
    prn_mat(a);

    b = creat_mat(bb);
    prn_mat(b);
    c = mat_add(a, b);
    printf("\n 相加结果：");
    prn_mat(c);
}
