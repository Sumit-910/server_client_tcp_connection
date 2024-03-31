/*
executing arguments

filename server_ipaddress port_no
agrv[0] = filename
argv[1] = server_ipaddress
argv[2] = port_no
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#define max_buffer_size 255

void error(const char *error_msg)
{
    perror(error_msg);
    exit(1);
}

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        fprintf(stderr, "Too few arguments\n");
        exit(1);
    }

    int sockfd, port_no;

    port_no = atoi(argv[2]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        error("Error opening socket");
    }

    struct sockaddr_in serv_addr;
    struct hostent *server;

    server = gethostbyname(argv[1]);
    if (server == NULL)
    {
        fprintf(stderr, "Error, no such host!\n");
    }

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr_list[0], (char *)&serv_addr.sin_addr.s_addr, server->h_length);

    serv_addr.sin_port = htons(port_no);

    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        error("Connection failed!");
    }

    char buffer[max_buffer_size];
    int check;
    while (1)
    {
        memset(buffer, 0, max_buffer_size);
        fgets(buffer, max_buffer_size, stdin);

        check = write(sockfd, buffer, strlen(buffer));
        if (check < 0)
        {
            error("Error on writing!");
        }

        memset(buffer, 0, max_buffer_size);

        check = read(sockfd, buffer, max_buffer_size);
        if (check < 0)
        {
            error("Error on reading!");
        }
        printf("Server : %s", buffer);

        int l = strncmp("Bye", buffer, 3);
        if (l == 0)
        {
            break;
        }
    }

    printf("Connection closed");
    close(sockfd);

    return 0;
}
