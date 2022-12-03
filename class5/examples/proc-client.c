#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#define SERVER_PATH "unix_sock"
#define DATA "Hello world!\n"

int main(void)
{
    int client_socket, rc;
    struct sockaddr_un remote;
    char buf[256];
    memset(&remote, 0, sizeof(struct sockaddr_un));

    // Create an unix domain datagram socket
    client_socket = socket(AF_UNIX, SOCK_DGRAM, 0);

    // Setup the unix sockaddr structure by using AF_UNIX for the family and giving it a filepath to send to.
    remote.sun_family = AF_UNIX;
    strcpy(remote.sun_path, SERVER_PATH);

    // Copy the data to be sent to the buffer and send it to the server.
    strcpy(buf, DATA);
    printf("Sending data...\n");

    rc = sendto(client_socket, buf, strlen(buf), 0, (struct sockaddr *)&remote, sizeof(remote));
    printf("Data sent!\n");

    rc = close(client_socket);
    return 0;
}
