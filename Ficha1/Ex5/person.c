#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <fcntl.h> /* O_RDONLY, O_WRONLY, O_CREAT, O_* */
#include <time.h>
#include <math.h>
#include "person.h"

#define MAX_BUFFER_SIZE 128

int checkInput(char * buffer, ssize_t readedBytes){
    char * input = strtok(buffer," ");
    char * flag = input[1];
    if(flag == "-i")
        return 0;
    else if(flag == "-u")
        return 1;
    return -1;
}

void addPerson(char * name, int age){
    int fd = open("file", O_CREAT, O_WRONLY, O_APPEND, 0640);
    Person p;
    p->idade = age;
    strcpy(p->nome,name);
    lseek(fd,0,SEEK_END);
    write(fd,p,sizeof(struct person));
    close(fd);
}

int updateAge(char * name, int new_age){
    int fd = open("file", O_RDWR, 0600);
    Person p;
    while(read(fd,p, sizeof(struct person)) > 0){
        if(strcmp(p->nome,name) == 0){
            p->idade = new_age;
            l_seek(fd,-sizeof(struct person), SEEK_CUR);
            write(fd,p, sizeof(struct person));
            return 0;
        }
    }
    return 1;
}
int main(int argc, char * argv[]){
    int fd_read ;
    char * buffer = malloc(sizeof(char) * MAX_BUFFER_SIZE);
    ssize_t readedBytes;
    while(readedBytes = read(0,buffer,MAX_BUFFER_SIZE) > 0){
        int op;
        if( (op = checkInput(buffer, readedBytes)) > 0){
            char * input = strtok(buffer," ");
            if (op == 0)
                addPerson(input[2], atoi(input[3])); // adicionar uma pessoa ao ficheiro binario
            else 
                if(updateAge(input[2], atoi(input[3])) == 0) // atualizar idade de uma pessoa num ficheiro
                    printf("Age updated succesufully!\n");
                else printf("Something went wrong!\n");
        }
    }
}
