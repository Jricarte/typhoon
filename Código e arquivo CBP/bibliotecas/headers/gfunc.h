/**
    Biblioteca de Funcoes de Jogo
    -----------------------------------------------
    Aqui sao declaradas as funcoes que serao usadas
    diretamente no jogo
**/
#ifndef GFUNC_H_INCLUDED
#define GFUNC_H_INCLUDED

#include "gstruct.h"

///Funcoes de loop
void gameStart(JOGADOR jog, OBSTACULO *submarinoInimigo, OBSTACULO *mergulhadores);
void startObstaculos(OBSTACULO merg[], OBSTACULO subInim[], JOGO game);

void gameLoop(JOGO game);
void spawnMergulhador(OBSTACULO mergulhadores[]);
void spawnSubInimigo(OBSTACULO submarinoInimigo[]);
void khitDetect(JOGADOR *jog, OBSTACULO merg[], OBSTACULO subInim[], OBSTACULO *torp, int *flag);
void atualizaInfo(JOGADOR *jog, OBSTACULO merg[], OBSTACULO subInim[], OBSTACULO *torp);
void loopSegundo(JOGADOR *jog, int *loop);

///Funcoes esteticas
//Relacionado a moldura
void fazMoldura();
void arrumaMar(JOGADOR j);

//Relacionado a exibicao de informacoes
void desenhaVidas(JOGADOR j);
void apagaVidas();
void desenhaO2(JOGADOR j);
void apagaO2();
void desenhaNmerg(JOGADOR j);
void apagaNmerg();
void fimJogo(JOGADOR j);

///Funcoes do Submarino do Jogador
//Desenho do jogador
void desenhaJogador(JOGADOR j);
void apagaJogador(JOGADOR j);
//Movimento do jogador
void moveJogador(JOGADOR *j,int *flag, OBSTACULO *torp);
//Funcoes relativas a posicao do jogador
int detectaColisao(JOGADOR j, OBSTACULO obs);
void foraAgua(JOGADOR *j);
void atualizaJog(JOGADOR *j);

///Funcoes de Obstaculos
int colisaoObstaculos(OBSTACULO obs1, OBSTACULO obs2);
int temObsLinha(OBSTACULO indv, OBSTACULO vetorobs[], int tamVetor, int ind);
///Funcoes de Torpedo
OBSTACULO iniciaTorpedo(JOGADOR j);
void desenhaTorpedo(OBSTACULO torp);
void apagaTorpedo(OBSTACULO torp);
void moveTorpedo(OBSTACULO *torp);
void bateTorpedoParede(OBSTACULO *torp);
void bateTorpedoSubInim(OBSTACULO *torp, OBSTACULO *sub, JOGADOR *j);
void loopTorpedo(OBSTACULO *torp, OBSTACULO *subInim, JOGADOR *j);

///Funcoes de mergulhadores
//Funcoes de inicializacao dos mergulhadores - Individuais
void inicializaMergulhadores(OBSTACULO *m);
void mudaStatus(OBSTACULO *obs, double prob);
//Desenho dos mergulhadores - Individuais
void desenhaMergulhador(OBSTACULO obs);
void apagaMergulhador(OBSTACULO m);
//Funcoes que mudam o status dos mergulhadores - Individuais e Coletivas
void startMergulhadores(OBSTACULO obs[]);
void atualizaStatusMergulhador(JOGADOR *j, OBSTACULO *obs);
//Funcoes de movimentacao dos mergulhadores - Individuais
void moveMergulhador(OBSTACULO *m);
void bateMergulhadorParede(OBSTACULO *obs);
//Funcao de mergulhadores que atualiza no loop
void funcoesLoopMerg(JOGADOR *jog,OBSTACULO mergulhadores[]);

///Funcoes dos Submarinos Inimigos
void inicializaSubInimigo(OBSTACULO *subI);
void desenhaSubInimigo(OBSTACULO obs);
void apagaSubmarino(OBSTACULO m);
void startSubInimigo(OBSTACULO obs[]);
void bateInimigo(JOGADOR *j, OBSTACULO *obs);
void bateParedeSubmarino(OBSTACULO *obs);
void moveSubInimigo(OBSTACULO *obs);
void subInimigoFinal(JOGADOR *jog,OBSTACULO submarinos[]);

///Funcoes auxiliares
void sleepcp(int milliseconds);
int detectaMorte(JOGADOR j, int *flag);

#endif // GFUNC_H_INCLUDED
