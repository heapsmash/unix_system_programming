// Write a program to verify that duplicated file descriptors share a file offset value
// and open file status flags.

#include "tlpi_hdr.h"
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
    int fd = open("temp", O_CREAT, S_IRUSR | S_IRGRP | S_IROTH);

    if (fd == -1)
        errExit("open()");

    int dupfd = dup(fd);
    if (dupfd == -1)
        errExit("dup");

    int fd_status_flags = fcntl(fd, F_GETFL);
    if (fd_status_flags == -1)
        errExit("fcntl(fd, F_GETFL)");

    int dupfd_status_flags = fcntl(dupfd, F_GETFL);
    if (dupfd_status_flags == -1)
        errExit("fcntl(dupfd, F_GETFL)");

    printf("%s", dupfd_status_flags == fd_status_flags ? "open file status flags are equal\n" : "open file status flags NOT equal\n");

    off_t off_fd = lseek(fd, 0, SEEK_CUR);
    if (off_fd == -1)
        errExit("lseek(fd, 0, SEEK_CUR)");

    off_t off_dupfd = lseek(dupfd, 0, SEEK_CUR);
    if (off_fd == -1)
        errExit("lseek(fd, 0, SEEK_CUR)");

    printf("%s", off_dupfd == off_fd ? "file offset values are equal\n" : "file offset values are NOT equal\n");

    return 0;
}
