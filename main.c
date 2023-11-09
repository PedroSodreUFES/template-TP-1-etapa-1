#include "tMapa.h"
#include "tMovimento.h"
#include "tPacman.h"
#include "tPosicao.h"
#include "tTunel.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tAuxiliares.h"

int main(int argc, char **argv)
{
    int n;
    tMapa *mapa = CriaMapa(argv[1]);
    inicializacaotxt(mapa);
    n = ContaFantasma(mapa);
    tFantasma *fantasma = InicializaFantasmas(mapa, n);
    tPacman *pacman = CriaPacman(ObtemPosicaoItemMapa(mapa, '>'));
    CriaTrilhaPacman(pacman, ObtemNumeroLinhasMapa(mapa), ObtemNumeroColunasMapa(mapa));
    RealizaJogo(pacman, mapa, fantasma, n);
    resumotxt(pacman);
    SalvaTrilhaPacman(pacman);
    rankingtxt(pacman);
    estatisticastxt(pacman);
    DesalocaPacman(pacman);
    DesalocaMapa(mapa);
    DesalocaFantasmas(fantasma);
    return 0;
}