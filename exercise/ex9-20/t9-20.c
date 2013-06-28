#include <stdio.h>

extern int mo_init(void);
extern void mo_free(void *bp);
extern void *mo_malloc(size_t size);

int main(void)
{
        if (mo_init() < 0)
                return -1;

        char *buf  = mo_malloc(1);
        printf("buf : %p\n", buf);
        if (buf)
                mo_free(buf);

        char *buf2 = mo_malloc(4);
        printf("buf2: %p\n", buf2);
        if (buf2)
                mo_free(buf2);

        char *buf3 = mo_malloc(8);
        printf("buf3: %p\n", buf3);

        char *buf4 = mo_malloc(12);
        printf("buf4: %p\n", buf4);

        if (buf3)
                mo_free(buf3);
        if (buf4)
                mo_free(buf4);

        buf  = mo_malloc(4);
        printf("buf : %p\n", buf);

        buf2 = mo_malloc(9);
        printf("buf2: %p\n", buf2);

        if (buf)
                mo_free(buf);
        if (buf2)
                mo_free(buf2);

        return 0;
}
