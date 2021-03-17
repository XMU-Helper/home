#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define N 100 // N 为字符串最大长度

typedef struct node // 定义树的结点
{
    char data;
    struct node *lchild;
    struct node *rchild;
} NODE;

// 按标准形式存储的二叉树的创建

NODE *creat_btree(char s[]) // s 为字符串, 如果左或右子树为空用'*' 表示
{
    NODE *stack[N], *p = NULL, *q; // p 指向当前结点， q  指向父结点
    int k = 0, top = 0;            // 初始化堆栈及字符位置
    char ch = s[0];                // 取一字符为当前处理字符
    while (ch != '\0')             // 字符串还未处理结束
    {
        if (isalpha(ch)) // 若当前字符为字母
        {
            p = (NODE *)malloc(sizeof(NODE));
            p->data = ch; // 以当前字符为值建立新结点
            p->lchild = NULL;
            p->rchild = NULL;
        }    // 初始化新结点的各指针域
        else // 当前字符不是字母
            switch (ch)
            {
            case '(':
                stack[top++] = p; // 当前结点进栈
                p = NULL;
                break;
            case ',':
                q = stack[top - 1]; // 取栈顶结点(不出栈)为父结点
                q->lchild = p;      // 把当前结点作为孩子链接
                p = NULL;
                break;
            case ')':
                q = stack[--top]; //  取栈顶结点(出栈)为父结点
                q->rchild = p;    // 把当前结点作为孩子链接
                p = q;
                break; // 取父结点为当前结点
            }

        ch = s[++k]; // 取下一字符为当前处理字符
    }                //  end while
    return (p);      // 返回树的根结点的地址
}

// 标准形式存储的二叉树以嵌套括号表示输出

void prn_btree(NODE *t) // t 为标准形式存储的二叉树
{
    if (t)
    {
        printf("%c", t->data);
        if ((t->lchild) || (t->rchild))
        {
            printf("(");

            if (t->lchild)
                prn_btree(t->lchild);
            else
                printf(" ");

            printf(",");

            if (t->rchild)
                prn_btree(t->rchild);
            else
                printf(" ");

            printf(")");
        }
    }
}

// 前序遍历的递归程序

void preorder(NODE *t)
{
    if (t != NULL)
    {
        printf("%c ", t->data);
        preorder(t->lchild);
        preorder(t->rchild);
    }
}

// 中序遍历的递归程序

void midorder(NODE *t)
{
    if (t != NULL)
    {
        midorder(t->lchild);
        printf("%c ", t->data);
        midorder(t->rchild);
    }
}

// 后序遍历的递归程序

void posorder(NODE *t)
{
    if (t != NULL)
    {
        posorder(t->lchild);
        posorder(t->rchild);
        printf("%c ", t->data);
    }
}

// 中序遍历的非递归程序

struct snode
{
    NODE *addr;
    struct snode *link;
};
typedef struct snode SNODE;
void s_midorder(NODE *t)
{
    SNODE *top = NULL, *p;
    while (t != NULL || top != NULL)
    {
        while (t != NULL) // 未到达叶结点
        {
            p = (SNODE *)malloc(sizeof(SNODE));
            p->addr = t;
            p->link = top;
            top = p;       // t 进栈
            t = t->lchild; // t 遍历左子树
        }
        if (top != NULL) // 栈非空
        {
            t = top->addr;          // 取栈顶结点的值并输出
            printf("%c ", t->data); // 该语句上移可实现前序遍历
            p = top;
            top = top->link; // t 出栈
            free(p);
            t = t->rchild; // t 遍历右子树
        }
    }
}

int main()
{
    NODE *t;

    // char  s[] ="A(B(D,E(H,I)), C(F(,J),G))";
    char s[] = "A(B(D,E(G, )), C(F(,h), ) )"; // 嵌套括号表示输出二叉树
    t = creat_btree(s);

    printf("\n嵌套括号表：");
    prn_btree(t);

    printf("\n前序遍历序列：");
    preorder(t);
    printf("\n中序遍历序列：");
    midorder(t);
    printf("\n后序遍历序列：");
    posorder(t);
    printf("\n中序遍历序列(非递归)：");
    s_midorder(t);

    putchar('\n');
    putchar('\n');
}
