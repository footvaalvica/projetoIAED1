#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "task.h"

int main () 
{   
    char command;
    /* Reads which command is going to be executed */
    scanf("%c", &command);
    switch(command)
        {
            case 'q':
                return 0;
                break;

            case 't':
                task();
                main();
                break;

            case 'l':
                return 0;
                break;

            case 'n':
                increaser();
                main();
                break;

            case 'u':
                utilizador();
                main();
                break;
            
            case 'm':
                return 0;
                break;

            case 'd':
                listtasks();
                main();
                break;

            case 'a':
                activities();
                main();
                break;

            /* qnd o commando n é dos q queriamos voltar a chamar a função*/
            default:
                main();
        }
    return 0;    
}