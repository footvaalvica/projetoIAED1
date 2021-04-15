#ifndef FUNCOES_H_INCLUDED
#define FUNCOES_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

/*defines*/
#define MAX_ID 10000
#define MAX_STRING_SIZE 200
#define DESC_SIZE 50
#define USER_SIZE 20
#define ACT_SIZE 20
#define MAX_ACT 10
#define MAX_USERS 50
#define ERROR -1
#define SUCCESS 0

/*defines boolean values*/
typedef enum {FALSE = 0, TRUE} boolean;
typedef char Act[ACT_SIZE+1];
typedef char User[USER_SIZE+1];
typedef char Desc[DESC_SIZE+1];

/*Declares the struct*/
typedef struct task {
    int id;
    Desc desc;
    User user;
    Act act;
    int dur;
    int inst;
    int toDoInst;
} Task;

/* declares global variables */
Task tasks[MAX_ID+1];
Act acts[MAX_ACT] = {{"TO DO"}, {"IN PROGRESS"}, {"DONE"}, {""}, {""}, {""}, {""}, {""}, {""}, {""}};
User users[MAX_USERS+1];
int actCounter = 3;
int userCounter = 0;
int id = 1;
int time = 0;

/* prototypes */
void timeInsertionSort(Task arr[], int n);
void alphabeticInsertionSort(Desc arr[], int n);
int task();
int tasklister();
int increaser();
int activities();
int utilizador();
int taskmover();
int listtasks();

#endif