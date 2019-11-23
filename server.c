#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>

#define PORT 22223

int main(int argc, char *argv[]) {
    int my_socket, new_socket, cli_size;
    char buff[256];
    struct sockaddr_in serv_addr, cli_addr;

    // make new socket
    my_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (my_socket < 0) {
        printf("error on socket creation\n");
        return 1;
    }

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    serv_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(my_socket, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        printf("error on binding\n");
        return 2;
    }

    listen(my_socket, 5);

    cli_size =  sizeof(cli_addr);
    new_socket = accept(my_socket, (struct sockadr *) &cli_addr, &cli_size);
    if(new_socket < 0 ) {
        return 3;
    }

    bzero(buff,256);

    int n = read(new_socket, buff, 255);

    if( n < 0) {
        printf("error reading from socket");
    }


    return 0;
}