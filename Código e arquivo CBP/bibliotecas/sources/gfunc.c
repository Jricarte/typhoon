/**
    Biblioteca de Funcoes de Jogo
    -----------------------------------------------
    Aqui sao declaradas as funcoes que serao usadas
    diretamente no jogo
**/
//Header game Functions
#include "../headers/gfunc.h"
//Bibliotecas Importadas
#include <conio2.h>
#include <time.h>
#include <string.h>
#include <windows.h>
#include "../headers/gstruct.h"
#include "../headers/gFile.h"

///Funcoes basicas
void gameStart(JOGADOR jog, OBSTACULO *submarinoInimigo, OBSTACULO *mergulhadores)
{
    fazMoldura();
    desenhaJogador(jog);
    gotoxy(XINICIAL,YFINAL+1);
    printf("O2:[||||||||||||||||||||||||||||||]");
}

void startObstaculos(OBSTACULO merg[], OBSTACULO subInim[], JOGO game)
{
    int i;

    for(i=0; i<NUM_MAX_MERG; i++)
    {
        merg[i] = game.mergulhadores[i];
    }
    for(i=0; i<MAXINIM; i++)
    {
        subInim[i] = game.submarinosInim[i];
    }
}

void gameLoop(JOGO game) ///Dividir em subfunções
{
    int flag=1, loop = 0, morte = 0;
    //Inicializa o Jogador, padrao para o jogo todo
    JOGADOR jog = game.jogador;
    OBSTACULO mergulhadores[NUM_MAX_MERG];
    OBSTACULO submarinoInimigo[MAXINIM];
    OBSTACULO torp;
    gameStart(jog, submarinoInimigo, mergulhadores);
    startObstaculos(mergulhadores, submarinoInimigo, game);

        do{

            khitDetect(&jog, mergulhadores, submarinoInimigo, &torp, &flag);

            //Independente do movimento do jogador
            atualizaInfo(&jog, mergulhadores, submarinoInimigo, &torp);

            loopSegundo(&jog, &loop);
            loop++;

            sleepcp(50);
            apagaVidas();
            desenhaVidas(jog);
            morte = detectaMorte(jog, &flag);

        }while(flag);

        ///Quando parar o looping, verifica se saiu por morrer ou por 'esc'
        if(morte)
            fimJogo(jog);

        else salvaJogo(&jog, mergulhadores, submarinoInimigo, &game);
}

void spawnMergulhador(OBSTACULO mergulhadores[])
{
    int i;
    for(i=0; i < NUM_MAX_MERG; i++)
    {
        if(mergulhadores[i].status == 0)
            inicializaMergulhadores(&mergulhadores[i]);

        if(!temObsLinha(mergulhadores[i], mergulhadores, NUM_MAX_MERG, i))
            mudaStatus(&mergulhadores[i], PROB_NASCE_MERG);
    }
}

void spawnSubInimigo(OBSTACULO submarinoInimigo[])
{
    int i;
    for(i=0; i < MAXINIM; i++)
    {
        if(submarinoInimigo[i].status == 0)
            inicializaSubInimigo(&submarinoInimigo[i]);
        if(!temObsLinha(submarinoInimigo[i], submarinoInimigo, MAXINIM, i))
            mudaStatus(&submarinoInimigo[i], PROBSUB);
    }
}

void khitDetect(JOGADOR *jog, OBSTACULO merg[], OBSTACULO subInim[], OBSTACULO *torp, int *flag)
{
    if(kbhit()) ///apenas se o usuario mexer o submarino
    {
        arrumaMar(*jog); //Arruma o teto
        moveJogador(jog, flag, torp);

        spawnMergulhador(merg);
        spawnSubInimigo(subInim);
    }
}

void atualizaInfo(JOGADOR *jog, OBSTACULO merg[], OBSTACULO subInim[], OBSTACULO *torp)
{
    foraAgua(jog);
    gotoxy(XFINAL-LOC_PONTUACAO,YINICIAL-1);
    printf("%6d pontos", jog->pontos);

    loopTorpedo(torp, subInim, jog);
    funcoesLoopMerg(jog, merg);
    subInimigoFinal(jog, subInim);
}

