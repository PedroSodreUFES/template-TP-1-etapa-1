#include "tMapa.h"
#include "tMovimento.h"
#include "tPacman.h"
#include "tPosicao.h"
#include "tTunel.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tAuxiliares.h"

tPacman* CriaPacman(tPosicao* posicao)
{
    tPacman *pacman = (tPacman*)malloc(sizeof(tPacman));
    pacman->estaVivo=1;
    pacman->historicoDeMovimentosSignificativos=NULL;
    pacman->nColisoesParedeBaixo=0;
    pacman->nColisoesParedeCima=0;
    pacman->nColisoesParedeDireita=0;
    pacman->nColisoesParedeEsquerda=0;
    pacman->nColunasTrilha=0;
    pacman->nFrutasComidasBaixo=0;
    pacman->nFrutasComidasCima=0;
    pacman->nFrutasComidasDireita=0;
    pacman->nFrutasComidasEsquerda=0;
    pacman->nLinhasTrilha=0;
    pacman->nMovimentosBaixo=0;
    pacman->nMovimentosCima=0;
    pacman->nMovimentosDireita=0;
    pacman->nMovimentosEsquerda=0;
    pacman->posicaoAtual=ClonaPosicao(posicao);
    pacman->trilha=NULL;
    pacman->nMovimentosSignificativos=0;
    return pacman;
}

tPacman* ClonaPacman(tPacman* pacman)
{
    tPacman *p = (tPacman*)malloc(sizeof(tPacman));
    p->posicaoAtual->linha = ObtemLinhaPosicao(ObtemPosicaoPacman(pacman));
    p->posicaoAtual->coluna = ObtemColunaPosicao(ObtemPosicaoPacman(pacman));
    return p;
}

tPosicao* ObtemPosicaoPacman(tPacman* pacman)
{
    return pacman->posicaoAtual;
}

int EstaVivoPacman(tPacman* pacman)
{
    return pacman->estaVivo;
}

void CriaTrilhaPacman(tPacman* pacman, int nLinhas, int nColunas)
{
    int i, j;
    int **trilha = (int **)malloc(nLinhas *sizeof(int*));
    for(i=0; i<nLinhas ; i++)
    {
        trilha[i] = (int *)malloc(nColunas * sizeof(int));
    }
    for(i=0; i<nLinhas ; i++)
    {
        for(j=0; j<nColunas ; j++)
        {
            trilha[i][j] = -1;
        }
    }
    trilha[ObtemLinhaPosicao(ObtemPosicaoPacman(pacman))][ObtemColunaPosicao(ObtemPosicaoPacman(pacman))]=0;
    pacman->trilha = trilha;
    pacman->nLinhasTrilha = nLinhas;
    pacman->nColunasTrilha = nColunas;
}

void AtualizaTrilhaPacman(tPacman* pacman)
{
    pacman->trilha[ObtemLinhaPosicao(ObtemPosicaoPacman(pacman))][ObtemColunaPosicao(ObtemPosicaoPacman(pacman))]=ObtemNumeroAtualMovimentosPacman(pacman);
}

void SalvaTrilhaPacman(tPacman* pacman)
{
    int i, j;
    FILE *inicializacao;
    inicializacao = fopen("trilha.txt", "w");
    for(i=0 ; i<pacman->nLinhasTrilha ; i++)
    {
        for(j=0; j<pacman->nColunasTrilha ; j++)
        {
            if(pacman->trilha[i][j]==-1)
            {
                fprintf(inicializacao, "#");
            }
            else
            {
                fprintf(inicializacao, "%d", pacman->trilha[i][j]);
            }
            if(j!=pacman->nColunasTrilha-1)
            {
                fprintf(inicializacao, " ");
            }
        }
        fprintf(inicializacao, "\n");
    }
    fclose(inicializacao);
}

