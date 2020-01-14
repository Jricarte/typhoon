/**
    Biblioteca de Funcoes de ARQUIVO
    -------------------------------------------------
    Aqui sao declaradas todas as funcoes relacionadas
    a abrir ou gravar algum arquivo no jogo
    
    Sim, aqui temos datas
**/

//Header game File
#include "../headers/gFile.h"
//Bibliotecas Importadas
#include <stdio.h>
#include <stdlib.h>
#include <conio2.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include "../headers/gstruct.h"
#include "../headers/menu.h"
///Salva o arquivo Criado no jogo

void salvaNome(JOGADOR *j)//auxiliar
{
    do
    {
        cputsxy(POS_X_INTER, LINHA_SALVAR+4, "Insira seu nome(MAX 10) >\n");
        cputsxy(POS_X_INTER, LINHA_SALVAR+6, ""); //para escrever na linha 16
        gets(j->nome);
    } while(strlen(j->nome) > MAX_CHAR_NOME);
}

void salvaEscolha(char *escolha)//auxiliar
{
    cputsxy(POS_X_INTER, LINHA_SALVAR,"Deseja salvar o jogo?\n");
    cputsxy(POS_X_INTER, LINHA_SALVAR+2,"[S]im\t[N]ao\n");
    do
    {
        *escolha = getch();
        *escolha = toupper(*escolha);
    } while (*escolha != 'S' && *escolha != 'N');
}

void salvaJogo(JOGADOR *j, OBSTACULO merg[], OBSTACULO subInim[], JOGO *game)
{
    int i;
    char escolha, nome[TAM_NOME_ARQUIVO];

    clrscr(); //Limpa tela

    salvaEscolha(&escolha);//auxiliar para consistencia
    if (escolha == 'S')
    {
        salvaNome(j);//auxiliar para pegar o nome com consistencia
        game->jogador = *j;
        for(i=0; i<NUM_MAX_MERG; i++)
            game->mergulhadores[i] = merg[i];
        for(i=0; i<MAXINIM; i++)
            game->submarinosInim[i] = subInim[i];
        strcpy(nome, j->nome);
        strcat(nome, ".jag");
        criaArq(nome, game);
    }
    clrscr();
}

int criaArq(char *nome, JOGO *game)
{
    FILE *arq;
    if(!(arq = fopen(nome, "wb"))) //Abre o arquivo e executa msg de erro caso ocorra
    {
        printf("ERRO DE CRIACAO");
        return 1;
    }
    else
    {
        gravaArq(arq, game); //Grava o arquivo
        return 0;
    }
}

void gravaArq(FILE *arq, JOGO *buff)
{
    if(fwrite(buff, sizeof(JOGO), 1, arq) != 1) //Grava o jogo e exibe msg de erro caso ocorra
        printf("Erro ao gravar jogo\n");
    fclose(arq);
}

///Abre o arquivo do jogo
int leArq(JOGO *game, char player[])
{
    FILE *arq;
    if(!(arq = fopen(player, "rb")))
    {
        printf("ERRO DE ABERTURA"); //Abre o arquivo e executa msg de erro caso ocorra
        return 1;
    }
    else
        return (carrega(arq, game)); //Carrega o jogo
}

int carrega(FILE *arq, JOGO *game)
{
    if(fread(game, sizeof(JOGO), 1, arq) != 1) //Le e envia a msg de erro caso ocorra
    {
        printf("ERRO DE LEITURA");
        fclose(arq);
        return 1;
    }
    else
    {
        fclose(arq);
    }
    return 0;
}

int leRanking()
{
    FILE *arq;
    arq = fopen("ranking.txt", "r");
    if(!arq)
    {
        printf("ERRO DE ABERTURA DO RANKING\nAperte qualquer tecla para sair");
        return 1;
    }
    else
    {
        mostraRanking(arq);
    }
    return 0;
}

int mostraRanking(FILE *arq)
{
    char buffer[BUFFERTXT], nome[TAMRANK][MAX_CHAR_RANK], botao;
    int pts[TAMRANK], i=0, menorPt=99999;

    textcolor(WHITE);
    cputsxy(CENTER, LINHA_TITULO, "RANKING");

    while(!feof(arq))
    {
        textcolor(WHITE);
        fgets(buffer, BUFFERTXT, arq);
        strcpy(nome[i], strtok(buffer, ","));
        pts[i] = atoi(strtok(NULL,"\n"));
        gotoxy(POS_X_INTER, LINHA_PRINT_RANK+i);

        switch(pts[i])
        {
        // alguns anos que como referencia, muda cor do recorde
        case 1917:
            textcolor(RED); break;
        case 1863:
            textcolor(YELLOW); break;
        case 1500:
            textcolor(GREEN); break;
        }

        printf("%d - %10s%8d\n", i+1, nome[i], pts[i]);

        if(pts[i] < menorPt)
            menorPt = pts[i];
        i++;
    }
    fclose(arq);
    do{
        cputsxy(POS_X_INTER, AVISO_GRANDE, "ESPACO para sair");
        botao = getch();
    } while(botao != ESP);

    clrscr();
    return menorPt;
}

int abreRanking(JOGADOR j)
{
    textcolor(WHITE);
    FILE *arq = fopen("ranking.txt", "r+");
    if(!arq)
    {
        printf("ERRO DE ABERTURA DO RANKING \n Aperte qualquer tecla para sair");
        return 1;
    }
    return montaRanking(arq, j);
}

void ordenaRank(JOGADOR j, char nomeUsr[], char nome[TAMRANK+1][MAX_CHAR_RANK], int pts[]) //auxiliar
{
    int auxInt, ptCompara, i;
    char auxChar[MAX_CHAR_RANK];

    ptCompara = j.pontos;
    for(i=0; i<TAMRANK+1; i++)
    {
        if(ptCompara > pts[i])
        {
            auxInt = pts[i];
            strcpy(auxChar, nome[i]);

            pts[i] =  ptCompara;
            strcpy(nome[i], nomeUsr);

            ptCompara = auxInt;
            strcpy(nomeUsr, auxChar);
        }
    }
}

void salvaRankArq(char nome[TAMRANK+1][MAX_CHAR_RANK], int pts[], FILE *arq)//salva no arquivo - AUXILIAR
{
    int i;

    for(i=0; i<TAMRANK-1; i++)
    {
        fprintf(arq, "%s,%d\n", nome[i], pts[i]);
    }
    fprintf(arq, "%s,%d", nome[i], pts[i]);
}

int montaRanking(FILE *arq, JOGADOR j)
{
    char nomeUsr[MAX_CHAR_RANK], buffer[BUFFERTXT], nome[TAMRANK+1][MAX_CHAR_RANK]={};
    int pts[TAMRANK+1]={}, i=0;
    clrscr();

    //Salva os nomes em array
    while(!feof(arq))
    {
        fgets(buffer, BUFFERTXT, arq);
        strcpy(nome[i], strtok(buffer, ","));
        pts[i] = atoi(strtok(NULL,"\n"));
        i++;
    }

    if(j.pontos > pts[MENOR_RANK])
    {
        do{
            printf("\nInsira seu nome(MAX 8) > ");
            gets(nomeUsr);
        } while(strlen(nomeUsr) > MAX_CHAR_RANK-1 || strlen(nomeUsr) <= 0); // -1 para colocar o \n
    }

    ordenaRank(j, nomeUsr, nome, pts);

    rewind(arq);

    salvaRankArq(nome, pts, arq);

    fclose(arq);

    return 0;
}