void loopSegundo(JOGADOR *jog, int *loop)
{
    if(*loop == LOOP_PER_SEC)
            {
                *loop = 0;
                atualizaJog(jog);
                desenhaO2(*jog);
                apagaO2();
                desenhaO2(*jog);
            }
}

///-----funcoes esteticas-------------------------------------------------///

void fazMoldura()
{
    TELA parede = {{XINICIAL,YINICIAL}, {XFINAL, YFINAL}};
    int i;
    //imprime linhas
    for(i=parede.ptUm.x; i<parede.ptDois.x; i++)
    {
        if(i%2)
            putchxy(i, YINICIAL+1, ' ');
        else
            putchxy(i, YINICIAL+1, '~');
        putchxy(i, YFINAL, '-');
    }
    for(i=parede.ptUm.y; i<parede.ptDois.y; i++)
    {
        putchxy(XINICIAL-1, i, '|');
        putchxy(XFINAL, i, '|');
    }
}

void arrumaMar(JOGADOR j) //Arruma o teto do cenario quando o sub passar
{
    int i;
    TELA parede = {{XINICIAL,YINICIAL}, {XFINAL, YFINAL}};
    if (j.coord.y < YINICIAL + TAM_SUBMARINO+1) // +1 para que nao redesenhe o mar com o submarino abaixo da linha
    {
        for(i=parede.ptUm.x; i<parede.ptDois.x; i++)
        {
            if(i%2)
                putchxy(i, YINICIAL+1, ' ');
            else
                putchxy(i, YINICIAL+1, '~');
        }
    }
}

void desenhaVidas(JOGADOR j)
{
    int i, posCoracao;

    if(j.vidas>0)
    for(i=0, posCoracao=0; i<j.vidas; i++, posCoracao+=3)
    {
        gotoxy(XFINAL-LOC_CORACAO+posCoracao,YFINAL+1);
        printf("<3");
    }
}

void apagaVidas()
{
    gotoxy(XFINAL-LOC_VIDAS, YFINAL+1);
    printf("Vidas:         ");
}

void desenhaO2(JOGADOR j)
{
    int i;

    for(i=0; i<j.oxi; i++)
    {
        gotoxy(XINICIAL+LOC_OXI_MERG+i,YFINAL+1);
        printf("|");
    }
}

void apagaO2()
{
    gotoxy(XINICIAL,YFINAL+1);
    printf("O2:[                              ]");
}

void desenhaNmerg(JOGADOR j) //desenha a quantidade de mergulhadores que o jog pegou na tela
{
    int i, p = 0;

    for(i=0; i<j.nMerg; i++)
    {
        gotoxy(XINICIAL+LOC_OXI_MERG+p,YINICIAL-1);
        printf("\\O/");
        p = p + LOC_OXI_MERG;
    }
}

void apagaNmerg()
{
    gotoxy(XINICIAL+LOC_OXI_MERG,YINICIAL-1);
    printf("                   ");
}

void fimJogo(JOGADOR j)
{
    int menorRaking;
    fflush(stdin);
    clrscr();
    fazMoldura();
    textcolor(RED);
    cputsxy(CENTER, TITLE_Y, "VOCE MORREU"); //
    cputsxy(AVISO_GRANDE, TITLE_Y+2, "clique em qualquer tecla para continuar");
    menorRaking = leRanking();
    if(menorRaking < j.pontos)
    {
        abreRanking(j);
    }
    clrscr();
    textcolor(LIGHTGRAY);
}

///----funcoes de desenho de jogador--------------------------------------///

