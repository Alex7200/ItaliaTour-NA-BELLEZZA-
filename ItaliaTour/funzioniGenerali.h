#pragma once

#include "librerie.h"

#define CAR_SEPARATORE ';'
#define CURVATURA_TERRESTRE 0.9996

double distanzaCitta(const luoghi &citta1, const luoghi &citta2);
double distanzaPiuCitta( const paese &italia , int cittaTransitorie);

void showInfo( const luoghi &citta );
void addCitta( paese &italia );
void addCittaFile( paese &italia );

int inserisciNomeCitta(const char stringa[], const paese &italia);
int ricercaCitta(const char nomeCitta[], const paese &italia);
void confronto(const luoghi &citta1, const luoghi &citta2);

void puntiInteresse(const luoghi &citta);
