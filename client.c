#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <unistd.h>
#include <strings.h>
#include <string.h>
#include <semaphore.h>
#include <fcntl.h>

#define PORT 22223

int main(int argc, char *argv[]) {
    int my_socket;
    struct sockaddr_in serv_addr;
    struct hostent *host;
    sem_t *sem_id = sem_open("pipe_123", O_RDWR, 0);
    
    char buff[256];
    char hostname[1024];
    gethostname(hostname, 1024);


    my_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (my_socket < 0){
        printf("error opening socket");
        return 1;
    }
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
    while(1) {
        
        bzero(buff, 256);
        fgets(buff,255,stdin);
        int n = write(my_socket, buff, strlen(buff));
        if(n < 0) {
            printf("error writing to socket");
            return 5;
        }
        sem_post(sem_id);
    }
    



    return 0;
}