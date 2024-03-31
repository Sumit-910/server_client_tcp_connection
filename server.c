#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define max_buffer_size 255
#define max_no_clients 5

void error(const char *error_msg)
{
    perror(error_msg);
    exit(1);
}

int main(int argc, char *argv[])
{
    // argc contains the number of arguments
    // argv contains the agruments, in this case argv[0] = filename and argv[1] = port number

    if (argc < 2)
    {
        // fprintf does printf on a file
        // stderr is used to print on an ongoing process in a terminal
        fprintf(stderr, "Port no not provided. Program terminated!\n");
        exit(1);
    }

    int sockfd, port_no;

    // initialising a communication i.e. generating a socket with number sockfd
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    // if no connection is formed then it returns -1
    if (sockfd < 0)
    {
        error("Error opening socket!");
    }

    struct sockaddr_in serv_addr, cli_addr;
    /*
    definition of sockaddr_in present in the netinet/in.h header
    struct sockaddr_in
    {
        short int sin_family;        // Address family, AF_INET
        unsigned short int sin_port; // Port number
        struct in_addr sin_addr;     // Internet address
        unsigned char sin_zero[8];   // Same size as struct sockaddr
    };
    */

    // initialize the data of serv_addr to 0
    // bzero((char *)&serv_addr, sizeof(serv_addr)); // depricated
    memset(&serv_addr, 0, sizeof(serv_addr));
    port_no = atoi(argv[1]);

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY; // allows requests from any network
    serv_addr.sin_port = htons(port_no);    // converts port_no from host byte order to network byte order

    /*
    When a server socket is associated or bound to a specific IP address and port number, it means that the server will listen for incoming connections on that IP address and port.
    */
    if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        error("Binding failed!");
    }

    listen(sockfd, max_no_clients);

    socklen_t clilen; // socklen_t is a 32-bit datatype that stores the length of the client address
    clilen = sizeof(cli_addr);

    // accept request from the client and store the socket no in newsockfd
    int newsockfd;
    newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);

    if (newsockfd < 0)
    {
        error("Error on accept!");
    }

    int check;
    char buffer[max_buffer_size];
    while (1)
    {
        memset(buffer, 0, max_buffer_size);
        check = read(newsockfd, buffer, max_buffer_size);

        if (check < 0)
        {
            error("Error on reading!");
        }
        printf("Client : %s\n", buffer);
        memset(buffer, 0, max_buffer_size);
        fgets(buffer, max_buffer_size, stdin);

        check = write(newsockfd, buffer, strlen(buffer));
        if (check < 0)
        {
            error("Error on writing!");
        }

        // end the loop
        int l = strncmp("Bye", buffer, 3);
        if (l == 0)
        {
            break;
        }
    }

    // close the sockets by the socket numbers
    close(newsockfd);
    close(sockfd);

    return 0;
}