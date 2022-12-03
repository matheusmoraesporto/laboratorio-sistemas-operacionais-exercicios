#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#define SOCK_PATH "unix_sock"

int main(void)
{
    int server_sock, len, rc;
    int bytes_rec = 0;
    struct sockaddr_un server_sockaddr, peer_sock;
    char buf[256];
    memset(&server_sockaddr, 0, sizeof(struct sockaddr_un));
    memset(buf, 0, 256);

    // Create an unix domain datagram socket
    server_sock = socket(AF_UNIX, SOCK_DGRAM, 0);

    // Setup the UNIX sockaddr structure by using AF_UNIX and giving it a filepath to bind to.
    server_sockaddr.sun_family = AF_UNIX;
    strcpy(server_sockaddr.sun_path, SOCK_PATH);
    len = sizeof(server_sockaddr);

    // Unlink the file so the bind will succeed, then bind to that file.
    unlink(SOCK_PATH);
    rc = bind(server_sock, (struct sockaddr *) &server_sockaddr, len);

    // Read data on the server from clients and print the data that was read.
    printf("waiting to recvfrom...\n");
    bytes_rec = recvfrom(server_sock, buf, 256, 0, (struct sockaddr *)&peer_sock, &len);
    printf("DATA RECEIVED = %s\n", buf);

    close(server_sock);
    return 0;
}