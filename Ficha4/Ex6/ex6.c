#include <stdio.h> 
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define Linhas 10
#define Colunas 1000

int ** initMatrix(){
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
    return matrix;
}

void search(int ** matrix, int target, int * results){
    int fd[2];
    pid_t pid;
    pid_t pids[Linhas];
    int status;

    if (pipe(fd) < 0){
        perror("Error creating pipe!\n");
        _exit(-1);
    }

    for(int i = 1; i <= Linhas; i++){
        if((pid = fork()) < 0){
            perror("Error while using fork()!\n");
            _exit(-1);
        }
        else if(!pid){
            close(fd[0]);

            int needle = 0;
            for(int j = 0; j < Colunas; j++){
                if(target == matrix[i-1][j]){
                    int msg = i-1;
                    write(fd[1], &msg, sizeof(int));
                    needle=1;
                }
            }
            close(fd[1]);
            if(!needle) _exit(-2);
            else _exit(0);
        }
        else 
            pids[i-1] = pid;
    }

    close(fd[1]);
    ssize_t readedBytes;
    int buf;

    while((readedBytes = read(fd[0], &buf, sizeof(buf))) > 0)
        results[buf]++;
    
    close(fd[0]);

    for(int i = 0; i < Linhas; i++){
        pid_t terminated_pid = waitpid(pids[i],&status,0);
    }
}

int main(int argc, char * argv[]){

    int ** matrix = initMatrix();
    
    int target;
    if(argc == 2){
		target = atoi(argv[1]);
	}
	else{
		printf("Target needed!\n");
		_exit(-1);
	}

    int * result = malloc(sizeof(int) * Linhas);
    for(int i = 0; i < Linhas; i++) result[i] = 0;

    search(matrix, target, result);

    for(int i = 0; i < Linhas; i++) 
        printf("%d,",result[i]);
    printf("\n");
    
    return 0;
}