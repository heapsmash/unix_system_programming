/*
    This exercise is designed to demonstrate why the atomicity guaranteed by opening
    a file with the O_APPEND flag is necessary. Write a program that takes up to three
    command-line arguments:
    $ atomic_append filename num-bytes [x]
    This file should open the specified filename (creating it if necessary) and append
    num-bytes bytes to the file by using write() to write a byte at a time. 
    
    By default, the program should open the file with the O_APPEND flag, but if a third command-line
    argument (x) is supplied, then the O_APPEND flag should be omitted, and instead the
    program should perform an lseek(fd, 0, SEEK_END) call before each write(). 

    Run two instances of this program at the same time without the x argument to write
    1 million bytes to the same file:
    $ atomic_append f1 1000000 & atomic_append f1 1000000
 
    Repeat the same steps, writing to a different file, but this time specifying the x
    argument:
    $ atomic_append f2 1000000 x & atomic_append f2 1000000 x
  
    List the sizes of the files f1 and f2 using ls –l and explain the difference.
*/

#include "tlpi_hdr.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
    char bytes[] = {0xAA};

    int open_flags = O_RDWR;
    off_t offset;

    if (argc < 3)
        usageErr("Usage: %s filename num-bytes [x]\n", argv[0]);

    char *file_name = argv[1];
    long n_bytes = getLong(argv[2], GN_ANY_BASE, argv[0]);

    if (argc == 3)
        open_flags |= O_APPEND;

    int fd = open(file_name, open_flags);
    if (fd == -1)
        errExit("open()");

    while (1)
    {
        if ((open_flags & O_APPEND) == 0)
        {
            offset = lseek(fd, 0, SEEK_END);
            if (offset == -1)
                errExit("lseek()");
        }

        ssize_t n_written = write(fd, bytes, 1);
        if (n_written == -1)
            errExit("write()");

        n_bytes -= n_written;
        if (n_bytes == 0)
            break;
    }

    if (close(fd) == -1)
        errExit("close()");

    return 0;
}
