/*
  Ficheiro: proj1.c
  Autor: Bruno Miguel da Silva Mendes ist199282/al99282
  Descricao: Ponto de entrada para o projeto de IAED19/20
*/

#include <stdio.h>
#include "funcoes.h"

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