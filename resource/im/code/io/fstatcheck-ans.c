/* $begin fstatcheck-ans */
#include "csapp.h"

int main (int argc, char **argv) 
{
    struct stat stat;
    char *type, *readok;
    int size;

    /* $end statcheck */
    if (argc != 2) {
	fprintf(stderr, "usage: %s <fd>\n", argv[0]);
	exit(0);
    }
    /* $begin statcheck */
    Fstat(atoi(argv[1]), &stat);
    if (S_ISREG(stat.st_mode))     /* Determine file type */
	type = "regular";
    else if (S_ISDIR(stat.st_mode))
	type = "directory";
    else if (S_ISCHR(stat.st_mode))
	type = "character device";
    else 
	type = "other";

    if ((stat.st_mode & S_IRUSR)) /* Check read access */
	readok = "yes";
    else
	readok = "no";

    size = stat.st_size; /* check size */

    printf("type: %s, read: %s, size=%d\n", 
	   type, readok, size);

    exit(0);
}
/* $end fstatcheck-ans */