void InsereNovoMovimentoSignificativoPacman(tPacman* pacman, COMANDO comando, const char* acao)
{
    tMovimento *movimento = CriaMovimento(ObtemNumeroAtualMovimentosPacman(pacman), comando , acao);
    pacman->historicoDeMovimentosSignificativos = realloc(pacman->historicoDeMovimentosSignificativos, ObtemNumeroMovimentosSignificativosPacman(pacman)*sizeof(tMovimento*));
    pacman->historicoDeMovimentosSignificativos[ObtemNumeroMovimentosSignificativosPacman(pacman)-1]=movimento;
}

void MataPacman(tPacman* pacman)
{
    pacman->estaVivo=0;
}

void DesalocaPacman(tPacman* pacman)
{
    int i;
    DesalocaPosicao(ObtemPosicaoPacman(pacman));
    for(i=0 ; i<pacman->nLinhasTrilha ; i++)
    {
        if(pacman->trilha[i]!=NULL)
        {
            free(pacman->trilha[i]);
        }
    }
    if(pacman->trilha!=NULL)
    {
        free(pacman->trilha);
    }
    for(i=0 ; i<pacman->nMovimentosSignificativos ; i++)
    {
        if(pacman->historicoDeMovimentosSignificativos[i]!=NULL)
        {
            free(pacman->historicoDeMovimentosSignificativos[i]);
        }
    }
    if(pacman->historicoDeMovimentosSignificativos!=NULL)
    {
        free(pacman->historicoDeMovimentosSignificativos);
    }
    if(pacman!=NULL)
    {
        free(pacman);
    }
}

int ObtemNumeroAtualMovimentosPacman(tPacman* pacman)
{
    return ObtemNumeroMovimentosBaixoPacman(pacman) + ObtemNumeroMovimentosCimaPacman(pacman) + ObtemNumeroMovimentosDireitaPacman(pacman) + ObtemNumeroMovimentosEsquerdaPacman(pacman);
}

int ObtemNumeroMovimentosSemPontuarPacman(tPacman* pacman)
{
    return ObtemNumeroAtualMovimentosPacman(pacman)-ObtemPontuacaoAtualPacman(pacman);
}

int ObtemNumeroColisoesParedePacman(tPacman* pacman)
{
    return ObtemNumeroColisoesParedeBaixoPacman(pacman) + ObtemNumeroColisoesParedeCimaPacman(pacman) + ObtemNumeroColisoesParedeDireitaPacman(pacman) + ObtemNumeroColisoesParedeEsquerdaPacman(pacman);
}

int ObtemNumeroMovimentosBaixoPacman(tPacman* pacman)
{
    return pacman->nMovimentosBaixo;
}

int ObtemNumeroFrutasComidasBaixoPacman(tPacman* pacman)
{
    return pacman->nFrutasComidasBaixo;
}

int ObtemNumeroColisoesParedeBaixoPacman(tPacman* pacman)
{
    return pacman->nColisoesParedeBaixo;
}

int ObtemNumeroMovimentosCimaPacman(tPacman* pacman)
{
    return pacman->nMovimentosCima;
}

int ObtemNumeroFrutasComidasCimaPacman(tPacman* pacman)
{
    return pacman->nFrutasComidasCima;
}

int ObtemNumeroColisoesParedeCimaPacman(tPacman* pacman)
{
    return pacman->nColisoesParedeCima;
}

int ObtemNumeroMovimentosEsquerdaPacman(tPacman* pacman)
{
    return pacman->nMovimentosEsquerda;
}

int ObtemNumeroFrutasComidasEsquerdaPacman(tPacman* pacman)
{
    return pacman->nFrutasComidasEsquerda;
}

int ObtemNumeroColisoesParedeEsquerdaPacman(tPacman* pacman)
{
    return pacman->nColisoesParedeEsquerda;
}

int ObtemNumeroMovimentosDireitaPacman(tPacman* pacman)
{
    return pacman->nMovimentosDireita;
}

int ObtemNumeroFrutasComidasDireitaPacman(tPacman* pacman)
{
    return pacman->nFrutasComidasDireita;
}

int ObtemNumeroColisoesParedeDireitaPacman(tPacman* pacman)
{
    return pacman->nColisoesParedeDireita;
}

