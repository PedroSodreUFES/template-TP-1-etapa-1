#include "tMapa.h"
#include "tMovimento.h"
#include "tPacman.h"
#include "tPosicao.h"
#include "tTunel.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

tTunel* CriaTunel(int linhaAcesso1, int colunaAcesso1, int linhaAcesso2, int colunaAcesso2)
{
    tTunel *tunel = (tTunel*)malloc(sizeof(tTunel));
    tPosicao *p1 = CriaPosicao(linhaAcesso1, colunaAcesso1);
    tPosicao *p2 = CriaPosicao(linhaAcesso2, colunaAcesso2);
    tunel->acesso1 = p1;
    tunel->acesso2 = p2;
    return tunel;
}

bool EntrouTunel(tTunel* tunel, tPosicao* posicao)
{
    if(tunel==NULL)
    {
        return false;
    }
    else if(SaoIguaisPosicao(posicao, tunel->acesso1))
    { 
        return true;
    }
    else if(SaoIguaisPosicao(posicao, tunel->acesso2))
    {
        return true;
    }
    return false;
}

void LevaFinalTunel(tTunel* tunel, tPosicao* posicao)
{
    if(tunel->acesso1->linha == posicao->linha && tunel->acesso1->coluna == posicao->coluna)
    {
        posicao->coluna = tunel->acesso2->coluna;
        posicao->linha = tunel->acesso2->linha;
    }
    else if(tunel->acesso2->linha == posicao->linha && tunel->acesso2->coluna == posicao->coluna)
    {
        posicao->coluna = tunel->acesso1->coluna;
        posicao->linha = tunel->acesso1->linha;
    }
}

void DesalocaTunel(tTunel* tunel)
{
    if(tunel->acesso1!=NULL)
    {
        free(tunel->acesso1);
    }
    if(tunel->acesso2!=NULL)
    {
        free(tunel->acesso2);
    }
    if(tunel!=NULL)
    {
        free(tunel);
    }
}