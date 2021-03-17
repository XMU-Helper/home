#define MAXN 100 // 定义栈的最大可用单元数
#include <stdio.h>
typedef struct stack // 定义栈的元素类型
{
    int n;     // 存放形参n
    char addr; // 递归返回地址用字符模拟
} STACK;
float fac1(int n) // 求n!递归模拟函数
{
    STACK s[MAXN]; // 建立工作栈
    float f;
    char d;
    int top = 0; // 栈初始化，用第二种表示法
    if (n < 0)
    {
        printf("n<0，输入数据错误!\n");
        return -1.0;
    }

in1: // 递归调用入口
    if (n == 0)
    {
        f = 1;
        goto ret_proc;
    }                    // 递归结束转返回处理
    s[top].n = n;        // 参数进栈
    s[top++].addr = 'A'; // 返回地址进栈并修改栈顶指针
    n = n - 1;           // 修改参数
    goto in1;            // 进入下一次递归调用

addr_A: // 递归返回地址
    f = f * n;
    goto ret_proc;

ret_proc:        // 递归返回处理(恢复调用前的值)入口
    if (top > 0) // 判别是否栈空
    {
        n = s[--top].n;  // 参数出栈
        d = s[top].addr; // 返回地址出栈
        goto addr_A;
    }
    return f; // 返回结果
}

int main() // 主函数
{
    int n;
    float facn;
    printf("Input an integer: ");
    scanf("%d", &n);
    facn = fac1(n);
    if (facn == -1.0)
    {
        return 0;
    }
    printf("%d! = %.2f\n", n, facn);
}
