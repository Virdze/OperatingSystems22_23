#include <stdio.h> 
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_BUFFER_SIZE 512

int runProgram(char * command){
    pid_t pid;
    int status,
        flag = 0,
        counter = 0;
    int fd[2];


    //printf("Im here\n");
    //printf("%s\n",command);
    //sleep(10);
    if( pipe(fd) < 0){
        perror("Error creating pipe");
        _exit(-1);
    }

    while(!flag){
        if((pid = fork()) < 0){
            perror("Error using fork()!\n");
            _exit(-1);
        }
        else if(!pid){
            close(fd[0]);
            dup2(fd[1],1);
            execlp(command,command,NULL);
        }
        else{
            close(fd[1]);
            pid_t terminated_pid = wait(&status);
            ssize_t readedBytes;
            char * buffer = malloc(sizeof(char) * readedBytes);

            if(WIFEXITED(status)){
                counter++;
                printf("%s: %d\n",command, WEXITSTATUS(status));
                while ((readedBytes = read(fd[0], buffer, MAX_BUFFER_SIZE)) > 0) {
                    buffer[readedBytes-1] = '\0';
                    printf("%s\n",buffer);
                    int output = atoi(buffer);
                    if (output == 0) flag = 1;
                }
            }
            else {
                printf("Something went wrong while running %s",command);
                return -1;
            }
            
        }
    }
    return counter;
}

//NEEDS TO BE FIXED : pipes ? 
int main(int argc, char * argv[]){
    
    pid_t pid;
    pid_t pids[3];
    int status, ret;

    for(int i = 0; i < 3; i++){
        if((pid = fork()) < 0){
            perror("Error while using fork()!\n");
            _exit(-1);
        }
        else if(!pid){
            sleep(10);
            ret = runProgram(argv[i+1]);
            _exit(ret);
        }
        else pids[i] = pid;
    }

    for(int i = 0; i < 3; i++){
        waitpid(pids[i],&status,0);
        if(WIFEXITED(status)){
            if(WEXITSTATUS(status) > 0)
                //results[i] = WEXITSTATUS(status)
                ;
        }
        else printf("Something went wrong running the executables!\n");
    }
}



/*

*/