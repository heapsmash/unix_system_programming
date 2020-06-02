// Write a program that opens an existing file for writing with the O_APPEND flag, and
// then seeks to the beginning of the file before writing some data. Where does the
// data appear in the file? Why?

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include "error_functions.h"

int main(int argc, char *argv[])
{
    char buf[] = "this is a test";
    if (argc < 2)
        usageErr("%s file_to_open", argv[0]);

    int fd = open(argv[1], O_RDWR | O_APPEND);
    if (fd == -1)
        errExit("opep");

    // off_t offset = lseek(fd, 0, SEEK_SET);
    // if (offset == -1)
    //     errExit("lseek");

    ssize_t n_written = write(fd, buf, sizeof(buf) - 1);
    if (n_written == -1)
        errExit("write");

    close(fd);

    return 0;
}