void desenhaJogador(JOGADOR j) //Desenha o jogador para direita
{
    int i;
    textcolor(j.cor);
    if(j.orientacao == 1)
    {
        for(i=0; i < j.dimen.h+1; i++)
        {
            gotoxy(j.coord.x, j.coord.y + i);
            cputsxy(j.coord.x, j.coord.y + i, j.imagem.desenhoDir[i]);
        }
    }
    else
    {
       for(i=0; i < j.dimen.h+1; i++)
        {
            gotoxy(j.coord.x, j.coord.y + i);
            cputsxy(j.coord.x, j.coord.y + i,j.imagem.desenhoEsq[i]);
        }
    }
    textcolor(LIGHTGRAY);
}

void apagaJogador(JOGADOR j)
{
    int i, k;
    for(i=j.coord.y; i < j.coord.y + j.dimen.h+1; i++)
    {
        for(k=j.coord.x; k < j.coord.x + j.dimen.w+1; k++)
            putchxy(k, i, ' ');
    }
}

///----funcoes de movimentacao do jogador---------------------------------///
void moveJogador(JOGADOR *j,int *flag, OBSTACULO *torp)
{
    char c;
    c = getch();
    if(c == EXT){
        c = getch();
        apagaJogador(*j);
        switch(c) {
            case DIR:
                if(j->coord.x + j->dimen.w < XFINAL-1)
                {
                    (j->coord.x)++;
                    j->orientacao = LDO_DIR;
                } break;
            case ESQ:
                if(j->coord.x > XINICIAL)
                {
                    (j->coord.x)--;
                    j->orientacao = LDO_ESQ;
                } break;
            case BAIXO:
                if(j->coord.y + j->dimen.h < YFINAL-1)
                {
                    (j->coord.y)++;
                } break;
            case CIMA:
                if(j->coord.y > YINICIAL)
                {
                    (j->coord.y)--;
                } break;
        }
        desenhaJogador(*j);
    }
    else if(c == ESP){
        apagaTorpedo(*torp);
        *torp = iniciaTorpedo(*j);
    }
    else if(c == ESC) {
        *flag = 0;
    }
}

///----funcoes de acoes --------------------------------------------------///

int detectaColisao(JOGADOR j, OBSTACULO obs)
{
    //comparacoes em relacao ao submarino
    if(j.coord.x + j.dimen.w <= obs.coord.x) //Verifica a direita
        return 0;
    if(j.coord.x > obs.coord.x + obs.dimen.w) //verifica a esquerda
        return 0;
    if(j.coord.y + j.dimen.h < obs.coord.y) // verifica embaixo
        return 0;
    if(j.coord.y > obs.coord.y + obs.dimen.h) //verifica em cima
        return 0;
    return 1; //Se nenhum dos if's for verdadeiro, houve colisao
}

void foraAgua(JOGADOR *j) //Zera o numero de mergulhadores, carrega oxigenio e conta os pontos.
{
    if(j->coord.y < YINICIAL+1)
    {
        apagaNmerg();
        j->pontos += j->nMerg*PONTOS_MERG;
        j->nMerg = 0;
        j->oxi = 30;
        gotoxy(XINICIAL,YFINAL+1);
        printf("O2:[||||||||||||||||||||||||||||||]");
    }
}

void atualizaJog(JOGADOR *j)
{
    if(j->coord.y > YINICIAL)
        j->pontos++;
    j->oxi--;
}

int colisaoObstaculos(OBSTACULO obs1, OBSTACULO obs2)
{

    if(obs1.status == 1 && obs2.status == 1)
    {
        //comparacoes em relacao ao submarino
        if(obs1.coord.x + obs1.dimen.w <= obs2.coord.x) //Verifica a direita
            return 0;
        if(obs1.coord.x > obs2.coord.x + obs2.dimen.w) //verifica a esquerda
            return 0;
        if(obs1.coord.y + obs1.dimen.h < obs2.coord.y) // verifica embaixo
            return 0;
        if(obs1.coord.y > obs2.coord.y + obs2.dimen.h) //verifica em cima
            return 0;
        else
            return 1;
    }
    return 0;
}

