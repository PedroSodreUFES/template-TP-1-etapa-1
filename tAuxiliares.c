#include "tMapa.h"
#include "tMovimento.h"
#include "tPacman.h"
#include "tPosicao.h"
#include "tTunel.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tAuxiliares.h"


//MOVE UM FANTASMA
void MoveFantasma(tMapa* mapa, tFantasma* fantasma, int n, int h, int v, COMANDO comando, tPacman* pacman)
{
    //COMIDA NA POSICAO QUE SE DESEJA MOVER
    if(mapa->grid[fantasma[n].linha + v][fantasma[n].coluna + h]=='*')
    {
        if(fantasma[n].comida==0&&fantasma[n].tunel==0)
        {
            mapa->grid[fantasma[n].linha][fantasma[n].coluna]=' ';
        }
        else if(fantasma[n].comida==1)
        {
            mapa->grid[fantasma[n].linha][fantasma[n].coluna]='*';
        }
        else if(fantasma[n].tunel==1)
        {
            mapa->grid[fantasma[n].linha][fantasma[n].coluna]='@';    
        }
        fantasma[n].comida=1;
        fantasma[n].tunel=0;
        fantasma[n].coluna = fantasma[n].coluna + h;
        fantasma[n].linha = fantasma[n].linha + v;
        mapa->grid[fantasma[n].linha][fantasma[n].coluna]=fantasma[n].nome;
    }

    //VAZIO NA POSICAO QUE SE DESEJA MOVER
    else if(mapa->grid[fantasma[n].linha + v][fantasma[n].coluna + h]==' ')
    {
        if(fantasma[n].comida==0&&fantasma[n].tunel==0)
        {
            mapa->grid[fantasma[n].linha][fantasma[n].coluna]=' ';
        }
        else if(fantasma[n].comida==1)
        {
            mapa->grid[fantasma[n].linha][fantasma[n].coluna]='*';
        }
        else if(fantasma[n].tunel==1)
        {
            mapa->grid[fantasma[n].linha][fantasma[n].coluna]='@';    
        }
        fantasma[n].comida=0;
        fantasma[n].tunel=0;
        fantasma[n].coluna=fantasma[n].coluna + h;
        fantasma[n].linha=fantasma[n].linha + v;
        mapa->grid[fantasma[n].linha][fantasma[n].coluna]=fantasma[n].nome;
    }

    //TUNEL NA POSICAO QUE SE DESEJA MOVER
    else if(mapa->grid[fantasma[n].linha + v][fantasma[n].coluna + h]=='@')
    {
        if(fantasma[n].comida==0&&fantasma[n].tunel==0)
        {
            mapa->grid[fantasma[n].linha][fantasma[n].coluna]=' ';
        }
        else if(fantasma[n].comida==1)
        {
            mapa->grid[fantasma[n].linha][fantasma[n].coluna]='*';
        }
        else if(fantasma[n].tunel==1)
        {
            mapa->grid[fantasma[n].linha][fantasma[n].coluna]='@';    
        }
        fantasma[n].tunel=1;
        fantasma[n].comida=0;
        fantasma[n].coluna = fantasma[n].coluna + h;
        fantasma[n].linha = fantasma[n].linha + v;
        mapa->grid[fantasma[n].linha][fantasma[n].coluna]=fantasma[n].nome;
    }

    //PACMAN NA POSICAO QUE SE DESEJA MOVER
    else if(mapa->grid[fantasma[n].linha + v][fantasma[n].coluna + h]=='>')
    {
        if(fantasma[n].comida==0&&fantasma[n].tunel==0)
        {
            mapa->grid[fantasma[n].linha][fantasma[n].coluna]=' ';
        }
        else if(fantasma[n].comida==1)
        {
            mapa->grid[fantasma[n].linha][fantasma[n].coluna]='*';
        }
        else if(fantasma[n].tunel==1)
        {
            mapa->grid[fantasma[n].linha][fantasma[n].coluna]='@';    
        }
        fantasma[n].tunel=0;
        fantasma[n].comida=0;
        fantasma[n].coluna = fantasma[n].coluna + h;
        fantasma[n].linha = fantasma[n].linha + v;
        mapa->grid[fantasma[n].linha][fantasma[n].coluna]=fantasma[n].nome;
        //CHECAR COLISAO FRONTAL
        if(v==1&&comando==MOV_CIMA)//FANTASMA PRA BAIXO, PACMAN PRA CIMA
        {
            MataPacman(pacman);
        }
        else if(v==-1&&comando==MOV_BAIXO)//FANTASMA PRA CIMA, PACMAN PRA BAIXO
        {
            MataPacman(pacman);
        }
        else if(h==1&&comando==MOV_ESQUERDA)//FANTASMA PRA DIREITA, PACMAN PRA ESQUERDA
        {
            MataPacman(pacman);
        }
        else if(h==-1&&comando==MOV_DIREITA)//FANTASMA PRA ESQUERDA, PACMAN PRA DIREITA
        {
            MataPacman(pacman);
        }
    }
    else
    {
        if(fantasma[n].comida==0&&fantasma[n].tunel==0)
        {
            mapa->grid[fantasma[n].linha][fantasma[n].coluna]=' ';
        }
        else if(fantasma[n].comida==1)
        {
            mapa->grid[fantasma[n].linha][fantasma[n].coluna]='*';
        }
        else if(fantasma[n].tunel==1)
        {
            mapa->grid[fantasma[n].linha][fantasma[n].coluna]='@';    
        }
        fantasma[n].tunel=0;
        fantasma[n].comida=0;
        fantasma[n].coluna = fantasma[n].coluna + h;
        fantasma[n].linha = fantasma[n].linha + v;
        mapa->grid[fantasma[n].linha][fantasma[n].coluna]=fantasma[n].nome;
    }

    //PAREDE: DIZ SE VAI INVERTER A DIRECAO OU NAO
    if(mapa->grid[fantasma[n].linha + v][fantasma[n].coluna + h]=='#')
    {
        if(fantasma[n].invertido==0)
        {
            fantasma[n].invertido=1;
        }
        else if(fantasma[n].invertido==1)
        {
            fantasma[n].invertido=0;
        }
    }
}


