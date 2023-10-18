#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <fcntl.h>
#include <signal.h>
#include <errno.h>
#include <ctype.h>
#include <unistd.h>

#define SERVER_PORT 9090

int main(int argc, char *argv[])
{
    struct sockaddr_in servizio;
    int socketfd;
    char stringa[20];
  
    servizio.sin_family = AF_INET;
    servizio.sin_port = htons(atoi(argv[3]));
    servizio.sin_addr.s_addr = inet_addr(argv[2]);

    socketfd = socket(AF_INET, SOCK_STREAM, 0);
    connect(socketfd, (struct sockaddr *)&servizio, sizeof(servizio));
    printf("Stabilita la connessione con il server..\n");

    printf("Stringa ricevuta \n");
    write(socketfd, argv[1], strlen(argv[1]));
    read(socketfd, stringa, strlen(stringa));
    printf("Ecco la stringa, %s\n", stringa);
    close(socketfd);
    return 0;
}