#pragma once

#define MAX_CAR 100+1
#define MAX_ELEM 1000
#define MAX_CITTA 5

typedef struct{
	double x;
	double y;
}coordinate;

typedef struct{
	char nomeCitta[MAX_CAR];
	char nomeRegione[MAX_CAR];
	int abitanti;
	double superficie;
	coordinate coord;
}luoghi;

typedef struct{
    luoghi citta[MAX_ELEM];
    int numCitta;
}paese;
