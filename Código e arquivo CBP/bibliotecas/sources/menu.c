/**
    Biblioteca de funcoes do menu
    -----------------------------------------------
    Aqui sao declaradas as funcoes que criam o menu
    e chamam as opcoes disponiveis
**/

//Header menu
#include "../headers/menu.h"
//Bibliotecas Importadas
#include <stdio.h>
#include <stdlib.h>
#include <conio2.h>
#include <time.h>
#include <string.h>
#include <windows.h>
#include "../headers/gfunc.h"
#include "../headers/gstruct.h"
#include "../headers/gFile.h"

///Backend do menu, executa a funcao selecionada pelo usuario
void menu()
{
    int escolha, flag=1;
    do
    {
        escolha = decideMenu();
        textcolor(LIGHTGRAY);
        clrscr();
        switch(escolha)
        {
        case 1: //Novo jogo
            startGame(); break;
        case 2: //Continuar Jogo
            loadGame(); break;
        case 3: //Recordes
            records(); break;
        case 4: //Creditos
            creditos(); break;
        case 5: //Sair
            flag = 0; break;
        default:
            break;
        }
    } while(flag);
}

///Backend do menu, muda a opção selecionada no menu
int decideMenu()
{
    int pos = 1; //Posicao do apontador (>)
    int flag = 1; //Muda quando aperta ESPACO
    char c;
    desenhaMenu(pos);

    while(flag)
    {
        if(kbhit())
        {
            c = getch();
            if(c == EXT)
            {
                c= getch();
                ///criar função secundaria
                switch(c)
                {
                case CIMA:
                    if(pos>1) pos--; break;
                case BAIXO:
                    if(pos<5) pos++; break;
                }
                desenhaMenu(pos);
            }
            else if(c == ESP)
            {
                flag = 0;
                return pos;
            }
        }
    }
    return -1;
}
///Front-end do menu, desenha a moldura
void molduraMenu()
{
    TELA parede = {{XINICIAL,YINICIAL}, {XFINAL, YFINAL}};
    int i;
    //imprime linhas
    for(i=parede.ptUm.x; i<parede.ptDois.x; i++)
    {
        putchxy(i, YINICIAL, '-');
        putchxy(i, YFINAL, '-');
    }
    for(i=parede.ptUm.y; i<parede.ptDois.y; i++)
    {
        putchxy(XINICIAL, i, '|');
        putchxy(XFINAL, i, '|');
    }
}

///Fornt-end do menu, Cria a interface
int desenhaMenu(int escolha)
{
    textcolor(WHITE);
    molduraMenu();
    textcolor(YELLOW);
    cputsxy(37, 5, "TYPHOON");
    switch(escolha)
    {
        case 1:
            textcolor(WHITE);
            cputsxy(POS_X_INTER, 9, "           "); //Apaga o escrito antes da opcao selecionada
            cputsxy(POS_X_INTER, 12, "- Carregar Jogo  ");
            cputsxy(POS_X_INTER, 15, "- Recordes  ");
            cputsxy(POS_X_INTER, 18, "- Creditos  ");
            cputsxy(POS_X_INTER, 21, "- Sair");
            textcolor(YELLOW);
            cputsxy(POS_X_INTER+2, 9, "> Novo Jogo"); //Opcao selecionada
            return 1; break;

        case 2:
            textcolor(WHITE);
            cputsxy(POS_X_INTER, 9, "- Novo Jogo  ");
            cputsxy(POS_X_INTER, 12, "           "); //Apaga o escrito antes da opcao selecionada
            cputsxy(POS_X_INTER, 15, "- Recordes  ");
            cputsxy(POS_X_INTER, 18, "- Creditos  ");
            cputsxy(POS_X_INTER, 21, "- Sair  ");
            textcolor(YELLOW);
            cputsxy(POS_X_INTER+2, 12, "> Carregar Jogo"); //Opcao selecionada
            return 2; break;

        case 3:
            textcolor(WHITE);
            cputsxy(POS_X_INTER, 9, "- Novo Jogo  ");
            cputsxy(POS_X_INTER, 12, "- Carregar Jogo  ");
            cputsxy(POS_X_INTER, 15, "           "); //Apaga o escrito antes da opcao selecionada
            cputsxy(POS_X_INTER, 18, "- Creditos  ");
            cputsxy(POS_X_INTER, 21, "- Sair  ");
            textcolor(YELLOW);
            cputsxy(POS_X_INTER+2, 15, "> Recordes"); //Opcao selecionada
            return 3; break;

        case 4:
            textcolor(WHITE);
            cputsxy(POS_X_INTER, 9, "- Novo Jogo  ");
            cputsxy(POS_X_INTER, 12, "- Carregar Jogo  ");
            cputsxy(POS_X_INTER, 15, "- Recordes  ");
            cputsxy(POS_X_INTER, 18, "           "); //Apaga o escrito antes da opcao selecionada
            cputsxy(POS_X_INTER, 21, "- Sair  ");
            textcolor(YELLOW);
            cputsxy(POS_X_INTER+2, 18, "> Creditos"); //Opcao selecionada
            return 4; break;
        case 5:
            textcolor(WHITE);
            cputsxy(POS_X_INTER, 9, "- Novo Jogo  ");
            cputsxy(POS_X_INTER, 12, "- Carregar Jogo  ");
            cputsxy(POS_X_INTER, 15, "- Recordes  ");
            cputsxy(POS_X_INTER, 18, "- Creditos  ");
            cputsxy(POS_X_INTER, 21, "           "); //Apaga o escrito antes da opcao selecionada
            textcolor(YELLOW);
            cputsxy(POS_X_INTER+2, 21, "> Sair"); //Opcao selecionada
            return 5; break;
    } return -1;
}

