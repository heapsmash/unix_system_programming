#include "tlpi_hdr.h"
#include <getopt.h>

int main(int argc, char *argv[])
{
    int opt, append_flag;

    while ((opt = getopt(argc, argv, "a:") != -1))
    {
        switch (opt)
        {
        case 'a':
            append_flag = 1;
            break;
        case 'h':
            usageErr("%s [-ah] file", argv[0]);
        default:
            append_flag = 0;
        }
    }
    puts(argv[optind]);
}