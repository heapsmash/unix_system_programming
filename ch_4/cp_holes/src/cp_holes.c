#include "tlpi_hdr.h"
#include <fcntl.h>

#ifndef BUF_SIZE /* Allow "cc -D" to override definition */
#define BUF_SIZE 1024
#endif /* BUF_SIZE */

int main(int argc, char *argv[])
{
    unsigned int buf[BUF_SIZE];
    if (argc < 3)
        usageErr("%s src dst\n", argv[0]);

    int src_fd = open(argv[1], O_RDONLY);
    if (src_fd == -1)
        errExit("open src_fd");

    int dst_fd = open(argv[2], O_EXCL | O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH); /* rw-rw-rw- */
    if (dst_fd == -1)
        errExit("open dst_fd");

    ssize_t n_read;
    while ((n_read = read(src_fd, buf, BUF_SIZE)) > 0)
        if (write(dst_fd, buf, n_read) != n_read)
            fatal("couldn't write whole buffer");
    if (n_read == -1)
        errExit("read");

    if (close(src_fd) == -1)
        errExit("close src_fd");

    if (close(dst_fd) == -1)
        errExit("close dst_fd");

    exit(EXIT_SUCCESS);
}
