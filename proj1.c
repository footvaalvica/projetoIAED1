/*
  Ficheiro: proj1.c
  Autor: Mateus Leite Pinho ist199282/al99282
  Descricao: Ponto de entrada para o projeto de IAED20/21
*/

#include <stdio.h>
#include "funcoes.h"

int main () 
{   
    /*Variavel que contem o comando a ser executado*/
    char command;
    /*Le carateres da stdin ate encontrar o caso terminal ou 
    um comando a executar*/
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