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
#define MIXED_FDS 6
#define EBADF 3

int challenge(int fd);
void print_curr_challenge();
sem_t *sem_id;

int curr_challenge = 0;
char *challenge_msg = "---------- CHALLENGE ----------\n";
char *line_separator = "------------------------------\n";


char *challenges[] = {"Bienvenido a nuestro TP3. Las respuestas no suelen ser las mismas que en el servidor original.\n para comenzar con los desafios escriba \"entendido \\n\".\n","# \\033[D \\033[A \\033[A \\033[D \\033[B \\033[C \\033[B \\033[D *", "https://vocaroo.com/i/s1lD9m8lGzei \n (la respuesta no es la misma que en el servidor original)", "EBADF", "respuesta = strings[192]", " .DATA_tp3  .TEXT_tp3  ?" ,"NOT WRITTEN" ,"##\n                               ##  ##\n                              #     ##\n                             ######## ##\n                            ##::::::# # ##\n                          ##::::::::::#  #\n                         #::::::::::::##  #\n                        #::::::::::::#::# #\n                       #:::::::::::::#:::#\n                       #:::::::::::::::::#\n                      #:::::::::::::::::#:#\n                      #:::::::::::::::::#:#\n                     #::::::::::::::::::::#\n                    #:::::::::::::::::::::#\n                   #::::::::::::::::::::::#\n                   #####:::#####::::::::::#\n                  #     #:#    ##:::::::::#\n                  #     ##       #::::::::#\n                 #   ## #        #::::::::#\n                 #   # #         #:::::::#\n                  #    #         #::::#::#\n                   X####     ##  #:::##:##\n                   #::::#    ##  #::#:#::#\n                 #:::::#        #::#:## #\n                  #:::::##      #:::::#  #\n                  #:::::::##  X#::::::#  #\n                  #:::::::::##::::::#:#\n                   ##########::::::::##\n                  #:::::::::::##:::::::#\n                 #::::::::::::::#::::#:#\n                ##::::::::::::####::###\n                #:::::::::::##  ##:::#\n                ##::::::::## #  ##:::#\n                 #### #####   ####:::#\n                     #  #  #  #:#::::##\n                     #  #  # #::#::::# #\n                     #  #####:::#::::# ##\n                    #####::::::##::::## #\n                    ##:::::::::#:::::#  #\n                     ###::::::#::::##    #\n                       ##::###::::#      #\n                      # ####X::::#       #\n                     #  #::::::##        #\n                     # ##:::::#          #\n                     # ##::::#          ##\n                   ##  ##::::#         #  #\n             ##  ## ### #::## #       ##  ###\n        # ###::###   #  #:#   #      ## ###::######\n       #:#::#::#::#  #   #    #    ### #::#::#::#::#\n      #::#::#::#::#                    #::#::#::##::#     #\n #########::#::#::######################::#::#::#:#########\n         #::#::###                        ###::#::#  dD\n          ## ##                            ## ##\n", " Mike One Echo ", " la excusa de homero es la respuesta. \n\n ==AMzI2XzUTNrB3Ms1jd/g2Y0F2dv02bj5SZiVHd19Weuc3d39yL6MHc0RHa \n\n es tambien nuestra excusa por entregar tarde todos los TPs. \n"};
char *answers[] = {"entendido", "#0854780*", "nokia", "simpsons", "marge", ".bart_section", "lisa", "homero", "moe", "patas chuecas"};
int challenge_count = 9;
char *marge = "marge";

int main(int argc, char *argv[]) {
    int my_socket, new_socket; 
    socklen_t cli_size;
    struct sockaddr_in serv_addr, cli_addr;
    sem_id = sem_open("pipe_123", O_CREAT, 0600, 0); 

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

    char *buf = "simpsons";
    write(9, buf, strlen(buf));

    listen(my_socket,1);

    cli_size =  sizeof(cli_addr);
    int pid;

    new_socket = accept(my_socket, (struct sockaddr *) &cli_addr, &cli_size);
    if (new_socket < 0)
            return 3;
    while (1) {
        
        
        if (challenge(new_socket) == 1) {
                if (curr_challenge < challenge_count ) curr_challenge++;
                else {
                    printf(" \n Felicidades, ha completado los acertijos!! \n");
                    exit(0);
                }
            } 
    }


    


    return 0;
}

int challenge(int fd) {
    print_curr_challenge();

    // read answer, verify, print response.
    char buffer[256];
    bzero(buffer,256);
    sem_wait(sem_id);
    int n = read(fd,buffer,255);
    if (n<0) {
        return 3;
    }
    

    if ( strncmp(buffer, answers[curr_challenge], strlen(answers[curr_challenge])) ){
        printf("respuesta incorrecta. \n");
        return 0;
    } else {
        printf("respuesta correcta! \n");
        return 1;
    }

}

void print_mixed_fds() {
    write(2,"s",1);
    write(2,"e",1);
    write(1,"l",1);
    write(2,"e",1);
    write(2,"h",1);
    write(2,"u",1);
    write(2,"s",1);
    write(2,"m",1);
    write(2," ",1);
    write(2,"p",1);
    write(1,"i",1);
    write(2,"t",1);
    write(2,"g",1);
    write(2,"i",1);
    write(2,"l",1);
    write(2,"l",1);
    write(2,"f",1);
    write(1,"s",1);
    write(2,"w",1);
    write(2," ",1);
    write(2,"s",1);
    write(2,"v",1);
    write(2,"m",1);
    write(1,"a",1);
    write(2,"b",1);
    write(2,"e",1);
    write(2,"p",1);
}

void print_curr_challenge() {
    printf(challenge_msg);
    printf("\n\n");
    if ( curr_challenge == MIXED_FDS ){
        printf("\n");
        print_mixed_fds();
        printf("\n");
    } else if( curr_challenge == EBADF){
        char *buf = "simpsons";
        write(9, buf, strlen(buf));
        printf(challenges[curr_challenge]);
    }else {
        printf(challenges[curr_challenge]);
    }
    printf("\n\n");
    printf(line_separator);
}
