/*
    $ cc -o setjmp_vars setjmp_vars.c
    $ ./setjmp_vars
    Inside doJump(): nvar=777 rvar=888 vvar=999
    After longjmp(): nvar=777 rvar=888 vvar=999
*/

#include <setjmp.h>
#include "tlpi_hdr.h"
static jmp_buf env;

int main(int argc, char *argv[])
{

    exit(EXIT_SUCCESS);
}
