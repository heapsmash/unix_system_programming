/* 
    Implement dup() and dup2() using fcntl() and, where necessary, close(). 
    (You may ignore the fact that dup2() and fcntl() return different errno values 
    for some error cases.) For dup2(), remember to handle the special case where oldfd equals newfd. 
    In this case, you should check whether oldfd is valid, which can be done by, for example,
    checking if fcntl(oldfd, F_GETFL) succeeds. If oldfd is not valid, then the function
    should return –1 with errno set to EBADF .
*/

#include "tlpi_hdr.h"
#include <fcntl.h>
int main(int argc, char *argv[])
{
    int old_fd = open("temp", O_CREAT, S_IRGRP | S_IROTH | S_IRUSR);
    if (old_fd == -1)
        errExit("open()");

    int new_fd = fcntl(old_fd, F_DUPFD, 0);
    if (new_fd == -1)
        errExit("fcntl()");

    if (old_fd == new_fd && fcntl(old_fd, F_GETFL) == -1)
        errExit("old_fd == new_fd");

    if (close(old_fd) == -1)
        errExit("close(old_fd)");

    if (close(new_fd) == -1)
        errExit("close(new_fd)");

    return 0;
}
