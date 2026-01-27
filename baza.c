#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "multiwersum.h"

// Funkcja pomocnicza do wczytywania tekstu bez entera
void wczytaj_tekst(char* bufor, int rozmiar) {
    fgets(bufor, rozmiar, stdin);
    size_t len = strlen(bufor);
    if (len > 0 && bufor[len - 1] == '\n') {
        bufor[len - 1] = '\0';
    }
}

void dodaj_przedmiot(Przedmiot** baza) {
    // 1. Alokacja pamięci na stercie
    Przedmiot* nowy = (Przedmiot*)malloc(sizeof(Przedmiot));
    
    if (nowy == NULL) {
        printf("BLAD: Brak pamieci RAM!\n");
        return;
    }

    printf("\n--- DODAWANIE NOWEGO OBIEKTU ---\n");
    
    // 2. Wczytywanie danych
    printf("Nazwa przedmiotu: ");
    wyczysc_bufor();
    wczytaj_tekst(nowy->nazwa, MAX_NAZWA);

    printf("Swiat pochodzenia: ");
    wczytaj_tekst(nowy->swiat_pochodzenia, MAX_SWIAT);

    printf("Poziom chaosu (0-10): ");
    int chaos;
    while (scanf("%d", &chaos) != 1 || chaos < 0 || chaos > 10) {
        printf("Blad! Podaj liczbe calkowita z zakresu 0-10: ");
        wyczysc_bufor();
    }
    nowy->poziom_chaosu = chaos;
    wyczysc_bufor();

    printf("Opis efektu: ");
    wczytaj_tekst(nowy->opis_efektu, MAX_OPIS);

    printf("Status stabilnosci (0-Stabilny, 1-Chwiejny, 2-Niestabilny, 3-Nieklasyfikowany): ");
    int status;
    if (scanf("%d", &status) != 1) status = 3;
    
    switch(status) {
        case 0: nowy->stabilnosc = STABILNY; break;
        case 1: nowy->stabilnosc = CHWIEJNY; break;
        case 2: nowy->stabilnosc = NIESTABILNY; break;
        default: nowy->stabilnosc = NIEKLASYFIKOWANY; break;
    }

    // 3. Wstawianie elementu na początek listy
    nowy->nastepny = *baza; 
    *baza = nowy;           

    printf("[SUKCES] Przedmiot '%s' zostal dodany do bazy.\n", nowy->nazwa);
}