//VAI MOVER FANTASMA POR FANTASMA E GERAR O MAPA
void MoveFantasmas(tMapa* mapa, tFantasma* fantasmas, int nfantasmas, COMANDO comando, tPacman* pacman)
{
    int i=0;
    for(i=0;i<nfantasmas;i++)
    {
        if(fantasmas[i].nome=='B'&&fantasmas[i].invertido==0)
        {
            MoveFantasma(mapa, fantasmas, i, -1, 0, comando, pacman);
        }
        else if(fantasmas[i].nome=='B'&&fantasmas[i].invertido==1) //h //v
        {
            MoveFantasma(mapa, fantasmas, i, 1, 0, comando, pacman);
        }
        else if(fantasmas[i].nome=='C'&&fantasmas[i].invertido==0)
        {
            MoveFantasma(mapa, fantasmas, i, 1, 0, comando, pacman);
        }
        else if(fantasmas[i].nome=='C'&&fantasmas[i].invertido==1)
        {
            MoveFantasma(mapa, fantasmas, i, -1, 0, comando, pacman);
        }
        else if(fantasmas[i].nome=='P'&&fantasmas[i].invertido==0)
        {
            MoveFantasma(mapa, fantasmas, i, 0, -1, comando, pacman);
        }
        else if(fantasmas[i].nome=='P'&&fantasmas[i].invertido==1)
        {
            MoveFantasma(mapa, fantasmas, i, 0, 1, comando, pacman);
        }
        else if(fantasmas[i].nome=='I'&&fantasmas[i].invertido==0)
        {
            MoveFantasma(mapa, fantasmas, i, 0, 1, comando, pacman);
        }
        else if(fantasmas[i].nome=='I'&&fantasmas[i].invertido==1)
        {
            MoveFantasma(mapa, fantasmas, i, 0, -1, comando, pacman);
        }
    }
}

