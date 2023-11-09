#ifndef TAUXILIARES_H_
#define TAUXILIARES_H_

#include "tMapa.h"
#include "tMovimento.h"
#include "tPacman.h"
#include "tPosicao.h"
#include "tTunel.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tAuxiliares.h"


typedef struct tFantasma{
    int comida;
    int invertido;
    int tunel;
    char nome;
    int linha;
    int coluna;
} tFantasma;

typedef struct tMv{
    int colisoes;
    int comidas;
    char nome;
    int movimentos;
}tMv;


void MoveFantasma(tMapa* mapa, tFantasma* fantasma, int n, int h, int v, COMANDO comando, tPacman* pacman);

void MoveFantasmas(tMapa* mapa, tFantasma* fantasmas, int nfantasmas, COMANDO comando, tPacman* pacman);

tFantasma* InicializaFantasmas(tMapa* mapa, int nfantasmas);

int ContaFantasma(tMapa* mapa);

int VeSeAlgumFantasmaTaInvertido(tMapa* mapa, int z, tFantasma* fantasma);

void DesalocaFantasmas(tFantasma *fantasma);

void RealizaJogo(tPacman *pacman, tMapa *mapa, tFantasma *fantasmas, int nfantasmas);

int pacmanprensado(tPacman* pacman,tFantasma* fantasma, int nfantasmas);

void PrintaMapa(tMapa *mapa, char tecla, tPacman *pacman, tFantasma *fantasma, int nfantasmas);

void inicializacaotxt(tMapa *mapa);

void resumotxt(tPacman *pacman);

void rankingtxt(tPacman *pacman);

void estatisticastxt(tPacman *pacman);

void ColocaFantasmaNoGrid(tMapa *mapa, tFantasma *fantasmas, int nfantasmas);

void VoltaPosicao(tPosicao *posicao, char tecla);

void SomaComida(tPacman *pacman, COMANDO comando);

#endif