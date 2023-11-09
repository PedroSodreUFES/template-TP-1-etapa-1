#include "tMapa.h"
#include "tMovimento.h"
#include "tPacman.h"
#include "tPosicao.h"
#include "tTunel.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tAuxiliares.h"

tPosicao* CriaPosicao(int linha, int coluna)
{
    tPosicao *posicao = (tPosicao *)malloc(sizeof(tPosicao));
    posicao->linha = linha;
    posicao->coluna = coluna;
    return posicao;
}

tPosicao* ClonaPosicao(tPosicao* posicao)
{
    tPosicao *p = (tPosicao*)malloc(sizeof(tPosicao));
    p->linha=posicao->linha;
    p->coluna=posicao->coluna;
    return p;
}

int ObtemLinhaPosicao(tPosicao* posicao)
{
    return posicao->linha;
}

int ObtemColunaPosicao(tPosicao* posicao)
{
    return posicao->coluna;
}

void AtualizaPosicao(tPosicao* posicaoAtual, tPosicao* posicaoNova)
{
    if(posicaoAtual!=NULL)
    {
        free(posicaoAtual);
    }
    posicaoAtual=posicaoNova;
}

bool SaoIguaisPosicao(tPosicao* posicao1, tPosicao* posicao2)
{
    if(ObtemLinhaPosicao(posicao1)==ObtemLinhaPosicao(posicao2) && ObtemColunaPosicao(posicao1) == ObtemColunaPosicao(posicao2))
    {
        return true;
    }
    return false;
}

void DesalocaPosicao(tPosicao* posicao)
{
    if(posicao!=NULL)
    {
        free(posicao);
    }
}