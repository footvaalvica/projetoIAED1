/* INCLUDES */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

/* DEFINES */

/* max number of IDs sorted */
#define MAX_ID 10000
/* max size of characters read from input*/
#define MAX_STRING_SIZE 200
/* max size of description string*/
#define DESC_SIZE 50
/* max size of user string*/
#define USER_SIZE 20
/* max size of activity string*/
#define ACT_SIZE 20
/* max number of ACTIVITIES*/
#define MAX_ACT 10
/* max number of USERS */
#define MAX_USERS 50
/* error code */
#define ERROR -1
/* success code */
#define SUCCESS 0

/*defines activity string */
typedef char Act[ACT_SIZE+1];
/*defines user string */
typedef char User[USER_SIZE+1];
/*defines description string */
typedef char Desc[DESC_SIZE+1];

/*
  Task: int, Desc, User, Act, int, int, int
  Representa um produto constituida por id, descricao, utilizador, atividade,
  duracao, e instante de inicio
*/
typedef struct task {
    int id;
    Desc desc;
    User user;
    Act act;
    int dur;
    int inst;
    int toDoInst;
} Task;

/*array of tasks*/
Task tasks[MAX_ID+1];
/*array of activity strings */
Act acts[MAX_ACT] = {{"TO DO"}, {"IN PROGRESS"}, {"DONE"}, {""}, 
{""}, {""}, {""}, {""}, {""}, {""}};
/* array of users */
User users[MAX_USERS+1];
/*counts how many activities exist */
int actCounter = 3;
/*counts how many users have been created */
int userCounter = 0;
/* counts how many tasks have been created */
int id = 1;
/* counts time */
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

/* FUNCTIONS */

/* ok ja tenho as funções quase todas :D */
/* mudar os sorts para ficarem como os do prof */
void timeInsertionSort(Task arr[], int n)
{
    int i, key, j;
    for (i = 1; i < n; i++) {
        key = arr[i].toDoInst;
        j = i - 1;
 
        /* Move elements of arr[0..i-1], that are
          greater than key, to one position ahead
          of their current position */
        while (j >= 0 && arr[j].toDoInst > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1].toDoInst = key;
    }
}

/*change this function if possible, because it sorts a new array 
instead of sorting the already existing one, it's just a waste of resouces*/
void alphabeticInsertionSort(Desc arr[], int n)
{
    int i, j;
    Desc key;
    for (i = 1; i < n; i++) {
        strcpy(key, arr[i]);
        j = i - 1;
 
        /* Move elements of arr[0..i-1], that are
          greater than key, to one position ahead
          of their current position */
        while (j >= 0 && (strcmp(arr[j], key) > 0)) {
            strcpy(arr[j + 1], arr[j]);
            j = j - 1;
        }
        strcpy(arr[j + 1],key);
    }
}

/*
  task: () -> int
  Cria uma tarefa nova.
*/
int task() 
{
    /* iniciar variaveis */
    Task local;
    int dur = 0, i = 0, l, k;
    char desc[DESC_SIZE], *token, variables[MAX_STRING_SIZE];
    const char s[2] = " "; /*const para o strtok*/

    /* lidar com o erro de muitos ids */
    if (id >= MAX_ID) {
        printf("too many tasks\n");
        return ERROR;
    }

    /* buscar o input */
    fgets(variables, MAX_STRING_SIZE, stdin);

    /* inicializar desc a 0 */
    strcpy(desc, "");
    
    /* divides the input based on spaces */
    token = strtok(variables, s);
    while(token != NULL) {
        if (i == 0)
            dur = atoi(token);
        else {
            strcat(desc, token);
            /*adds white space*/
            strcat(desc, " ");
        }
        i++;
        token = strtok(NULL, s);
    }

    /*remover \n da descrição*/
    for (l = 0; desc[l] != '\0'; l++) {}
    desc[l-2] = '\0';


    /* procurar duplicate descriptions */
    for (k = 1; k <= id; k++) {
        if (strcmp(tasks[k].desc, desc) == 0) {
            printf("duplicate description\n");
            /* remove last white space from string*/
            strcpy(desc, "");
            return ERROR;
        }
    }

    /* ver se dur >= 0 */
    if (dur < 0) {
        printf("invalid duration\n");
        return ERROR;
    }

    /* criação da tarefa */
    local.id = id;  
    strcpy(local.desc, desc);
    strcpy(local.user, "0");
    strcpy(local.act, "TO DO");
    local.dur = dur;
    local.inst = 0;

    /* remove last white space from string*/
    strcpy(desc, "");

    /*colocação da tarefa na tabela*/
    tasks[id] = local;
    printf("task %d\n", id);
    id++;    
    return SUCCESS;
}

