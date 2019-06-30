/**
    Biblioteca de Funcoes de arquivo
    -------------------------------------------------
    Aqui sao declaradas todas as funcoes relacionadas
    a abrir ou gravar algum arquivo no jogo
**/

#ifndef GFILE_H_INCLUDED
#define GFILE_H_INCLUDED

#include "gstruct.h"
#include <stdio.h>

//Funcoes para salvar o jogo
void salvaNome(JOGADOR *j);
void salvaEscolha(char *escolha);
void salvaJogo(JOGADOR *j, OBSTACULO merg[], OBSTACULO subInim[], JOGO *game);
int criaArq(char *nome, JOGO *game);
void gravaArq(FILE *arq, JOGO *buff);
//Funcoes para carregar um jogo
int leArq(JOGO *game, char player[]);
int carrega(FILE *arq, JOGO *game);
//Funcoes para carregar Ranking
int leRanking();
int mostraRanking(FILE *arq);
//Funcoes para Salvar no Ranking
void ordenaRank(JOGADOR j, char nomeUsr[], char nome[TAMRANK+1][MAX_CHAR_RANK], int pts[]);
void salvaRankArq(char nome[TAMRANK+1][MAX_CHAR_RANK], int pts[], FILE *arq);
int abreRanking(JOGADOR j);
int montaRanking(FILE *arq, JOGADOR j);

#endif // GFILE_H_INCLUDED
