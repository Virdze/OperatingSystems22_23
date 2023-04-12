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
        close(fd[0]);
        dup2(fd[1],1);
        close(fd[1]);
        execlp("ls","ls","/etc",NULL);
        _exit(-1);
    }
    else{
        pid_t terminated_pid = wait(&status);
        if(WIFEXITED(status)){
            close(fd[1]);
            dup2(fd[0],0);
            close(fd[0]);
            execlp("wc","wc","-l", NULL);
        }
    }
    return 0;
}