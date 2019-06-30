/**
    Biblioteca de funcoes do menu
    -----------------------------------------------
    Aqui sao declaradas as funcoes que criam o menu
    e chamam as opcoes disponiveis
**/

#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include "../headers/gstruct.h"

//Back-end do menu
void menu();
int decideMenu();
//Front-end do menu
void molduraMenu();
int desenhaMenu(int escolha);
//Funcoes de escolha
void startGame();
void loadGame();
void records();
void creditos();
//Funcoes auxiliares e secundarias
void carregaPeloNome(char nome[]);
int moveApontador(char c, int *p);
void printaCreditos(char texto[LINHAS][CHARMAX]);

#endif // MENU_H_INCLUDED
