#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <unistd.h>

#define PORT 22223


int main(int argc, char *argv[]) {
    int my_socket;
    struct sockaddr_in serv_addr;
    struct hostent *host;
    
    char buff[256];
    char hostname[1024];
    gethostname(hostname, 1024);


    my_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (my_socket < 0)
        error("error opening socket");

    host = gethostbyname(hostname);
    if (host == NULL) {
        printf("could not get host");
        return 1;
    }

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)host->h_addr_list[0], (char *)&serv_addr.sin_addr.s_addr, host->h_length);
    serv_addr.sin_port = htons(PORT);

    if (connect(my_socket,&serv_addr,sizeof(serv_addr)) < 0) {
            printf("error connecting to socket");
            return 4;
    }

    bzero(buff, 256);
    fgets(buff, 255, stdin);
    int n = write(my_socket, buff, sizeof(buff));
    if(n < 0) {
        printf("error writing to socket");
        return 5;
    }
    bzero(buff, 256);
    n = read(my_socket, buff, 255);
    if (n < 0) {
        printf("error reading from socket");
        return -5;
    }



    return 0;
}