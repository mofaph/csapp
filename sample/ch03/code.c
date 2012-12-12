/*
 * p107
 *
 * 使用 GCC 产生汇编代码：
 *
 * unix> gcc -O1 -S code.c
 */

int accum = 0;

int sum(int x, int y)
{
        int t = x + y;
        accum += t;
        return t;
}