int ObtemNumeroMovimentosSignificativosPacman(tPacman* pacman)
{
    return pacman->nMovimentosSignificativos;
}

int ObtemPontuacaoAtualPacman(tPacman* pacman)
{
    return ObtemNumeroFrutasComidasBaixoPacman(pacman) + ObtemNumeroFrutasComidasCimaPacman(pacman) + ObtemNumeroFrutasComidasEsquerdaPacman(pacman) + ObtemNumeroFrutasComidasDireitaPacman(pacman);
}

tMovimento** ClonaHistoricoDeMovimentosSignificativosPacman(tPacman* pacman)
{
    tMovimento **historico = (tMovimento**)malloc(ObtemNumeroMovimentosSignificativosPacman(pacman) * sizeof(tMovimento*));
    int i;
    for(i=0 ; i<ObtemNumeroMovimentosSignificativosPacman(pacman); i++)
    {
        historico[i]=CriaMovimento(ObtemNumeroMovimento(pacman->historicoDeMovimentosSignificativos[i]) , ObtemComandoMovimento(pacman->historicoDeMovimentosSignificativos[i]) , ObtemAcaoMovimento(pacman->historicoDeMovimentosSignificativos[i]));
    }
    if(historico==NULL)
    {
        return NULL;
    }
    return historico;
}

