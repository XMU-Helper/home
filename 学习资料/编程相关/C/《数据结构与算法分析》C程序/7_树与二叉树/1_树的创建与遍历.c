#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define M 3   // M 为树的度
#define N 100 // N 为字符串最大长度

typedef struct node // 定义树的结点
{
    char data;
    struct node *child[M];
} NODE;

// 按标准形式存储的一般树的创建
NODE *creat_tree(char s[], int m) // s 为字符串, m为度
{
    NODE *stack[N], *p = NULL, *q; // p 指向当前结点， q  指向父结点
    int i, k = 0, top = 0;         // 初始化堆栈及字符位置
    char ch = s[0];                // 取一字符为当前处理字符
    while (ch != '\0')             // 字符串还未处理结束
    {
        if (isalpha(ch)) // 若当前字符为字母
        {
            p = (NODE *)malloc(sizeof(NODE));
            p->data = ch; // 以当前字符为值建立新结点
            for (i = 0; i < m; i++)
                p->child[i] = NULL;
        }    // 初始化新结点的各指针域
        else // 当前字符不是字母
            switch (ch)
            {
            case '(':
                stack[top++] = p;
                break; // 当前结点进栈
            case ',':
                q = stack[top - 1]; // 取栈顶结点 (不出栈) 为父结点
                i = -1;
                while (q->child[++i] != NULL)
                    ; // 找空的指针域
                q->child[i] = p;
                break; // 把当前结点作为孩子进行链接
            case ')':
                q = stack[--top]; // 取栈顶结点 (出栈)为父结点
                i = -1;
                while (q->child[++i] != NULL)
                    ;            // 找空的指针域
                q->child[i] = p; // 把当前结点作为孩子进行链接
                p = q;           // 取父结点为当前结点
            }
        ch = s[++k]; // 取下一字符为当前处理字符
    }                //  end while
    return (p);      // 返回树的根结点的地址
}

// 标准形式存储的一般树以嵌套括号表示输出

void prn_tree(NODE *T, int m) // t 为标准形式存储的一般树
{
    int i;
    if (T == NULL)
        return;
    printf("%c", T->data);
    if (T->child[0])
    {
        printf("(");
        for (i = 0; i < m && T->child[i]; i++) // 前序遍历根结点的各子树
        {
            prn_tree(T->child[i], m);
            if (i < m - 1 && T->child[i + 1])
                printf(",");
            else
                printf(")");
        }
    }
}

// 用递归实现前序遍历
void pre1_traverse(NODE *T, int m)
{
    int i;
    if (T != NULL)
    {
        printf("%c", T->data);  // 输出根结点的值
        for (i = 0; i < m; i++) // 前序遍历根结点的各子树
            pre1_traverse(T->child[i], m);
    }
}

// 用栈实现前序遍历(非递归)
void pre2_traverse(NODE *T, int m)
{
    NODE *s[100];
    int top, i;
    if (T == NULL)
        return;
    s[0] = T;
    top = 1; // 树根结点进栈

    while (top > 0) // 栈非空时
    {
        T = s[--top];                // 取出栈结点为当前结点
        printf("%c", T->data);       // 输出当前结点的值
        for (i = m - 1; i >= 0; i--) // 当前结点从右到左各子树
            if (T->child[i] != NULL)
                s[top++] = T->child[i]; // 子树根结点进栈
    }
}

//  用队列实现层次遍历
void lev_traverse(NODE *T, int m)
{
    NODE *q[100], *p;
    int head, tail, i;
    q[0] = T;
    head = 0;
    tail = 1; // 树根结点入队

    while (head < tail) // 队列非空时
    {
        p = q[head++];          // 取出队结点为当前处理结点
        printf("%c", p->data);  // 输出当前结点的值
        for (i = 0; i < m; i++) // 对于当前结点从左到右各子树
            if (p->child[i] != NULL)
                q[tail++] = p->child[i]; // 子树根结点入队
    }
}

int main()
{
    NODE *t;
    int m = M;
    char s[] = "A ( B ( E,F (L),G ),C ( H,I ),D ( J,K ( M,N ) ) )";
    t = creat_tree(s, m);

    printf("\n嵌套括号表：");
    prn_tree(t, m);

    printf("\n序遍历序列(归前)：");
    pre1_traverse(t, m);
    printf("\n前序遍历序列(非递归)：");
    pre2_traverse(t, m);
    printf("\n层次遍历序列：");
    lev_traverse(t, m);

    putchar('\n');
    putchar('\n');
}
