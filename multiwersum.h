#ifndef MULTIWERSUM_H
#define MULTIWERSUM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX_NAZWA 100
#define MAX_SWIAT 50
#define MAX_OPIS 200

typedef enum {
    STABILNY,
    CHWIEJNY,
    NIESTABILNY,
    NIEKLASYFIKOWANY
} StatusStabilnosci;

typedef struct Przedmiot {
    char nazwa[MAX_NAZWA + 1];
    char swiat_pochodzenia[MAX_SWIAT + 1];
    int poziom_chaosu;
    char opis_efektu[MAX_OPIS + 1];
    StatusStabilnosci stabilnosc;
    struct Przedmiot* nastepny;
} Przedmiot;

void naglowek_aplikacji();
void wyczysc_bufor();
void dodaj_przedmiot(Przedmiot** baza);
void wyswietl_liste(Przedmiot* baza);
void edytuj_przedmiot(Przedmiot* baza);
void usun_przedmiot(Przedmiot** baza);
void wyszukaj_przedmioty(Przedmiot* baza);
void sortuj_przedmioty(Przedmiot* baza);
void zwolnij_pamiec(Przedmiot** baza);
void zapisz_do_pliku(Przedmiot* baza, const char* nazwa_pliku);
void wczytaj_z_pliku(Przedmiot** baza, const char* nazwa_pliku);
#endif