///Funcao que inicia um novo jogo
void startGame()
{
    JOGO usuario = {
    {
        {35, YINICIAL}, //coordenadas
        {9,1}, //dimensoes
        {
            {"  __lxl_",
            ">(_o_o_o)"}, // Submarino direita
            {" _lxl__ ",
            "(o_o_o_)<"} // Sumarino esquerda
        },
        1, //começa na direita
        3, //vida
        30, //oxigenio
        0, //pontos
        0, //numero de mergulhadores
        YELLOW
    }, //Declaração do jogador
    {/*mergulhadores*/},{/*submarinos Inimigos*/}
    };
    srand(time(0)); //Cria uma seed randomica
    startMergulhadores(usuario.mergulhadores);
    startSubInimigo(usuario.submarinosInim);
    clrscr(); //Limpa a tela
    gameLoop(usuario); //Comeca o jogo
}

///Carrega um jogo ja iniciado
void loadGame()
{
    JOGO game; //Buffer
    char nome[TAM_NOME_ARQUIVO]; //Para leitura do nome do arquivo
    srand(time(0)); //Cria Seed randomica

    ///Criar funcao secundaria
    do{
        printf("carregue(MAX 10) > ");
        gets(nome);
    } while(strlen(nome) > MAX_CHAR_NOME);

    strcat(nome, ".jag");

    //Se der uma mensagem de erro, volta ao menu
    if(leArq(&game, nome) == 1)
    {
        printf("\nClique para continuar");
        getch();
        clrscr();
    }
    //Senao, inicia o jogo
    else
    {
        clrscr();
        gameLoop(game);
    }
}

void records()
{
    clrscr();
    leRanking();
}

void creditos()
{
    int linha, coluna;
    char botao;
    char texto[LINHAS][CHARMAX] =
    { //As strings em branco pulam linha
        "Feito por:",
        "Andreas Emilio Panzenhagen Franz",
        "Jordi Pujol Ricarte","",
        "Professora: Mara Abel",
        "Monitor: Caua Antunes","",
        "Materia de Algoritmos e Programacao",
        "Curso de Ciencia da Computacao",
        "Universidade Federal do Rio Grande do Sul","",
        "-----------------------------------------","",
        "Codigo aberto sob licensa do MIT",
        "2019","","",
        "aperte ESPACO para sair"
    };

    for(linha=0; linha<LINHAS; linha++)
    {
        coluna=0;
        while(texto[linha][coluna] != '\0')
        {
            putchxy(20+coluna, 5+linha, texto[linha][coluna]);
            sleepcp(TEMPO);
            coluna++;
        }
    }

    do{
        botao = getch();
    } while(botao != ESP);

    clrscr();

}
