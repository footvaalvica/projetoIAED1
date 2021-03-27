#define MAX_ID 10000
#define MAX_STRING_SIZE 200
#define DESC_SIZE 50
#define USER_SIZE 20
#define ACT_SIZE 20
#define MAX_ACT 10
#define MAX_USERS 50

typedef char Act[ACT_SIZE];
typedef char User[USER_SIZE];

/*Declares the struct*/
typedef struct task {
    int id;
    char desc[DESC_SIZE];
    User user;
    Act act;
    int dur;
    int inst;
} Task;

/* declares global variables */

Task tasks[MAX_ID];
Act acts[MAX_ACT] = {{"TO DO"}, {"IN PROGRESS"}, {"DONE"}, {""}, {""}, {""}, {""}, {""}, {""}, {""}};
User users[MAX_USERS];
int actCounter = 3;
int userCounter = 0;
int id = 1;
int time = 0;

int task () {
    Task local;
    int dur = 0, i = 0, l;
    char desc[DESC_SIZE], *token, variables[MAX_STRING_SIZE];
    const char s[2] = " "; /*const para o strtok*/

    /* lidar com o erro de muitos ids */
    if (id >= MAX_ID) {
        printf("too many tasks\n");
        return -1;
    }

    /* buscar o input */
    fgets(variables, MAX_STRING_SIZE, stdin);
    
    /* analisar o input
    ainda nao sei como é que vou lidar com isto, eles nao especificam */
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

    /*remover ultimo white space da descrição */
    for (l = 0; desc[l] != '\0'; l++) {}
    desc[l-1] = '\0';

    /* procurar duplicate descriptions */
    for (i=1; i <= id; i++) {
        if (strcmp(tasks[i].desc, desc) == 0) {
            printf("duplicate description\n");
            return -1;
        }
    }

    /* criação da tarefa*/
    local.id = id;  
    strcpy(local.desc, desc);
    strcpy(local.user, "0");
    strcpy(local.act, "TO DO");
    local.dur = dur;
    local.inst = time;

    /*colocação da tarefa na tabela*/
    tasks[id] = local;
    printf("task %d\n", id);
    id++;
    return 0;
}

int increaser() {
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

    if (atoi(variables) <= 0) {
        printf("invalid time\n");
        return -1;
    }
    
    /* aumentar o global time */
    time += atoi(variables);
    printf("%d\n", time);
    return 0;
}

int activities() {
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

int utilizador() {
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

int listtasks() {
    int i = 0, l;
    char variables[MAX_STRING_SIZE];

    fgets(variables, MAX_STRING_SIZE, stdin);

    /* remover o white space no inicio e o \n*/
    for (i = 0; variables[i] != 0; i++) {
        variables[i] = variables[i+1];
    }
    for (l = 0; variables[l] != '\0'; l++) {}
    variables[l-1] = '\0';

    /* verificar se ha alguma activity q de match */

    /* maybe preciso de criar um vetor? que pita */
    for (i = 1; i <= id; i++) {
        if (strcmp(tasks[i].act,variables) == 0) {
            printf("%d %d %s", tasks[i].id, tasks[i].inst, tasks[i].desc);
        }
    }

    return 0;
}