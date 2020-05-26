#include "tlpi_hdr.h"
#include <linux/limits.h>
#include <getopt.h>
#include <fcntl.h>

#ifndef BUF_SIZE /* Allow "cc -D" to override definition */
#define BUF_SIZE 1024
#endif /* BUF_SIZE */
#define NAME_LEN

int main(int argc, char *argv[])
{
    char buf[BUF_SIZE], *file_name;
    int opt, tee_fd;
    ssize_t num_read;

    int append_flag = 0;
    while ((opt = getopt(argc, argv, "a:")) != -1)
    {
        switch (opt)
        {
        case 'a':
            append_flag = 1;
            break;
        case '?':
            usageErr("%s [-ah] file\n", argv[0]);
        }
    }

    if (append_flag == 0)
    {
        if (argv[1] == NULL)
            usageErr("%s [-ah] file\n", argv[0]);
        file_name = strdup(argv[1]);
    }
    else
    {
        if (argv[2] == NULL)
            usageErr("%s [-ah] file\n", argv[0]);
        file_name = strdup(argv[2]);
    }

    if (file_name == NULL)
        usageErr("%s [-ah] file\n", argv[0]);

    if (append_flag)
        tee_fd = open(file_name, O_WRONLY | O_APPEND);
    else
        tee_fd = open(file_name, O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
    if (tee_fd == -1)
        errExit("open");

    while ((num_read = read(STDIN_FILENO, buf, BUF_SIZE)) > 0)
        if (write(tee_fd, buf, num_read) != num_read)
            fatal("couldn't write whole buffer");

    if (num_read == -1)
        errExit("read");

    if (close(tee_fd) == -1)
        errExit("close");

    exit(EXIT_SUCCESS);
}