//inicializa fantasmasas
tFantasma* InicializaFantasmas(tMapa* mapa, int nfantasmas)
{
    int i, j, z=0;
    tFantasma* fantasma = (tFantasma*)malloc(nfantasmas*sizeof(tFantasma));
    for(i=0 ; i<ObtemNumeroLinhasMapa(mapa) ; i++)
    {
        for(j=0 ; j<ObtemNumeroColunasMapa(mapa) ; j++)
        {
            if(mapa->grid[i][j]=='P'||mapa->grid[i][j]=='I'||mapa->grid[i][j]=='C'||mapa->grid[i][j]=='B')
            {
                fantasma[z].coluna=j;
                fantasma[z].comida=0;
                fantasma[z].linha=i;
                fantasma[z].nome=mapa->grid[i][j];
                fantasma[z].tunel=0;
                fantasma[z].invertido=VeSeAlgumFantasmaTaInvertido(mapa, z, fantasma);
                z++;
            }
        }
    }
    return fantasma;
}

//conta fantasmas inicialmente
int ContaFantasma(tMapa* mapa)
{
    int i, j, cont=0;
    for(i=0 ; i<mapa->nLinhas ; i++)
    {
        for(j=0 ; j<mapa->nColunas ; j++)
        {
            if(mapa->grid[i][j] =='P' || mapa->grid[i][j] == 'I' || mapa->grid[i][j]=='C'|| mapa->grid[i][j] == 'B')
            {
                cont++;
            }
        }
    }
    return cont;
}

