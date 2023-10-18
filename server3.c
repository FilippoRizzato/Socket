#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <fcntl.h>
#include <signal.h>
#include <errno.h>
#include <unistd.h>
#include <ctype.h>

#define SERVER_PORT 9090

int main(int argc, char *argv[])
{
    struct sockaddr_in servizio, rem_indirizzo;
    int socketfd, fromlen = sizeof(servizio), soa;

    servizio.sin_family = AF_INET;
    servizio.sin_addr.s_addr = htonl(INADDR_ANY);
    servizio.sin_port = htons(SERVER_PORT);

    socketfd = socket(AF_INET, SOCK_STREAM, 0);

    bind(socketfd, (struct sockaddr *)&servizio, sizeof(servizio));

    listen(socketfd, 10);

    for (;;)
    {
        printf("\n\n server in ascolto...\n");
        fflush(stdout);

        soa = accept(socketfd, (struct sockaddr *)&rem_indirizzo, &fromlen);
        char stringa[20];
        read(soa, stringa, strlen(stringa));

        for (int i = 0; i < strlen(stringa); i++)
        {
            for (int j = strlen(stringa - 1); j >= 0; j--)
            {
                if (stringa[i] == stringa[j - 1])
                {
                    printf("La stringa è palindroma");
                    write(soa, stringa, strlen(stringa));
                }
                else
                {
                    printf("La stringa non è palindroma");
                    write(soa, stringa, strlen(stringa));
                }
            }
        }
    }
    close(soa);
    return 0;
}