int tasklister()
{
    int i = 0, l, k, h;
    int ids[MAX_ID+1];
    Desc descs[MAX_ID+1];
    char *token, variables[MAX_STRING_SIZE];
    const char s[2] = " "; /*const para o strtok*/

    /* buscar o input */
    fgets(variables, MAX_STRING_SIZE, stdin);    
    
    /*remover \n da descrição*/
    for (l = 0; variables[l] != '\0'; l++) {}
    variables[l-1] = '\0';
    
    if (strcmp(variables, "") == 0) {
        /*adicionar alphabetic sort*/
        for (k = 1; k <= id; k++) {
            strcpy(descs[k], tasks[k].desc);
        }
        
        /*dar o sort alphabetic */
        alphabeticInsertionSort(descs, id);

        for (k = 1; k <= id; k++) {
            for (h = 1; h < id; h++) {
                if (strcmp(descs[k], tasks[h].desc) == 0) {
                    printf("%d %s #%d %s\n", tasks[h].id, tasks[h].act, 
                    tasks[h].dur, tasks[h].desc);
                }
            }
        }
    return 0;
    } else {
        /* analisar o input
        ainda nao sei como é que vou lidar com isto, eles nao especificam */
        token = strtok(variables, s);
        while(token != NULL) {
            ids[i] = atoi(token);
            i++;
            if (atoi(token) >= id) {
                printf("%d: no such task\n", id);
                return -1;
            }
            token = strtok(NULL, s);
        }
        for (k = 0; k < (id-1); k++) {
            printf("%d %s #%d %s\n", ids[k], tasks[ids[k]].act, 
            tasks[ids[k]].dur, tasks[ids[k]].desc);
        }
    return 0;
    }
}

int increaser()
{
    int i;
    char variables[MAX_STRING_SIZE];

    fgets(variables, MAX_STRING_SIZE, stdin);

    /* remover o white space no inicio*/
    for (i = 0; variables[i] != 0; i++) {
        variables[i] = variables[i+1];
    }
    
    /* error checking */
    /* para verificar se é float estou à procurar do .*/
    for (i = 0; variables[i] != 0; i++) {
        if (variables[i] == '.') {
            printf("invalid time\n");
            return -1;
        }
    }

    if (atoi(variables) < 0) {
        printf("invalid time\n");
        return -1;
    }
    
    /* aumentar o global time */
    time += atoi(variables);
    printf("%d\n", time);
    return 0;
}

int activities() 
{
    int i = 0, l;
    char variables[MAX_STRING_SIZE];

    fgets(variables, MAX_STRING_SIZE, stdin);

    /* remover o white space no inicio e o \n*/
    for (i = 0; variables[i] != 0; i++) {
        variables[i] = variables[i+1];
    }
    for (l = 0; variables[l] != '\0'; l++) {}
    variables[l-1] = '\0';

    if (strcmp(variables, "") == 0) {
        /*prints all variables */
        for (i = 0; i < actCounter; i++)  {
            printf("%s\n", acts[i]);   
        }
        return 0;
    }
    
    /* error checking */
    /* uppercase check*/
    i = 0;
    while (variables[i] != '\0') {
        if (islower(variables[i]) != 0) {
            printf("invalid description\n");
            return -1;
        }
        i++;
    }

    /* too many activities */
    if (actCounter == (MAX_ACT - 1)) {
        printf("too many activities\n");
        return -1;
    }

    /* dups */
    for (i = 0; i < actCounter; i++)  {
        if (strcmp(acts[i], variables) == 0) {
            printf("duplicate activity\n");
            return -1;
        }
    }

    /* adding the activity */
    strcpy(acts[actCounter], variables);
    actCounter++;
    return 0;
}

