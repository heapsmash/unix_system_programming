#define _GNU_SOURCE

#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

#define READ 0
#define WRITE 1

FILE *my_popen(char *cmdstring);

int main(int argc, char *argv[])
{
    char line[500 + 1] = "";

    FILE *childpid = my_popen("man 2 open");

    if (childpid != NULL)
        while (fgets(line, sizeof(line), childpid))
            printf("%s", line);

    return 0;
}

FILE *my_popen(char *cmdstring)
{
    int pipefd[2];
    char buf[32], *argv[] = {"/bin/sh", "-c", cmdstring, NULL};

    if (pipe(pipefd) == -1)
    {
        perror("pipe");
        return NULL;
    }

    pid_t pid = fork();
    if (pid == -1)
    {
        perror("fork()");
        return NULL;
    }

    if (pid == 0) // child
    {
        int out_fd = dup2(pipefd[WRITE], STDOUT_FILENO);
        if (out_fd < 0)
            perror("dup2");

        close(pipefd[WRITE]);

        execv("/bin/sh", argv);
        perror("execve failed!");
        _exit(123);
    }

    int wstatus;

    if (pid != wait(&wstatus) || !WIFEXITED(wstatus))
    {
        perror("Divorsed");
        return NULL;
    }

    close(pipefd[WRITE]);

    return fdopen(pipefd[READ], "r");
}