//Ve se algum fantasma comeca invertido
int VeSeAlgumFantasmaTaInvertido(tMapa* mapa, int i, tFantasma* fantasma)
{   
    if(fantasma[i].nome=='P')
    {
        if(mapa->grid[fantasma[i].linha-1][fantasma[i].coluna ]=='#')
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    else if(fantasma[i].nome=='C')
    {
        if(mapa->grid[fantasma[i].linha][fantasma[i].coluna+1]=='#')
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    else if(fantasma[i].nome=='B')
    {
        if(mapa->grid[fantasma[i].linha][fantasma[i].coluna-1]=='#')
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    else if(fantasma[i].nome=='I')
    {
        if(mapa->grid[fantasma[i].linha+1][fantasma[i].coluna]=='#')
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
}

//DesalocaFantasmas
void DesalocaFantasmas(tFantasma *fantasma)
{
    free(fantasma);
}

//FAZ INICIALIZACAO.TXT
void inicializacaotxt(tMapa* mapa)
{
    int i, j, linha, coluna;
    FILE *inicalizacao;
    inicalizacao = fopen("inicializacao.txt", "w");
    for(i=0 ; i<ObtemNumeroLinhasMapa(mapa) ; i++)
    {
        fprintf(inicalizacao, "%s\n", mapa->grid[i]);
    }
    for(i=0 ; i<ObtemNumeroLinhasMapa(mapa); i++)
    {
        for(j=0 ; j<ObtemNumeroColunasMapa(mapa) ; j++)
        {
            if(mapa->grid[i][j]=='>')
            {
                linha=i+1;
                coluna=j+1;
            }
        }
    }
    fprintf(inicalizacao, "Pac-Man comecara o jogo na linha %d e coluna %d\n", linha , coluna);
    fclose(inicalizacao);
}

//O JOGO EM SI
void RealizaJogo(tPacman *pacman, tMapa *mapa, tFantasma *fantasmas, int nfantasmas)
{
    char tecla, tinhafantasmaantes;
    int nfrutas = mapa->nFrutasAtual;
    tPosicao *posicaocheck=ClonaPosicao(ObtemPosicaoPacman(pacman));
    COMANDO comando;
    while(nfrutas!=ObtemPontuacaoAtualPacman(pacman) && EstaVivoPacman(pacman) && ObtemNumeroAtualMovimentosPacman(pacman)<ObtemNumeroMaximoMovimentosMapa(mapa))
    {
        posicaocheck->linha=ObtemLinhaPosicao(ObtemPosicaoPacman(pacman));
        posicaocheck->coluna=ObtemColunaPosicao(ObtemPosicaoPacman(pacman));
        tinhafantasmaantes=1;
        scanf("%*[^asdw]");
        scanf("%c", &tecla);
        if(tecla=='w')
        {
            pacman->nMovimentosCima++;
            comando=MOV_CIMA;
            posicaocheck->linha--;
        }
        else if(tecla=='a')
        {
            pacman->nMovimentosEsquerda++;
            comando=MOV_ESQUERDA;
            posicaocheck->coluna--;
        }
        else if(tecla=='d')
        {
            pacman->nMovimentosDireita++;
            comando=MOV_DIREITA;
            posicaocheck->coluna++;
        }
        else if(tecla=='s')
        {
            pacman->nMovimentosBaixo++;
            comando=MOV_BAIXO;
            posicaocheck->linha++;
        }


        //tem parede na posicao
        if(EncontrouParedeMapa(mapa, posicaocheck))
        {
            pacman->nMovimentosSignificativos++;
            InsereNovoMovimentoSignificativoPacman(pacman, comando, "p");
            VoltaPosicao(posicaocheck, tecla);
        }

        //tem comida na posicao
        else if(EncontrouComidaMapa(mapa, posicaocheck))
        {
            pacman->nMovimentosSignificativos++;
            SomaComida(pacman, comando);
            InsereNovoMovimentoSignificativoPacman(pacman, comando, "c");
            tinhafantasmaantes=0;
        }

        //MoveTodosOsFantasmas
        MoveFantasmas(mapa, fantasmas, nfantasmas, comando, pacman);

        //apos o fantasma sair, ele achou uma comida
        if(EncontrouComidaMapa(mapa, posicaocheck) && tinhafantasmaantes==1)
        {
            pacman->nMovimentosSignificativos++;
            SomaComida(pacman, comando);
            InsereNovoMovimentoSignificativoPacman(pacman, comando, "c");
        }

        //Move o Pacman
        MovePacman(pacman, mapa, comando);

        //pacman prensado na parede
        if(pacmanprensado(pacman, fantasmas, nfantasmas))
        {
            MataPacman(pacman);
        }

        //pacman morreu
        if(!EstaVivoPacman(pacman))
        {
            pacman->nMovimentosSignificativos++;
            InsereNovoMovimentoSignificativoPacman(pacman, comando, "m");
            if(mapa->grid[ObtemLinhaPosicao(ObtemPosicaoPacman(pacman))][ObtemColunaPosicao(ObtemPosicaoPacman(pacman))]=='>')
            {
                mapa->grid[ObtemLinhaPosicao(ObtemPosicaoPacman(pacman))][ObtemColunaPosicao(ObtemPosicaoPacman(pacman))]=' ';
            }
        }
        AtualizaTrilhaPacman(pacman);
        PrintaMapa(mapa, tecla, pacman, fantasmas, nfantasmas);
    }
    if(ObtemPontuacaoAtualPacman(pacman)==nfrutas)
    {
        printf("Voce venceu!\n");
    }
    else
    {
        printf("Game over!\n");
    }
    printf("Pontuacao final: %d\n", ObtemPontuacaoAtualPacman(pacman));
    free(posicaocheck);
}

//VE SE O PACMAN FOI PRENSADO POR UM FANTASMA NA PAREDE
int pacmanprensado(tPacman* pacman,tFantasma* fantasma, int nfantasmas)
{
    int i;
    for(i=0 ; i<nfantasmas ; i++)
    {
        if(fantasma[i].coluna == ObtemColunaPosicao(ObtemPosicaoPacman(pacman)) && fantasma[i].linha == ObtemLinhaPosicao(ObtemPosicaoPacman(pacman)))
        {
            return 1;
        }
    }
    return 0;
}

//PRINTA O MAPA
void PrintaMapa(tMapa *mapa, char tecla, tPacman *pacman, tFantasma *fantasma, int nfantasmas)
{
    int i, j;
    ColocaFantasmaNoGrid(mapa, fantasma, nfantasmas);
    printf("Estado do jogo apos o movimento '%c':\n", tecla);
    for(i=0 ; i<ObtemNumeroLinhasMapa(mapa) ; i++)
    {
        for(j=0 ; j<ObtemNumeroColunasMapa(mapa) ; j++)
        {
            printf("%c", mapa->grid[i][j]);
        }
        printf("\n");
    }
    printf("Pontuacao: %d\n\n", ObtemPontuacaoAtualPacman(pacman));
}

//FAZ RESUMO.TXT
void resumotxt(tPacman *pacman)
{
    int i;
    FILE *resumo;
    char letra;
    resumo = fopen("resumo.txt", "w");
    tMovimento **m = ClonaHistoricoDeMovimentosSignificativosPacman(pacman);
    for(i=0 ; i<ObtemNumeroMovimentosSignificativosPacman(pacman) ; i++)
    {
        fprintf(resumo,"Movimento %d ", ObtemNumeroMovimento(m[i]));
        if(ObtemComandoMovimento(m[i])==MOV_BAIXO)
        {
            letra='s';
        }
        else if(ObtemComandoMovimento(m[i])==MOV_CIMA)
        {
            letra='w';
        }
        else if(ObtemComandoMovimento(m[i])==MOV_DIREITA)
        {
            letra='d';
        }
        else if(ObtemComandoMovimento(m[i])==MOV_ESQUERDA)
        {
            letra='a';
        }
        fprintf(resumo,"(%c) ", letra);
        if(strcmp(ObtemAcaoMovimento(m[i]), "m")==0)
        {
            fprintf(resumo,"fim de jogo por encostar em um fantasma\n");
        }
        else if(strcmp(ObtemAcaoMovimento(m[i]), "p")==0)
        {
            fprintf(resumo,"colidiu com a parede\n");
        }
        else if(strcmp(ObtemAcaoMovimento(m[i]), "c")==0)
        {
            fprintf(resumo,"pegou comida\n");
        }
    }
    for(i=0 ; i<ObtemNumeroMovimentosSignificativosPacman(pacman); i++)
    {
        if(m[i]!=NULL)
        {
            free(m[i]);
        }
    }
    if(m!=NULL)
    {
        free(m);
    }
    fclose(resumo);
}

//FAZ ESTATISTICAS.TXT
void estatisticastxt(tPacman *pacman)
{
    FILE *estatisticas;
    estatisticas = fopen("estatisticas.txt", "w");
    fprintf(estatisticas, "Numero de movimentos: %d\n", ObtemNumeroAtualMovimentosPacman(pacman));
    fprintf(estatisticas, "Numero de movimentos sem pontuar: %d\n", ObtemNumeroMovimentosSemPontuarPacman(pacman));
    fprintf(estatisticas, "Numero de colisoes com parede: %d\n", ObtemNumeroColisoesParedePacman(pacman));
    fprintf(estatisticas, "Numero de movimentos para baixo: %d\n", ObtemNumeroMovimentosBaixoPacman(pacman));
    fprintf(estatisticas, "Numero de movimentos para cima: %d\n", ObtemNumeroMovimentosCimaPacman(pacman));
    fprintf(estatisticas, "Numero de movimentos para esquerda: %d\n", ObtemNumeroMovimentosEsquerdaPacman(pacman));
    fprintf(estatisticas, "Numero de movimentos para direita: %d\n", ObtemNumeroMovimentosDireitaPacman(pacman));
    fclose(estatisticas);
}

//FAZ RANKING.TXT
void rankingtxt(tPacman *pacman)
{
    FILE *ranking;

    ranking = fopen("ranking.txt", "w");

    tMv movimento[4], salvavalor;

    int i=0, j=0;

    movimento[0].comidas=ObtemNumeroFrutasComidasEsquerdaPacman(pacman);
    movimento[0].nome='a';
    movimento[0].movimentos=ObtemNumeroMovimentosEsquerdaPacman(pacman);
    movimento[0].colisoes=ObtemNumeroColisoesParedeEsquerdaPacman(pacman);
    
    movimento[1].comidas=ObtemNumeroFrutasComidasBaixoPacman(pacman);
    movimento[1].nome='s';
    movimento[1].movimentos=ObtemNumeroMovimentosBaixoPacman(pacman);
    movimento[1].colisoes=ObtemNumeroColisoesParedeBaixoPacman(pacman);

    movimento[2].comidas=ObtemNumeroFrutasComidasDireitaPacman(pacman);
    movimento[2].nome='d';
    movimento[2].movimentos=ObtemNumeroMovimentosDireitaPacman(pacman);
    movimento[2].colisoes=ObtemNumeroColisoesParedeDireitaPacman(pacman);

    movimento[3].comidas=ObtemNumeroFrutasComidasCimaPacman(pacman);
    movimento[3].nome='w';
    movimento[3].movimentos=ObtemNumeroMovimentosCimaPacman(pacman);
    movimento[3].colisoes=ObtemNumeroColisoesParedeCimaPacman(pacman);

    for(i=0;i<4;i++)
    {
        for(j=0;j<4;j++)
        {
            if(movimento[i].comidas>movimento[j].comidas)
            {
                salvavalor=movimento[j];
                movimento[j]=movimento[i];
                movimento[i]=salvavalor;
            }
            else if(movimento[i].comidas==movimento[j].comidas)
            {
                if(movimento[i].colisoes<movimento[j].colisoes)
                {
                    salvavalor=movimento[j];
                    movimento[j]=movimento[i];
                    movimento[i]=salvavalor;
                }
                else if(movimento[i].colisoes==movimento[j].colisoes)
                {
                    if(movimento[i].movimentos>movimento[j].movimentos)
                    {
                        salvavalor=movimento[j];
                        movimento[j]=movimento[i];
                        movimento[i]=salvavalor;
                    }
                    else if(movimento[i].movimentos==movimento[j].movimentos)
                    {
                        if(movimento[i].nome<movimento[j].nome)
                        {
                            salvavalor=movimento[j];
                            movimento[j]=movimento[i];
                            movimento[i]=salvavalor;
                        }
                    }
                }
            }
        }
    }

    //PRINTA EM ORDEM DECRESCENTE OS MOVIMENTOS(DO MELHOR PRO PIOR UTILIZADO)
    for(i=0;i<4;i++)
    {
        fprintf(ranking, "%c,%d,%d,%d\n", movimento[i].nome, movimento[i].comidas, movimento[i].colisoes, movimento[i].movimentos);
    }

    fclose(ranking);
}

//COLOCA OS FANTASMAS NO GRID
void ColocaFantasmaNoGrid(tMapa *mapa, tFantasma *fantasmas, int nfantasmas)
{
    int i;
    for(i=0 ; i<nfantasmas ; i++)
    {
        mapa->grid[fantasmas[i].linha][fantasmas[i].coluna]=fantasmas[i].nome;
    }
}

//RETORNA A POSICAO ANTERIOR
void VoltaPosicao(tPosicao *posicao, char tecla)
{
    if(tecla=='w')
    {
        posicao->linha++;
    }
    else if(tecla=='a')
    {
        posicao->coluna++;
    }
    else if(tecla=='d')
    {
        posicao->coluna--;
    }
    else if(tecla=='s')
    {
        posicao->linha--;
    }
}

//SOMA NUMERO DE FRUTA DO PACMAN DE ACORDO COM O COMANDO
void SomaComida(tPacman *pacman, COMANDO comando)
{
    if(comando == MOV_CIMA)
    {
        pacman->nFrutasComidasCima++;
    }
    else if(comando == MOV_BAIXO)
    {
        pacman->nFrutasComidasBaixo++;
    }
    else if(comando == MOV_ESQUERDA)
    {
        pacman->nFrutasComidasEsquerda++;
    }
    else if(comando == MOV_DIREITA)
    {
        pacman->nFrutasComidasDireita++;
    }
}