int utilizador() 
{
    int i = 0, l;
    char variables[MAX_STRING_SIZE];

    fgets(variables, MAX_STRING_SIZE, stdin);

    /* remover o white space no inicio e o \n*/
    for (i = 0; variables[i] != 0; i++) {
        variables[i] = variables[i+1];
    }
    for (l = 0; variables[l] != '\0'; l++) {}
    variables[l-1] = '\0';

    /*proibir de ter whitespaces or maybe not assumo só q o input está correto é ver o q dá*/
    
    if (strcmp(variables, "") == 0) {
        /*prints all users */
        for (i = 0; i < MAX_USERS; i++)  {
            if (strcmp(users[i], "") != 0) {
                printf("%s\n", users[i]);
            }   
        }
        return 0;
    }

    /*check if user already exists */
    for (i = 0; i <= userCounter; i++) {
        if (strcmp(users[i],variables) == 0) {
            printf("user already exists\n");
            return -1;
        }
    }    

    /* too many users */
    if (userCounter == (MAX_USERS - 1)) {
        printf("too many users\n");
        return -1;
    }

    /*adds user*/
    strcpy(users[userCounter], variables);
    userCounter++;
    return 0;
}

int taskmover()
{
    int i = 0, l, idLocal, k;
    boolean noActFound = TRUE;
    boolean noUserFound = TRUE;
    char *token, variables[MAX_STRING_SIZE];
    Act act;
    User user;
    const char s[2] = " "; /*const para o strtok*/

    /* buscar o input */
    fgets(variables, MAX_STRING_SIZE, stdin);

    /*inicializar act a 0*/
    strcpy(act, "");
    /* analisar o input
    ainda nao sei como é que vou lidar com isto, eles nao especificam */
    token = strtok(variables, s);
    while(token != NULL) {
        if (i == 0) {
            idLocal = atoi(token);
        } else if (i == 1) {
            strcpy(user, token);
        } else {
            strcat(act, token);
            /*adds white space*/
            strcat(act, " ");
        }
        i++;
        token = strtok(NULL, s);
    }

    /*remover \n do act*/
    for (l = 0; act[l] != '\0'; l++) {}
    act[l-2] = '\0';

    if (idLocal >= id) {
        printf("no such task\n");
        strcpy(act, "");
        return -1;
    }

    if (strcmp(act, "TO DO") == 0) {
        printf("task already started\n");
        strcpy(act, "");
        return -1;
    }

    for (k = 0; k < MAX_ACT; k++) {
        if (strcmp(acts[k], act) == 0){
            noActFound = FALSE;
        }
    }

    if (noActFound == TRUE) {
        printf("no such activity\n");
        strcpy(act, "");
        return -1;
    }

    for (k = 0; k < MAX_USERS; k++) {
        if (strcmp(users[k], user) == 0){
            noUserFound = FALSE;
        }
    }

    if (noUserFound == TRUE) {
        printf("no such user\n");
        strcpy(act, "");
        return -1;
    }

    if (strcmp(tasks[idLocal].act, "TO DO") == 0) {
        tasks[idLocal].toDoInst = time;
    }

    /* mudar valores da tarefa*/
    strcpy(tasks[idLocal].user, user);
    strcpy(tasks[idLocal].act, act);
    tasks[idLocal].inst = time;

    if (strcmp(act, "DONE") == 0) {
        printf("duration=%d slack=%d\n", tasks[idLocal].inst - tasks[idLocal].toDoInst, (tasks[idLocal].inst - tasks[idLocal].toDoInst) - tasks[idLocal].dur);
    }
    
    strcpy(act, "");
    return 0;
}

/* falta dar sort do output alfabeticamente*/
int listtasks() 
{
    int i = 0, l;
    int h = 1;
    Task localVector[MAX_ID+1];
    char variables[MAX_STRING_SIZE];

    fgets(variables, MAX_STRING_SIZE, stdin);

    /* remover o white space no inicio e o \n*/
    for (i = 0; variables[i] != 0; i++) {
        variables[i] = variables[i+1];
    }
    for (l = 0; variables[l] != '\0'; l++) {}
    variables[l-1] = '\0';

    for (i = 1; i < id; i++) {
        if (strcmp(tasks[i].act, variables) == 0) {
            localVector[h] = tasks[i];
            h++;
        }
    }

    /*sort */
    timeInsertionSort(localVector, h);

    /* print */
    for (i = 0; i < h; i++) {
        if (strcmp(localVector[i].act, variables) == 0) {
            printf("%d %d %s\n", localVector[i].id, localVector[i].toDoInst, localVector[i].desc);
        }
    }

    return 0;
}