int temObsLinha(OBSTACULO indv, OBSTACULO vetorobs[], int tamVetor, int ind)
{
    int i, posVetor, posIndv = indv.coord.y;
    for(i=0; i<tamVetor; i++)
    {
        posVetor = vetorobs[i].coord.y;
            if(posIndv == posVetor || posIndv == posVetor+1 || posIndv == posVetor-1)
                if(ind != i)
                    return 1;
    }
    return 0;
}

///----funcoes de torpedos------------------------------------------------///
OBSTACULO iniciaTorpedo(JOGADOR j)
{
    OBSTACULO torp  =
    {
        ///Coordenadas X e Y
        {
            j.coord.x + j.dimen.w, //Posicao X
            j.coord.y + j.dimen.h //Posicao Y
        },
        ///Largura e Altura
        {
            LARG_TORP-1, //Largura -1
            TAM_MERG_TORP-1  //Altura -1
        },
        ///Desenhos
        {
            {"=>",""}, //Desenho Direita
            {"<=",""}  //Desenho Esquerda
        },
        ///Tipo, orientacao, cor e status
        3, //Tipo 3 - Torpedo
        j.orientacao, //Mesmo lado que o submarino
        WHITE, //Cor branca pro torpedo
        ATIV //Status Ativo
    };

    if(j.orientacao==LDO_ESQ)
    {
        torp.coord.x = j.coord.x-2;
    }

    return torp;
}

void desenhaTorpedo(OBSTACULO torp)
{
    if(torp.status == ATIV)
    {
        if(torp.orientacao == LDO_DIR)
            cputsxy(torp.coord.x, torp.coord.y, torp.imagem.desenhoDir[0]);
        else if(torp.orientacao == LDO_ESQ)
            cputsxy(torp.coord.x, torp.coord.y, torp.imagem.desenhoEsq[0]);
    }
}

void apagaTorpedo(OBSTACULO torp)
{
    if(torp.status == ATIV)
    {
        if(torp.orientacao == LDO_DIR)
            cputsxy(torp.coord.x, torp.coord.y, "  ");
        else if(torp.orientacao == LDO_ESQ)
            cputsxy(torp.coord.x, torp.coord.y, "  ");
    }
}

void moveTorpedo(OBSTACULO *torp)
{
    if(torp->status == ATIV)
    {
        if(torp->orientacao == LDO_DIR)
            torp->coord.x += VEL_TORP;
        else if(torp->orientacao == LDO_ESQ)
            torp->coord.x -= VEL_TORP;
    }
}

void bateTorpedoParede(OBSTACULO *torp)
{
    if(torp->status == ATIV)
    {
        if(torp->coord.x <= XINICIAL+1)
        {
            torp->status = DESATIV;
        }
        else if (torp->coord.x + torp->dimen.w >= XFINAL-2)
        {
            torp->status = DESATIV;
        }
    }
}

void bateTorpedoSubInim(OBSTACULO *torp, OBSTACULO *sub, JOGADOR *j)
{
    if(colisaoObstaculos(*torp, *sub))
    {
        apagaTorpedo(*torp);
        torp->status = 0;
        apagaSubmarino(*sub);
        sub->coord.y = 0;
        sub->status = 0;
        j->pontos += PTO_SUB;
    }
}

void loopTorpedo(OBSTACULO *torp, OBSTACULO *subInim, JOGADOR *j)
{
    int i;
    apagaTorpedo(*torp);
    moveTorpedo(torp);
    bateTorpedoParede(torp);
    desenhaTorpedo(*torp);
    for(i=0; i<MAXINIM; i++)
    {
        bateTorpedoSubInim(torp, &subInim[i], j);
    }
}

///----funcoes de inicializacao dos mergulhadores-------------------------///

