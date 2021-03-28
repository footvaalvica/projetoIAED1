#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "task.h"

int main () 
{   
    char command;
    /* Reads which command is going to be executed */
    do {
        scanf("%c", &command);
        switch(command) {
            case 't':
                task();
                break;

            case 'l':
                tasklister();
                break;

            case 'n':
                increaser();
                break;

            case 'u':
                utilizador();
                break;
                
            case 'm':
                taskmover();
                break;

            case 'd':
                listtasks();
                break;

            case 'a':
                activities();
                break;
        }
    }
    while(command != 'q');
    return 0;    
}