#pragma once

#ifndef SERIJE_H
#define SERIJE_H

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define DATOTEKA "serije.dat"

#define MAX_NAZIV 100
#define MAX_ZANR 50
#define MAX_PLATFORMA 50

extern int ukupnoSerija;

typedef enum
{
    PLANIRAM,
    GLEDAM,
    ZAVRSENO,
    ODUSTAO
} Status;

typedef enum
{
    IZLAZ = 0,
    DODAJ = 1,
    PRIKAZI = 2,
    AZURIRAJ = 3,
    OBRISI = 4,
    SORTIRAJ = 5,
    PRETRAZI = 6,
    REKURZIJA = 7,
    OBRISI_DATOTEKU = 8,
    PREIMENUJ_DATOTEKU = 9
} Izbornik;

typedef struct
{
    char naziv[MAX_NAZIV];
    char zanr[MAX_ZANR];
    int brojSezona;
    int pogledaneSezone;
    int godina;
    Status status;
    float ocjena;
    char platforma[MAX_PLATFORMA];
} Serija;

static inline int jePrazanNiz(int broj)
{
    return broj <= 0;
}

void ucitajSerije(Serija** serije, int* broj);
void spremiSerije(const Serija* serije, int broj);

void dodajSeriju(Serija** serije, int* broj);
void prikaziSerije(const Serija* serije, int broj);

void obrisiSeriju(Serija** serije, int* broj);
void azurirajSeriju(Serija* serije, int broj);

void sortirajSerije(Serija* serije, int broj);
void pretraziSeriju(Serija* serije, int broj);

void rekurzivniIspis(const Serija* serije, int broj, int index);

void obrisiDatoteku(void);
void preimenujDatoteku(void);

const char* statusToString(Status status);

#endif
