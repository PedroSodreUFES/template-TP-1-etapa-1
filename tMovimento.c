#include "tMapa.h"
#include "tMovimento.h"
#include "tPacman.h"
#include "tPosicao.h"
#include "tTunel.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tAuxiliares.h"

tMovimento* CriaMovimento(int numeroDoMovimento, COMANDO comando, const char* acao)
{
    tMovimento *movimento = (tMovimento*)malloc(sizeof(tMovimento));
    movimento->comando=comando;
    movimento->numeroDoMovimento=numeroDoMovimento;
    strcpy(movimento->acao, acao);
    return movimento;
}

int ObtemNumeroMovimento(tMovimento* movimento)
{
    return movimento->numeroDoMovimento;
}

COMANDO ObtemComandoMovimento(tMovimento* movimento)
{
    return movimento->comando;
}

char* ObtemAcaoMovimento(tMovimento* movimento)
{
    return movimento->acao;
}

void DesalocaMovimento(tMovimento* movimento)
{
    if(movimento!=NULL)
    {
        free(movimento);
    }
}

void EntraTunelMapa(tMapa* mapa, tPosicao* posicao);
