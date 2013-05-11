/*
 * 10.10
 *
 * mofaph@gmail.com
 * 2013-5-11
 *
 * $ cc -I../common ../common/csapp.c ex10-10.c -lpthread
 */

#include "csapp.h"

int main(int argc, char **argv)
{
        int n;
        rio_t rio;
        char buf[MAXLINE];

        if (argc > 2) {
                fprintf(stderr, "usage: %s [filename]\n", argv[0]);
                return -1;
        }

        /* 这里将文件里的内容，拷贝到标准输出 */
        if (argc == 2) {
                char *filename = argv[1];
                int fd = Open(filename, O_RDONLY, 0);
                Rio_readinitb(&rio, fd);
                for (;;) {
                        n = Rio_readlineb(&rio, buf, MAXLINE);
                        if (n <= 0)
                                goto done;
                        Rio_writen(STDOUT_FILENO, buf, n);
                }
        }

        /* 没有输入文件名，将标准输入拷贝到标准输出 */
        Rio_readinitb(&rio, STDIN_FILENO);
        while ((n = Rio_readlineb(&rio, buf, MAXLINE)) != 0)
                Rio_writen(STDOUT_FILENO, buf, n);

done:
        return 0;
}
