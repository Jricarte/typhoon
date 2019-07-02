/**
    Biblioteca de Estruturas e Constantes
    --------------------------------------------
    Aqui estao declaradas todas as estruturas e
    constantes usadas no jogo
**/

#ifndef GSTRUCT_H_INCLUDED
#define GSTRUCT_H_INCLUDED

//Constantes de teclas
#define EXT -32
#define ESC 27
#define DIR 77
#define ESQ 75
#define CIMA 72
#define BAIXO 80
#define ESP 32
#define ENTER 13

///GFUNC
//Orientacao
#define LDO_DIR 1
#define LDO_ESQ 2

//PONTOS
#define PTO_SUB 10

#define ATIV 1
#define DESATIV 0

#define VEL_TORP 2

#define TAM_SUBMARINO 2
#define TAM_MERG_TORP 1

#define LARG_SUBMARINO 10
#define LARG_TORP 2
#define LARG_MERG 4

//constantes de probabilidade e maximo de obstaculos
#define PROB_NASCE_MERG 0.06
#define PROBSUB 0.4
#define MAXINIM 5
#define NUM_MAX_MERG 5

//Constantes de posição
#define XINICIAL 3
#define XFINAL 78
#define YINICIAL 3
#define YFINAL 23

#define X_MIN_OBS 3
#define Y_MIN_OBS 5
#define X_MAX_OBS 70
#define Y_MAX_OBS 18

#define LOC_PONTUACAO 13
#define LOC_VIDAS 16
#define LOC_CORACAO 9
#define LOC_OXI_MERG 4

///definicoes para o jogador
#define JOG_X_INICIAL 35
#define JOG_Y_INICIAL 3
#define VIDAS 3
#define OXIGENIO 30
#define MAX_MERG_SUB 5

//Posicao de texto
#define CENTER 37
#define AVISO_GRANDE 20
#define POS_X_INTER 30 //Posicao para acoes interativas
#define TITLE_Y 5

//constantes de pontuacao
#define PONTOS_MERG 20
#define LOOP_PER_SEC 20

///CONSTANTES GFILE
//Constantes para arquivos bin
#define TAM_NOME_ARQUIVO 15 //(nome[11] - '\0')+".jag"+'\0'
#define MAX_CHAR_NOME 11
#define LINHA_SALVAR 10

//RANKING
#define LINHA_TITULO 9
#define LINHA_PRINT_RANK 11
#define TAMRANK 5
#define MENOR_RANK 4
#define MAX_CHAR_RANK 9
#define BUFFERTXT 15

///constantes credito
//constantes para creditos
#define CHARMAX 45
#define LINHAS 18
#define TEMPO 15

///Estruturas
typedef struct coordenadas
{
    int x;
    int y;
} CORD;

typedef struct tela
{
    CORD ptUm; //Superior esquerdo
    CORD ptDois; //Inferior direito
} TELA;

typedef struct dimensoes
{
    int w; //Largura (-1)
    int h; //Altura (-1)
} DIMENS;

typedef struct desenhos
{
    char desenhoDir[2][10]; //Desenho para direita
    char desenhoEsq[2][10]; //Desenho para esquerda
} DESENHO;

typedef struct submarino_jogador
{
    CORD coord;
    DIMENS dimen;
    DESENHO imagem;
    int orientacao; //1- Direita, 2- Esquerda
    int vidas;
    int oxi; //Oxigenio disponivel
    int pontos; //Pontos na rodada
    int nMerg; //Numero de mergulhadores embarcados
    int cor; //Cor do submarino
    char nome[6]; //Nome do jogador, final
} JOGADOR;

typedef struct obstaculo //Estrutura igual para os mergulhadores e Sub inimigos
{
    CORD coord;
    DIMENS dimen;
    DESENHO imagem;
    int tipo; //1- Submarino, 2- Mergulhador, 3- Torpedo
    int orientacao; //1- Direita, 2- Esquerda
    int color;
    int status;//0 - nao existe, 1 - existe
} OBSTACULO;

typedef struct jogo
{
    JOGADOR jogador;
    OBSTACULO mergulhadores[NUM_MAX_MERG];
    OBSTACULO submarinosInim[MAXINIM];
} JOGO;

#endif // GSTRUCT_H_INCLUDED