void inicializaMergulhadores(OBSTACULO *m) //Verifica-se previamente se o obs eh um mergulhador
{
    double r;
    m->coord.y = Y_MIN_OBS + (rand()% Y_MAX_OBS); ///certo
    m->coord.x = X_MIN_OBS + (rand()% X_MAX_OBS); ///certo
    m->dimen.h = 0;
    m->dimen.w = LARG_MERG-1;
    m->tipo = 2;
    strcpy(m->imagem.desenhoDir[0], ">-/o\0");
    strcpy(m->imagem.desenhoEsq[0], "o\\-<\0");


    r = rand()/((double)RAND_MAX);
    if( r <= 0.5)
        m->orientacao = LDO_DIR;
    else
        m->orientacao = LDO_ESQ;
}

void mudaStatus(OBSTACULO *obs, double prob) //muda o status dos mergulhadores e sub inimigos
{
    double r;
    if(obs->status == DESATIV)
    {

        r = rand()/((double)RAND_MAX);
        if( r <= prob)
            obs->status = ATIV;
        else
            obs->status = DESATIV;
    }
}

void desenhaMergulhador(OBSTACULO obs)
{
    if(obs.status)
    {
       if(obs.orientacao == LDO_DIR)
            cputsxy(obs.coord.x, obs.coord.y, obs.imagem.desenhoDir[0]);
        else
            cputsxy(obs.coord.x, obs.coord.y, obs.imagem.desenhoEsq[0]);
    }
}

void apagaMergulhador(OBSTACULO m)
{
    if(m.status == ATIV)
        cputsxy(m.coord.x, m.coord.y, "    ");
}

void startMergulhadores(OBSTACULO *obs) //Verifica-se previamente se o obs eh um mergulhador
{
    int i;
    for(i=0;i<NUM_MAX_MERG;i++)
    {
        inicializaMergulhadores(&obs[i]);

        if(!temObsLinha(obs[i], obs, NUM_MAX_MERG, i))
            mudaStatus(&obs[i], PROB_NASCE_MERG);

        desenhaMergulhador(obs[i]);
    }
}

void atualizaStatusMergulhador(JOGADOR *j, OBSTACULO *obs) //pega os mergulhadores
{
    if(detectaColisao(*j, *obs))
    {

        if(obs->status == ATIV && j->nMerg < MAX_MERG_SUB){
            obs->status = DESATIV;
            cputsxy(obs->coord.x, obs->coord.y, "    ");
            j->nMerg++;
            desenhaNmerg(*j);
        }
    }
}

void moveMergulhador(OBSTACULO *m)
{
    if(m->orientacao == LDO_DIR) //Se o mergulhador for para direita
        m->coord.x++;
    else if(m->orientacao == LDO_ESQ) //Se o mergulhador for para esquerda
        m->coord.x--;
}

void bateMergulhadorParede(OBSTACULO *obs) //muda a direcao do mergulhador quando bate na parede
{
    if(obs->coord.x + obs->dimen.w == XFINAL-1)
        obs->orientacao = LDO_ESQ;
    else if(obs->coord.x == XINICIAL)
        obs->orientacao = LDO_DIR;
}

void funcoesLoopMerg(JOGADOR *jog,OBSTACULO mergulhadores[]) //Faz todas as funcoes de mergulhadores
{
    int i;
    for(i=0;i<NUM_MAX_MERG;i++) //Atualiza o status dos mergulhadores
    {
        atualizaStatusMergulhador(jog, &mergulhadores[i]);
        apagaMergulhador(mergulhadores[i]);
        bateMergulhadorParede(&mergulhadores[i]);
        moveMergulhador(&mergulhadores[i]);
        desenhaMergulhador(mergulhadores[i]);
    }
}

///--------------------funcões-dos-submarinos-inimigos---------------------------///

