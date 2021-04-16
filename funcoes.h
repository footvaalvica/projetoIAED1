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

/* string defines */
#define TOO_MANY_TASKS "too many tasks\n"
#define DUPLICATE_DESCRIPTION "duplicate description\n"
#define INVALID_DURATION "invalid duration\n"
#define TO_DO "TO DO"
#define TASK_PRINTF "task %d\n"
#define NO_SUCH_TASK "%d: no such task\n" 
#define INVALID_TIME "invalid time\n"
#define INVALID_DESCRIPTION "invalid description\n"
#define TOO_MANY_ACTIVITIES "too many activities\n"
#define DUPLICATE_ACTIVITY "duplicate activity\n"


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
typedef struct {
    int id;
    Desc desc;
    User user;
    Act act;
    int dur;
    int inst;
    int toDoInst;
} Task;

/* Time Sort defines */
#define key(A) (A.toDoInst)
#define less(A,B) (key(A) < key(B))

/* Alphabetic Sort defines */
#define keyAlpha(A) (A.desc)
#define lessAlpha(A,B) (strcmp(keyAlpha(A), keyAlpha(B)) < 0)

/* array for merge sort */
Task aux[MAX_ID];
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
void timeSort(Task a[], int left, int right);
void merge(Task a[], int left, int m, int right);
void mergeAlphabetic(Task a[], int left, int m, int right);
void alphabeticSort(Task a[], int left, int right);
int tasklisterErrorCheck(int it, char *user, char *act);
int task();
int taskLister();
int increaser();
int activities();
int utilizador();
int taskmover();
int listtasks();

/* FUNCTIONS */

/*
  timeSort: (Task, int, int) -> void
  Usa merge sort para dar sort ao vetor por tempo na função listtasks()
*/
void timeSort(Task a[], int left, int right)
{
    int m = (right+left)/2;
    if (right <= left) return;
    timeSort(a, left, m);
    timeSort(a, m+1, right);
    merge(a, left, m, right);
}

/*
  merge: (Task, int, int, int) -> void
  Função merge para o merge sort
*/
void merge(Task a[], int left, int m, int right) 
{
    int i, j, k;
    for (i = m+1; i > left; i--)
        aux[i-1] = a[i-1];
    for (j = m; j < right; j++)
        aux[right+m-j] = a[j+1];
    for (k = left; k <= right; k++) {
        if (less(aux[j], aux[i]) || i == m+1)
            a[k] = aux[j--];
        else
            a[k] = aux[i++];
    }
}

/*
  mergeAlphabetic: (Task, int, int, int) -> void
  Função merge para o merge sort alfabetico
*/
void mergeAlphabetic(Task a[], int left, int m, int right)
{
    int i, j, k;
    for (i = m+1; i > left; i--)
        aux[i-1] = a[i-1];
    for (j = m; j < right; j++)
        aux[right+m-j] = a[j+1];
    for (k = left; k <= right; k++) {
        if (lessAlpha(aux[j], aux[i]) || i == m+1)
            a[k] = aux[j--];
        else
            a[k] = aux[i++];
    }
}

/*
  alphabeticSort: (Task, int, int) -> void
  Usa merge sort para dar sort ao vetor alfabeticamente na função listtasks()
  e funcao tasklister()
*/
void alphabeticSort(Task a[], int left, int right)
{
    int m = (right+left)/2;
    if (right <= left) return;
    alphabeticSort(a, left, m);
    alphabeticSort(a, m+1, right);
    mergeAlphabetic(a, left, m, right);
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
    /* inicializar desc a 0 */
    strcpy(desc, "");

    /* lidar com o erro de muitos ids */
    if (id >= MAX_ID) {
        printf(TOO_MANY_TASKS);
        return ERROR;
    }

    /* buscar o input */
    fgets(variables, MAX_STRING_SIZE, stdin);

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
            printf(DUPLICATE_DESCRIPTION);
            /* remove last white space from string*/
            strcpy(desc, "");
            return ERROR;
        }
    }

    /* ver se dur >= 0 */
    if (dur < 0) {
        printf(INVALID_DURATION);
        return ERROR;
    }

    /* criação da tarefa */
    local.id = id;  
    strcpy(local.desc, desc);
    strcpy(local.user, "0");
    strcpy(local.act, TO_DO);
    local.dur = dur;
    local.inst = 0;

    /* remove last white space from string*/
    strcpy(desc, "");

    /*colocação da tarefa na tabela*/
    tasks[id] = local;
    printf(TASK_PRINTF, id);
    id++;    
    return SUCCESS;
}