void MovePacman(tPacman* pacman, tMapa* mapa, COMANDO comando)
{
    tPosicao *posicaocheck=ClonaPosicao(ObtemPosicaoPacman(pacman));
    int tavanotunel=0, entroutunel=0, bateuparede=0;
    //Ve se pacman tava no tunel antes de se mexer
    if(EntrouTunel(ObtemTunelMapa(mapa), ObtemPosicaoPacman(pacman)))
    {
        tavanotunel=1;
    }
    
    //movimento
    if(comando == MOV_CIMA)
    {
        posicaocheck->linha--;
    }
    else if(comando == MOV_BAIXO)
    {
        posicaocheck->linha++;
    }
    else if(comando == MOV_ESQUERDA)
    {
        posicaocheck->coluna--;
    }
    else if(comando == MOV_DIREITA)
    {
        posicaocheck->coluna++;
    }

    //parede
    if(EncontrouParedeMapa(mapa, posicaocheck))
    {
        bateuparede=1;
        if(comando == MOV_CIMA)
        {
            pacman->nColisoesParedeCima++;
        }
        else if(comando == MOV_BAIXO)
        {
            pacman->nColisoesParedeBaixo++;
        }
        else if(comando == MOV_ESQUERDA)
        {
            pacman->nColisoesParedeEsquerda++;
        }
        else if(comando == MOV_DIREITA)
        {
            pacman->nColisoesParedeDireita++;
        }
    }

    //comida
    else if(EncontrouComidaMapa(mapa, posicaocheck))
    {
        if(tavanotunel==1)
        {
            mapa->grid[ObtemLinhaPosicao(ObtemPosicaoPacman(pacman))][ObtemColunaPosicao(ObtemPosicaoPacman(pacman))]='@';
        }
        else if(mapa->grid[ObtemLinhaPosicao(ObtemPosicaoPacman(pacman))][ObtemColunaPosicao(ObtemPosicaoPacman(pacman))]=='>')
        {
            mapa->grid[ObtemLinhaPosicao(ObtemPosicaoPacman(pacman))][ObtemColunaPosicao(ObtemPosicaoPacman(pacman))]=' ';
        }
        mapa->grid[posicaocheck->linha][posicaocheck->coluna]='>';
        pacman->posicaoAtual->linha = posicaocheck->linha;
        pacman->posicaoAtual->coluna = posicaocheck->coluna;
    }

    //tunel
    else if(mapa->grid[ObtemLinhaPosicao(posicaocheck)][ObtemColunaPosicao(posicaocheck)]=='@')
    {
        if(tavanotunel==1)
        {
            mapa->grid[ObtemLinhaPosicao(ObtemPosicaoPacman(pacman))][ObtemColunaPosicao(ObtemPosicaoPacman(pacman))]='@';
        }
        else if(mapa->grid[ObtemLinhaPosicao(ObtemPosicaoPacman(pacman))][ObtemColunaPosicao(ObtemPosicaoPacman(pacman))]=='>')
        {
            mapa->grid[ObtemLinhaPosicao(ObtemPosicaoPacman(pacman))][ObtemColunaPosicao(ObtemPosicaoPacman(pacman))]=' ';
        }
        pacman->posicaoAtual->linha = posicaocheck->linha;
        pacman->posicaoAtual->coluna = posicaocheck->coluna;
        AtualizaTrilhaPacman(pacman);
        EntraTunelMapa(mapa, pacman->posicaoAtual);
        mapa->grid[ObtemLinhaPosicao(ObtemPosicaoPacman(pacman))][ObtemColunaPosicao(ObtemPosicaoPacman(pacman))]='>';
        entroutunel=1;
    }

    //VAZIO
    else if(mapa->grid[ObtemLinhaPosicao(posicaocheck)][ObtemColunaPosicao(posicaocheck)]==' ')
    {
        if(tavanotunel==1)
        {
            mapa->grid[ObtemLinhaPosicao(ObtemPosicaoPacman(pacman))][ObtemColunaPosicao(ObtemPosicaoPacman(pacman))]='@';
        }
        else if(mapa->grid[ObtemLinhaPosicao(ObtemPosicaoPacman(pacman))][ObtemColunaPosicao(ObtemPosicaoPacman(pacman))]=='>')
        {
            mapa->grid[ObtemLinhaPosicao(ObtemPosicaoPacman(pacman))][ObtemColunaPosicao(ObtemPosicaoPacman(pacman))]=' ';
        }
        pacman->posicaoAtual->linha = posicaocheck->linha;
        pacman->posicaoAtual->coluna = posicaocheck->coluna;
        mapa->grid[ObtemLinhaPosicao(ObtemPosicaoPacman(pacman))][ObtemColunaPosicao(ObtemPosicaoPacman(pacman))]='>';
    }

    //pisoufantasma  
    else if(mapa->grid[ObtemLinhaPosicao(posicaocheck)][ObtemColunaPosicao(posicaocheck)]=='P'||mapa->grid[ObtemLinhaPosicao(posicaocheck)][ObtemColunaPosicao(posicaocheck)]=='C'||mapa->grid[ObtemLinhaPosicao(posicaocheck)][ObtemColunaPosicao(posicaocheck)]=='B'||mapa->grid[ObtemLinhaPosicao(posicaocheck)][ObtemColunaPosicao(posicaocheck)]=='I')
    {
        MataPacman(pacman);
        if(tavanotunel==1)
        {
            mapa->grid[ObtemLinhaPosicao(ObtemPosicaoPacman(pacman))][ObtemColunaPosicao(ObtemPosicaoPacman(pacman))]='@';
        }
        else if(mapa->grid[ObtemLinhaPosicao(ObtemPosicaoPacman(pacman))][ObtemColunaPosicao(ObtemPosicaoPacman(pacman))]=='>')
        {
            mapa->grid[ObtemLinhaPosicao(ObtemPosicaoPacman(pacman))][ObtemColunaPosicao(ObtemPosicaoPacman(pacman))]=' ';
        }
        pacman->posicaoAtual->linha = posicaocheck->linha;
        pacman->posicaoAtual->coluna = posicaocheck->coluna;
    }

    //PARADO EM CIMA DO TUNEL //NAO EH NECESSARIO
    /*if(tavanotunel==1 && bateuparede==1)
    {
        mapa->grid[ObtemLinhaPosicao(ObtemPosicaoPacman(pacman))][ObtemColunaPosicao(ObtemPosicaoPacman(pacman))]='@';
        AtualizaTrilhaPacman(pacman);
        EntraTunelMapa(mapa, ObtemPosicaoPacman(pacman));
        mapa->grid[ObtemLinhaPosicao(ObtemPosicaoPacman(pacman))][ObtemColunaPosicao(ObtemPosicaoPacman(pacman))]='>';
    }*/
    free(posicaocheck);
}