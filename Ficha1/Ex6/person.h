#ifndef __PERSON
#define __PERSON

void addPerson(Person new_person, int age);
void updateAge(int new_age);

typedef struct person{
    char nome[50];
    int idade;
} * Person;

#endif