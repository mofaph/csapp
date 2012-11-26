/* $begin mmapwrite-ans */
#include "csapp.h"

/*
 * mmapwrite - uses mmap to modify a disk file 
 */
void mmapwrite(int fd, int len) 
{
    char *bufp;

    /*    bufp = Mmap(NULL, len, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);*/
    bufp = Mmap(NULL, len, PROT_READ|PROT_WRITE, MAP_PRIVATE, fd, 0);
    bufp[0] = 'J'; 
}

/* mmapwrite driver */
int main(int argc, char **argv) 
{
    int fd;
    struct stat stat;

    /* check for required command line argument */
    if (argc != 2) {
	printf("usage: %s <filename>\n", argv[0]);
	exit(0);
    }

    /* open the input file and get its size */
    fd = Open(argv[1], O_RDWR, 0);
    fstat(fd, &stat);
    mmapwrite(fd, stat.st_size);
    exit(0);
}
/* $end mmapwrite-ans */


