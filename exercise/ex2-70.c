/*
 * 练习题 2.70
 *
 * 写出具有如下原型的函数的代码：
 *
 * Return 1 when x can be represented as an n-bit, 2's complement
 * number; 0 otherwise
 * Assume 1 <= n <= w
 *
 *         int fits_bits(int x, int n);
 *
 * 函数应该遵循位级整数编码规则。
 */

#include <limits.h>

/*
 * 如果我们需要观察一个数是否可以使用 n 位补码和表示。我们可以将这个数的低 n-1 位
 * 全部置零，然后观察 w...n 这些位。
 *
 * 对于正数来说，如果这些 w...n 这些位非零的话，则说明 n 位补码不足以表示这个数。
 * 对于负数来说，如果这些 w...n 这些位不是全 1 的话，则说明 n 位补码不足以表示这
 * 个数。
 */
int fits_bits(int x, int n)
{
        /* 1. 取得一个低 n-1 位为全 1，其他位全 0 的数 */
        int r = (1 << (n-1)) - 1;

        /* 2. 将这个数取反 */
        int s = ~r;

        /* 3. 将 x 的低 n-1 位置零，然后查看 w...n 是否为 0，或者全 1 */
        int t = s & x;
        int u = s ^ t;

        /* 4. 取得 x 的符号位 */
        int sign = INT_MIN & x;

        return (!sign && !t) || (t && !u);
}
