#include "tlpi_hdr.h"

extern char etext, edata, end;
extern char **environ;

void programm_addresses(void)
{
    printf("First address past:\n");
    printf("    program text (etext)      %10p\n", &etext);
    printf("    initialized data (edata)  %10p\n", &edata);
    printf("    uninitialized data (end)  %10p\n", &end);

    exit(EXIT_SUCCESS);
}

int main(int argc, char *argv[])
{
    char **ep;
    for (ep = environ; *ep != NULL; ep++)
        puts(*ep);

    int j;
    for (j = 0; j < argc; j++)
        printf("argv[%d] = %s\n", j, argv[j]);

    char **p;
    for (p = argv; *p != NULL; p++)
        puts(*p);

    exit(EXIT_SUCCESS);
}