void inicializaSubInimigo(OBSTACULO *subI) //Verifica-se previamente se o obs eh um mergulhador
{
    double r;
    subI->coord.y = (Y_MIN_OBS) + (rand()% (Y_MAX_OBS-2)); ///certo
    subI->dimen.h = TAM_SUBMARINO-1;
    subI->dimen.w = LARG_SUBMARINO-1;
    subI->tipo = 1;
    strcpy(subI->imagem.desenhoDir[0], "  __lxl_\0");
    strcpy(subI->imagem.desenhoDir[1], ">{_0_0_0}\0");
    strcpy(subI->imagem.desenhoEsq[0], " _lxl__ \0");
    strcpy(subI->imagem.desenhoEsq[1], "{0_0_0_}<\0");
    subI->color = RED;

    r = rand()/((double)RAND_MAX);
    if( r <= 0.5)
    {
        subI->orientacao = LDO_DIR;
        subI->coord.x = X_MIN_OBS; ///certo
    }
    else
    {
        subI->orientacao = LDO_ESQ;
        subI->coord.x = X_MAX_OBS-1; ///certo
    }
}

void desenhaSubInimigo(OBSTACULO obs) ///ok
{
    textcolor(obs.color);

    if(obs.status)
    {
        if(obs.orientacao == LDO_DIR)
        {
            cputsxy(obs.coord.x, obs.coord.y, obs.imagem.desenhoDir[0]);
            cputsxy(obs.coord.x, obs.coord.y+1, obs.imagem.desenhoDir[1]);
        }
        else
        {
            cputsxy(obs.coord.x, obs.coord.y, obs.imagem.desenhoEsq[0]);
            cputsxy(obs.coord.x, obs.coord.y+1, obs.imagem.desenhoEsq[1]);
        }
    }

    textcolor(LIGHTGRAY);
}
void apagaSubmarino(OBSTACULO obs) //ok
{
    if(obs.status)
    {
        cputsxy(obs.coord.x, obs.coord.y, "         ");
        cputsxy(obs.coord.x, obs.coord.y+1, "         ");
    }
}



void startSubInimigo(OBSTACULO obs[]) //Verifica-se previamente se o obs eh um mergulhador
{
    int i;

    for(i=0;i<MAXINIM;i++)
    {
        inicializaSubInimigo(&obs[i]);
        if(!temObsLinha(obs[i], obs, MAXINIM, i))
            mudaStatus(&obs[i], PROBSUB);
        desenhaSubInimigo(obs[i]);
    }
}

void bateInimigo(JOGADOR *j, OBSTACULO *obs)
{
    if(detectaColisao(*j, *obs))
    {
        if(obs->status == ATIV)
        {
            j->nMerg = 0;
            apagaJogador(*j);
            j->coord.x = JOG_X_INICIAL;
            j->coord.y = JOG_Y_INICIAL;
            desenhaJogador(*j);
            j->vidas--;
            desenhaVidas(*j);
            printf("\a");
        }
    }

}

void bateParedeSubmarino(OBSTACULO *obs)
{
    if(obs->coord.x + obs->dimen.w == XFINAL-1)
        obs->orientacao = LDO_ESQ;
    else if(obs->coord.x == XINICIAL)
        obs->orientacao = LDO_DIR;

}

void moveSubInimigo(OBSTACULO *obs) //ok
{
    if(obs->status)
    {
        if(obs->orientacao == LDO_DIR) //Se o mergulhador for para direita
            obs->coord.x++;
        else if(obs->orientacao == LDO_ESQ) //Se o mergulhador for para esquerda
            obs->coord.x--;
    }
}

void subInimigoFinal(JOGADOR *jog,OBSTACULO submarinos[])
{
    int i;

    for(i=0; i<MAXINIM; i++)
    {
        //mudaStatus(&submarinos[i], PROBSUB);
        bateInimigo(jog, &submarinos[i]);
        apagaSubmarino(submarinos[i]);
        bateParedeSubmarino(&submarinos[i]);
        moveSubInimigo(&submarinos[i]);
        desenhaSubInimigo(submarinos[i]);
    }
}


void sleepcp(int milliseconds) // Cross-platform sleep function
{
    clock_t time_end;
    time_end = clock() + milliseconds * CLOCKS_PER_SEC/1000;
    while (clock() < time_end)
    {
    }
}

int detectaMorte(JOGADOR j, int *flag)
{
    if(j.oxi == 0 || j.vidas == 0)
    {
        *flag = 0;
        return 1;
    }
        return 0;
}