/*
  tasklister: () -> int
  Lista as tarefas.
*/
int tasklister()
{
    /* inicializar variaveis */
    int i = 0, l, k;
    /* vetor para guardar todos os ids do input*/
    int ids[MAX_ID+1];
    /* vetor que leva sort para nao alterar o original */
    Task localVector[MAX_ID+1];
    /* variaveis para ler o input */
    char *token, variables[MAX_STRING_SIZE];
    /*const para o strtok*/
    const char s[2] = " ";

    /* buscar o input */
    fgets(variables, MAX_STRING_SIZE, stdin);    
    
    /*remover \n da descrição*/
    for (l = 0; variables[l] != '\0'; l++) {}
    variables[l-1] = '\0';
    
    /* se a descrição for vazia */
    if (strcmp(variables, "") == 0) {
        /* copiar todas as tarefas até ao numero de tarefas que existem
        para outro vetor*/
        for (k = 0; k <= id; k++) {
            localVector[k] = tasks[k];
        }
        
        /* sort alphabetically */
        alphabeticSort(localVector, 0, id);

        /* print out results */
        for (k = 2; k <= id; k++) {
            printf("%d %s #%d %s\n", localVector[k].id, localVector[k].act, 
            localVector[k].dur, localVector[k].desc);
        }
    } else {
        /* analisar o input e dividir os ids */
        token = strtok(variables, s);
        while(token != NULL) {
            ids[i] = atoi(token);
            i++;
            if (atoi(token) >= id) {
                printf(NO_SUCH_TASK, id);
                return ERROR;
            }
            token = strtok(NULL, s);
        }
        /* dar print de todos os ids pela ordem do input*/
        for (k = 0; k < (id-1); k++) {
            printf("%d %s #%d %s\n", ids[k], tasks[ids[k]].act, 
            tasks[ids[k]].dur, tasks[ids[k]].desc);
        }
    }
    return SUCCESS;
}

/*
  increaser: () -> int
  Avança o tempo do sistema.
*/
int increaser()
{   
    /*inicializar variaveis */
    int i;
    char variables[MAX_STRING_SIZE];

    /* ler input */
    fgets(variables, MAX_STRING_SIZE, stdin);

    /* remover o white space no inicio*/
    for (i = 0; variables[i] != 0; i++) {
        variables[i] = variables[i+1];
    }
    
    /* error checking */
    /* para verificar se é float estou a procurar o . na string*/
    for (i = 0; variables[i] != 0; i++) {
        if (variables[i] == '.') {
            printf(INVALID_TIME);
            return ERROR;
        }
    }
    /* verificar se é menor que 0 */
    if (atoi(variables) < 0) {
        printf(INVALID_TIME);
        return ERROR;
    }
    
    /* aumentar o global time */
    time += atoi(variables);
    printf("%d\n", time);
    return SUCCESS;
}

/*
  activities: () -> int
  Adiciona uma atividade ou lista todas as atividades.
*/
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
            printf(INVALID_DESCRIPTION);
            return ERROR;
        }
        i++;
    }

    /* too many activities */
    if (actCounter == MAX_ACT) {
        printf(TOO_MANY_ACTIVITIES);
        return ERROR;
    }

    /* dups */
    for (i = 0; i < actCounter; i++)  {
        if (strcmp(acts[i], variables) == 0) {
            printf(DUPLICATE_ACTIVITY);
            return ERROR;
        }
    }

    /* adding the activity */
    strcpy(acts[actCounter], variables);
    actCounter++;
    return SUCCESS;
}

