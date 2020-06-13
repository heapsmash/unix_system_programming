#include "us_xfr.h"

#define BACKLOG 5

int main(int argc, char *argv[])
{
        struct sockaddr_un addr;
        int socketFd, clientFd;
        ssize_t numRead;
        char buf[BUF_SIZE];

        socketFd = socket(AF_UNIX, SOCK_STREAM, 0);
        if (socketFd == -1)
                errExit("socket");

        /* construct server socket address, bind socket to it and make this a listening socket */

        if (remove(SV_SOCK_PATH) == -1 && errno != ENOENT)
                errExit("remove-%s", SV_SOCK_PATH);

        memset(&addr, 0, sizeof(struct sockaddr_un));
        addr.sun_family = AF_UNIX;
        strncpy(addr.sun_path, SV_SOCK_PATH, sizeof(addr.sun_path) - 1);

        if (bind(socketFd, (struct sockaddr *)&addr, sizeof(struct sockaddr_un)) == -1)
                errExit("bind");

        if (listen(socketFd, BACKLOG) == -1)
                errExit("listen");

        for (;;) /* Handle client connections iteratively */
        {
                /* Accept a connection. The connection is returned on a new socket, 'cfd'; 
                the listening socket ('sfd') remains open and can be used to accept further connections. */

                clientFd = accept(socketFd, NULL, NULL);
                if (clientFd == -1)
                        errExit("accept");

                /* Transfer data from connected socket to stdout until EOF */
                while ((numRead = read(clientFd, buf, BUF_SIZE)) > 0)
                        if (write(STDOUT_FILENO, buf, numRead) != numRead)
                                fatal("partial/failed write");
                if (numRead == -1)
                        errExit("read");

                if (close(clientFd) == -1)
                        errMsg("close");
        }
}
