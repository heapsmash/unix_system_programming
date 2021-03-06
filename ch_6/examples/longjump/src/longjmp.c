/*
    $ ./longjmp
    Calling f1() after initial setjmp()
    We jumped back from f1()
    Specifying a command-line argument causes the jump to occur from f2():
    $ ./longjmp x
    Calling f1() after initial setjmp()
    We jumped back from f2()
*/

#include <setjmp.h>
#include "tlpi_hdr.h"
static jmp_buf env;

static void f2(void) { longjmp(env, 2); }

static void f1(int argc)
{
    if (argc == 1)
        longjmp(env, 1);
    f2();
}

int main(int argc, char *argv[])
{
    switch (setjmp(env))
    {
    case 0: // this is the return afer the inital setjmp()
        printf("Calling f1() after initial setjmp()\n");
        f1(argc); // never returns
        break;    // but this is good form.

    case 1:
        printf("We jumped back from f1()\n");
        break;

    case 2:
        printf("We jumped back from f2()\n");
        break;
    }

    exit(EXIT_SUCCESS);
}