/*
  utilizador: () -> int
  Adiciona um utilizador ou lista todos os utilizadores.
*/
int utilizador() 
{   
    /* inicializar variaveis */
    int i = 0, l;
    char variables[MAX_STRING_SIZE];

    /* storing input in a variable */
    fgets(variables, MAX_STRING_SIZE, stdin);

    /* remover o white space no inicio e o \n*/
    for (i = 0; variables[i] != 0; i++) {
        variables[i] = variables[i+1];
    }
    for (l = 0; variables[l] != '\0'; l++) {}
    variables[l-1] = '\0';

    /* if input is null print out all users */
    if (strcmp(variables, "") == 0) {
        for (i = 0; i < MAX_USERS; i++)  {
            if (strcmp(users[i], "") != 0) {
                printf("%s\n", users[i]);
            }   
        }
        return SUCCESS;
    }

    /*check if user already exists */
    /* look through the whole array for user */
    for (i = 0; i <= userCounter; i++) {
        if (strcmp(users[i],variables) == 0) {
            printf("user already exists\n");
            return ERROR;
        }
    }    

    /* check if there's too many users */
    if (userCounter == (MAX_USERS + 1)) {
        printf("too many users\n");
        return ERROR;
    }

    /*adds user*/
    strcpy(users[userCounter], variables);
    userCounter++;
    return SUCCESS;
}

/*
  taskmover: () -> int
  Move uma tarefa de uma atvidade para outra.
*/
int taskmover()
{
    /* inicializar variaveis */
    /* idLocal, act e user sao para guardar o input */
    int i = 0, l, idLocal, k;
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

    /* verifica todos os erros */

    if (idLocal >= id || idLocal == 0) {
        printf("no such task\n");
        strcpy(act, "");
        return ERROR;
    }

    if (strcmp(act, "TO DO") == 0) {
        printf("task already started\n");
        strcpy(act, "");
        return ERROR;
    }

    for (k = 0; k < MAX_ACT; k++) {
        if (strcmp(acts[k], act) == 0){
            goto FOUND;
        }
    }
    printf("no such activity\n");
    strcpy(act, "");
    return ERROR;
    FOUND:;

    for (k = 0; k < MAX_USERS; k++) {
        if (strcmp(users[k], user) == 0){
            goto END;
        }
    }
    printf("no such user\n");
    strcpy(act, "");
    return ERROR;
    END:;

    if (strcmp(tasks[idLocal].act, act) == 0) {
        strcpy(act, "");
        return ERROR;
    }

    if (strcmp(tasks[idLocal].act, "TO DO") == 0) {
        tasks[idLocal].toDoInst = time;
    }

    /* mudar valores da tarefa*/
    strcpy(tasks[idLocal].user, user);
    strcpy(tasks[idLocal].act, act);
    tasks[idLocal].inst = time;

    if (strcmp(act, "DONE") == 0) {
        printf("duration=%d slack=%d\n", 
        tasks[idLocal].inst - tasks[idLocal].toDoInst, 
        (tasks[idLocal].inst - tasks[idLocal].toDoInst) - tasks[idLocal].dur);
    }
    
    strcpy(act, "");
    return SUCCESS;
}

/*
  listtasks: () -> int
  Lista todas as tarefas que estejam numa dada atividade.
*/
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
    timeSort(localVector, 0, h);

    /* check if values are equal and sort only if they are*/
    for (i = 0; i < h; i++) {
        if (localVector[i].toDoInst == localVector[i+1].toDoInst) {
            alphabeticSort(localVector, i, i+1);
        }
    }

    /* print */
    for (i = 0; i <= h; i++) {
        if (strcmp(localVector[i].act, variables) == 0) {
            printf("%d %d %s\n", localVector[i].id, 
            localVector[i].toDoInst, localVector[i].desc);
        }
    }

    return 0;
}