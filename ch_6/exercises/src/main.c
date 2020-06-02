/*
    Implement setenv() and unsetenv() using getenv(), putenv(), and, where necessary,
    code that directly modifies environ. Your version of unsetenv() should check to see
    whether there are multiple definitions of an environment variable, and remove
    them all (which is what the glibc version of unsetenv() does).
*/

#define _GNU_SOURCE // To get various declarations from <stdlib.h>
#include <stdlib.h>
#include "tlpi_hdr.h"

#define MAX_LEN 100 // This value is not ideal, however this is just an exercise.
#define MAX_VARS 100

extern char **environ;

int my_setenv(const char *name, const char *value, int overwrite)
{
    static char env_var[MAX_VARS][MAX_LEN + 1];
    static int current_var = 0;

    if (name == NULL || value == NULL)
    {
        errMsg("const char *name and const char *value can't be NULL: my_setenv()\n");
        return 1;
    }

    size_t name_len = strlen(name);
    if ((name_len + strlen(value) + 1) > MAX_LEN)
    {
        errMsg("MAX_ENV exceeded: my_setenv()\n");
        return 1;
    }

    strcat(env_var[current_var], name);
    env_var[current_var][name_len] = '=';
    strcat(env_var[current_var], value);

    if (overwrite == 0)
        if (getenv(name) != NULL)
        {
            current_var++;
            return 0;
        }

    int return_value = putenv(env_var[current_var]);
    current_var++;

    return return_value;
}

int my_unsetenv(char *name)
{
    return putenv(name);
}

void print_env(void)
{
    char **ep;
    for (ep = environ; *ep != NULL; ep++)
        puts(*ep);
}

int main(int argc, char *argv[])
{
    clearenv();

    if (my_setenv("FIRST", "BOB", 0) != 0)
        errExit("my_setenv()");

    if (my_setenv("SECOND", "BOB", 1) != 0)
        errExit("my_setenv()");

    if (my_setenv("SECOND", "BOB", 0) != 0)
        errExit("my_setenv()");

    if (my_setenv("THIRD", "BOB", 1) != 0)
        errExit("my_setenv()");

    print_env();

    puts("==================");

    if (my_unsetenv("THIRD") != 0)
        errExit("my_unsetenv()");

    print_env();

    return 0;
}
