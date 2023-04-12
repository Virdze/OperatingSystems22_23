#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>

int main(int argc, char * argv[]){
    
    pid_t pid ;
    int status;

    int fd[2];

    if(pipe(fd) < 0){
        perror("Error while creating pipe!\n");
        _exit(-1);
    }

    if((pid = fork()) < 0){
        perror("Error using fork!\n");
        _exit(-1);
    }
    else if(!pid){
        //Filho tem de por o stdinput para a end de leitura do pipe
        close(fd[1]);
        dup2(fd[0],0);
        close(fd[0]);
        sleep(2);
        ssize_t bytes_read;
        char buffer[1024];
        while((bytes_read = read(0, &buffer,1024)) > 0){
            buffer[bytes_read-1] = '\0';
            execlp(buffer,buffer,NULL);
        }
        _exit(-1);
    }
    else{
        ssize_t bytes_read;
        char buffer[1024];
        if((bytes_read = read(0, &buffer, 1024)) > 0){
            write(fd[1], buffer, bytes_read);
            close(fd[1]);
        }
        wait(&status);
        close(fd[0]);
    }
    return 0;
}