#include <stdio.h> 
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>


#define MAX_BUFFER_SIZE 512

int mysystem(char ** command){

    pid_t pid;
    int status;
    int exec_return;

    if((pid = fork()) < 0){
        perror("Error using fork()!\n");
        _exit(-1);
    }
    else if(!pid){
        exec_return = execvp(command[0], command);
        _exit(1);
    }
    else {
        pid_t terminated_pid = wait(&status); 
        if(WIFEXITED(status)){
            printf("FILHO (%d) terminou com sucesso com o codigo (%d)!\n", terminated_pid, WEXITSTATUS(status));
            return exec_return;
        }
        else return -1;
    }
}

int main(int argc, char * argv[]){
    char buffer[MAX_BUFFER_SIZE];
    ssize_t readedBytes;

    pid_t pid;
    int status;

    while((readedBytes = read(0, buffer, MAX_BUFFER_SIZE)) > 0){
        char * args[20];

        buffer[readedBytes-1] = '\0'; //Retirar o \n do input e substituir pelo fim de linha.
        char * arg = strtok(buffer," ");
   
        int i = 0;
        while(arg != NULL){
            args[i] = arg;
            arg = strtok(NULL, " ");
            i++;
        }

        
        if(strcmp(args[i-1], "&") == 0){
            //Execução em segundo plano
            if((pid = fork()) < 0){
                perror("Error using fork()!\n");
                _exit(-1);
            }
            else if (!pid){
                args[i-1] = NULL;
                execvp(args[0], args);
            } 
        }
        else{
            args[i] = NULL;
            //Execução em primeiro plano
            mysystem(args);
        }
    }
    return 0;
}