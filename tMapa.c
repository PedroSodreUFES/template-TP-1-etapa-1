#include "tMapa.h"
#include "tMovimento.h"
#include "tPacman.h"
#include "tPosicao.h"
#include "tTunel.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tAuxiliares.h"

tMapa* CriaMapa(const char* caminhoConfig)
{
    FILE *mp;
    int i, coluna;
    mp = fopen(caminhoConfig, "r");
    tMapa *mapa = (tMapa*)malloc(sizeof(tMapa));
    char **grid = (char **)malloc(200*sizeof(char *));
    for(i=0; i<200 ; i++)
    {
        grid[i]=(char *)malloc(sizeof(char)*200);
    }
    mapa->grid=grid;
    fscanf(mp, "%d%*c", &mapa->nMaximoMovimentos);
    i=0;
    while(fscanf(mp, "%[^\n]%*c", mapa->grid[i])==1)
    {
        if(i==1)
        {
            coluna = strlen(mapa->grid[i]);
        }
        i++;
    }
    mapa->nLinhas = i;
    mapa->nColunas = coluna;
    mapa->nFrutasAtual = ObtemQuantidadeFrutasIniciaisMapa(mapa);
    
    int j, linha1=-1, coluna1=-1, linha2=-1, coluna2=-1, a=0;
    for(i=0 ; i<ObtemNumeroLinhasMapa(mapa) ; i++)
    {
        for(j=0 ; j<ObtemNumeroColunasMapa(mapa) ; j++)
        {
            if(mapa->grid[i][j]=='@')
            {
                if(a==0)
                {
                    linha1=i;
                    coluna1=j;
                }
                else if(a==1)
                {
                    linha2=i;
                    coluna2=j;
                }
                a++;
            }
            if(a==2)
            {
                break;
            }
        }
        if(a==2)
        {
            break;
        }
    }
    if(linha1==-1)
    {
        mapa->tunel=NULL;
    }
    else
    {
        mapa->tunel = CriaTunel(linha1, coluna1, linha2, coluna2);  
    }
    fclose(mp);
    return mapa;
}

tTunel* ObtemTunelMapa(tMapa* mapa)
{
    return mapa->tunel;
}

tPosicao* ObtemPosicaoItemMapa(tMapa* mapa, char item)
{
    int i, j;
    for(i=0 ; i<mapa->nLinhas ; i++)
    {
        for(j=0 ; j<mapa->nColunas ; j++)
        {
            if(mapa->grid[i][j]==item)
            {
                tPosicao *p;
                p->linha=i;
                p->coluna=j;
                return p;
            }
        }
    }
    return NULL;
}

char ObtemItemMapa(tMapa* mapa, tPosicao* posicao)
{
    return mapa->grid[ObtemLinhaPosicao(posicao)][ObtemColunaPosicao(posicao)];
}

int ObtemNumeroLinhasMapa(tMapa* mapa)
{
    return mapa->nLinhas;
}

int ObtemNumeroColunasMapa(tMapa* mapa)
{
    return mapa->nColunas;
}

int ObtemQuantidadeFrutasIniciaisMapa(tMapa* mapa)
{
    int i, j, cont=0;
    for(i=0 ; i<ObtemNumeroLinhasMapa(mapa) ; i++)
    {
        for(j=0 ; j<ObtemNumeroColunasMapa(mapa) ; j++)
        {
            if(mapa->grid[i][j]=='*')
            {
                cont++;
            }
        }
    }
    return cont;
}


void DesalocaMapa(tMapa* mapa)
{
    int i;
    for(i=0 ; i<200 ; i++)
    {
        if(mapa->grid[i]!=NULL)
        {
            free(mapa->grid[i]);
        }
    }
    if(mapa->grid!=NULL)
    {
        free(mapa->grid);
    }
    if(PossuiTunelMapa(mapa))
    {
        DesalocaTunel(ObtemTunelMapa(mapa));
    }
    if(mapa!=NULL)
    {
        free(mapa);
    }
}

int ObtemNumeroMaximoMovimentosMapa(tMapa* mapa)
{
    return mapa->nMaximoMovimentos;
}

bool EncontrouComidaMapa(tMapa* mapa, tPosicao* posicao)
{
    if(mapa->grid[ObtemLinhaPosicao(posicao)][ObtemColunaPosicao(posicao)]=='*')
    {
        return true;
    }
    return false;
}

bool EncontrouParedeMapa(tMapa* mapa, tPosicao* posicao)
{
    if(mapa->grid[ObtemLinhaPosicao(posicao)][ObtemColunaPosicao(posicao)]=='#')
    {
        return true;
    }
    return false;
}

bool AtualizaItemMapa(tMapa* mapa, tPosicao* posicao, char item)
{
    if(mapa==NULL || mapa->grid==NULL || ObtemLinhaPosicao(posicao)>=ObtemNumeroLinhasMapa(mapa) || ObtemLinhaPosicao(posicao)<0 || ObtemColunaPosicao(posicao)>=ObtemNumeroColunasMapa(mapa) ||ObtemColunaPosicao(posicao)<0)
    {
        return false;
    }
    else
    {
        mapa->grid[ObtemLinhaPosicao(posicao)][ObtemColunaPosicao(posicao)]=item;
        return true;
    }
}

bool PossuiTunelMapa(tMapa* mapa)
{
    if(mapa->tunel==NULL)
    {
        return false;
    }
    else
    {
        return true;
    }
}

bool AcessouTunelMapa(tMapa* mapa, tPosicao* posicao)
{
    return EntrouTunel(mapa->tunel, posicao);
}

void EntraTunelMapa(tMapa* mapa, tPosicao* posicao)
{
    LevaFinalTunel(mapa->tunel, posicao);
}