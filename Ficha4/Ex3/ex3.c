#include <stdio.h> 
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char * argv[]){
    int fd[2];
    pid_t pid;
    int status;

    if (pipe(fd) < 0){
        perror("Error creating pipe!\n");
        _exit(-1);
    }

    if ((pid = fork()) < 0 ){
        perror("Error using fork()!\n");
        _exit(-1);
    }
    else if (!pid){
        int msg = 999;
        close(fd[0]);
        write(fd[1],&msg,sizeof(msg));
        close(fd[1]);
        _exit(0);
    }
    else {
        close(fd[1]);
        pid_t terminated_pid = wait(&status);
        if(WIFEXITED(status)){
            if(WEXITSTATUS(status) == 0){
                ssize_t readedBytes;
                int buf;
                while((readedBytes = read(fd[0], &buf, sizeof(buf))) > 0){
                    printf("Pai (%d) leu o número %d do filho (%d)!\n",getpid(), buf, terminated_pid);
                }
                close(fd[0]);
            }
            else printf("Something went wrong!\n");
        }
    }
    return 0;
}