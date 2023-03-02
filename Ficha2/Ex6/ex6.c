#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <fcntl.h> /* O_RDONLY, O_WRONLY, O_CREAT, O_* */
#include <unistd.h>

#define Linhas 10
#define Colunas 1000

int main(int argc , char * argv[]){
    int ** matrix = (int**) malloc(Linhas * sizeof(int*));
    
    int rand_max = 10000;
    printf("Generating numbers from 0 to %d... ",rand_max);
    for(int i = 0; i < Linhas; i++){
        matrix[i] = (int*) malloc(sizeof(int) * Colunas);
        for( int j = 0; j < Colunas; j++){
            matrix[i][j] = rand() % rand_max;
        }
    }
    printf("Done.\n");
    int target;
    if(argc == 2){
		target = atoi(argv[1]);
	}
	else{
		printf("Target needed!\n");
		_exit(-2);
	}
    int status;
    pid_t pid;

    pid_t pids[Linhas];

    for(int i = 1; i <= Linhas; i++){
        if((pid = fork()) < 0){
            perror("Error while using fork()!\n");
            _exit(-2);
        }
        else if(!pid){
            int needle = 0;
            for(int j = 0; j < Colunas && !needle;j++){
                if(target == matrix[i-1][j])
                    _exit(i-1);
            }
            _exit(200);
        }
        else 
            pids[i-1] = pid;
    }
    for(int i = 0; i < Linhas; i++){
        pid_t terminated_pid = waitpid(pids[i],&status,0);

        if(WIFEXITED(status)){
            if(WEXITSTATUS(status) == 200)
                printf("Not found -> line number %d\n", i);
            else if (WEXITSTATUS(status) > 0){
                printf("Found the target %d in the line %d\n",target, WEXITSTATUS(status));
            }
        }
    }

    return 0;
}