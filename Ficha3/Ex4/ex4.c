#include <stdio.h> 
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int mysystem(char * command){
    char * args[50];
    char * arg = strtok(command," ");
   
    int i = 0;
    while(arg != NULL){
        args[i] = arg;
        arg = strtok(NULL, " ");
        i++;
    }

    args[i] = NULL; 

    pid_t pid;
    int status;
    int exec_return;

    if((pid = fork()) < 0){
        perror("Error using fork()!\n");
        _exit(-1);
    }
    else if(!pid){
        exec_return = execvp(args[0], args);
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
    char command[50];
    for(int i = 1; i < argc; i++){
        strcat(command,argv[i]);
        strcat(command," ");
    }
    int system_return = mysystem(command);
    printf("Código retorno da call system: (%d)\n",system_return);
    return 0;
}