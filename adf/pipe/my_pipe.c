#define _GNU_SOURCE /* See feature_test_macros(7) */
#include <fcntl.h>  /* Obtain O_* constant definitions */
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char *argv[])
{
    int fds[2];

    if (pipe(fds) == -1)
    {
        perror("pipe");
        return 1;
    }

    char buf[32];
    if (write(fds[0], "fds[0]", sizeof("fds[0]")) < 0)
    {
        perror("write");
    }
    if (read(fds[1], buf, sizeof(buf)) < 0)
    {
        perror("read");
    }

    printf("%s\n", buf);
    write(fds[1], "write[1]", sizeof("write[1]"));
    read(fds[0], buf, sizeof(buf));
    printf("%s\n", buf);

    return 0;
}