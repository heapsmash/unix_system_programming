#include "us_xfr.h"

int main(int argc, char *argv[])
{
        struct sockaddr_un addr;
        int socketFd;
        ssize_t numRead;
        char buf[BUF_SIZE];

        socketFd = socket(AF_UNIX, SOCK_STREAM, 0); /* Create client socket */
        if (socketFd == -1)
                errExit("socket");

        /* Construct server address, and make the connection */

        memset(&addr, 0, sizeof(struct sockaddr_un));
        addr.sun_family = AF_UNIX;
        strncpy(addr.sun_path, SV_SOCK_PATH, sizeof(addr.sun_path) - 1);

        if (connect(socketFd, (struct sockaddr *)&addr, sizeof(struct sockaddr_un)) == -1)
                errExit("connect");

        /* Copy stdin to socket */

        while ((numRead = read(STDIN_FILENO, buf, BUF_SIZE)) > 0)
                if (write(socketFd, buf, numRead) != numRead)
                        fatal("partial/failed write");

        if (numRead == -1)
                errExit("read");

        exit(EXIT_SUCCESS); // closes our socket; server sees EOF
}
