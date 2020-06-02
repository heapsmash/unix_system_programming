/*
    $ ./modify_env "GREET=Guten Tag" SHELL=/bin/bash BYE=Ciao
    GREET=Guten Tag
    SHELL=/bin/bash
    $ ./modify_env SHELL=/bin/sh BYE=byebye
    SHELL=/bin/sh
    GREET=Hello world
 */

#define _GNU_SOURCE // To get various declarations from <stdlib.h>
#include <stdlib.h>
#include "tlpi_hdr.h"

extern char **environ;

int main(int argc, char *argv[])
{
    int j;
    char **ep;

    clearenv(); // Erase entire environment

    for (j = 1; j < argc; j++)
        if (putenv(argv[j]) != 0)
            errExit("putenv: %s", argv[j]);

    if (setenv("GREET", "Hello world", 0) == -1)
        errExit("setenv");

    unsetenv("BYE");

    for (ep = environ; *ep != NULL; ep++)
        puts(*ep);

    exit(EXIT_SUCCESS);
}
