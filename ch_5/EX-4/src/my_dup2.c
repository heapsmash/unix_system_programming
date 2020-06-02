/* 
    Implement dup() and dup2() using fcntl() and, where necessary, close(). 
    (You may ignore the fact that dup2() and fcntl() return different errno values 
    for some error cases.) For dup2(), remember to handle the special case where oldfd equals newfd. 
    In this case, you should check whether oldfd is valid, which can be done by, for example,
    checking if fcntl(oldfd, F_GETFL) succeeds. If oldfd is not valid, then the function
    should return –1 with errno set to EBADF.

    The dup2() system call performs the same task as dup(), but instead of using the lowest-numbered unused file descriptor, 
    it uses the file descriptor number specified in newfd. If the file descriptor newfd was previously open, it is silently closed before being reused.

    The steps of closing and reusing the file descriptor newfd are performed atomically. This is important, 
    because trying to implement equivalent functionality using close(2) and dup() would be subject to race conditions, 
    whereby newfd might be reused between the two steps. Such reuse could happen because the main program is interrupted by a sig‐nal handler 
    that allocates a file descriptor, or because a parallel thread allocates a file descriptor.

    Note the following points:
    1. If oldfd is not a valid file descriptor, then the call fails, and newfd is not closed.

    2. If oldfd is a valid file descriptor, and newfd has the same value as oldfd, then dup2() does nothing, and returns newfd.

*/

#include "tlpi_hdr.h"
#include <fcntl.h>
int main(int argc, char *argv[])
{
    if (argc != 2)
        usageErr("%s newfd\n", argv[0]);
    int newfd = getInt(argv[1], GN_ANY_BASE, argv[0]);

    int old_fd = open("temp", O_CREAT, S_IRGRP | S_IROTH | S_IRUSR);
    if (old_fd == -1)
        errExit("open()");

    if (old_fd == newfd)
        return newfd;

    if (close(newfd) == -1)
        errExit("close()");

    int dup_fd = fcntl(old_fd, F_DUPFD, newfd);
    if (dup_fd == -1)
        errExit("fcntl()");

    printf("dup = %d old = %d\n", dup_fd, old_fd);

    if (close(old_fd) == -1)
        errExit("close(old_fd)");

    if (close(dup_fd) == -1)
        errExit("close(new_fd)");

    return 0;
}
