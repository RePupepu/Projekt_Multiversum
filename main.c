#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "multiwersum.h"

// Funkcja pomocnicza do czyszczenia bufora
void wyczysc_bufor() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void naglowek_aplikacji() {
    printf("\n======================================================\n");
    printf("   BIURO ZAGUBIONYCH RZECZY MULTIWERSUM (System v1.0)\n");
    printf("======================================================\n");
}

int main(int argc, char *argv[]) {
    // Ustawienie polskich znaków
    setlocale(LC_ALL, ""); 

    //Ścieżka do pliku przekazywana w argumencie
    if (argc < 2) {
        printf("BLAD: Nie podano nazwy pliku bazy danych!\n");
        printf("Uzycie: %s <nazwa_pliku.txt>\n", argv[0]);
        printf("UWAGA: Uruchomiono w trybie testowym (bez zapisu).\n");
    }

    Przedmiot* baza = NULL;
    int wybor = -1;

    while (wybor != 0) {
        naglowek_aplikacji();
        printf("1. Dodaj nowy przedmiot\n");
        printf("2. Wyswietl liste przedmiotow\n");
        printf("3. Edytuj przedmiot\n");
        printf("4. Usun przedmiot\n");
        printf("5. Wyszukiwanie i Filtry\n");
        printf("6. Sortowanie\n");
        printf("7. Zapisz / Wczytaj baze\n");
        printf("0. Wyjscie\n");
        printf("------------------------------------------------------\n");
        printf("Twoj wybor: ");

        if (scanf("%d", &wybor) != 1) {
            printf("To nie jest liczba!\n");
            wyczysc_bufor();
            continue;
        }
        wyczysc_bufor();

        switch (wybor) {
            case 1:
                printf("\n[INFO] Funkcja dodawania wkrotce...\n");
                break;
            case 2:
                printf("\n[INFO] Lista jest pusta.\n");
                break;
            case 0:
                printf("\nZamykanie systemu...\n");
                break;
            default:
                printf("\nNieznana opcja.\n");
        }

        if (wybor != 0) {
            printf("\nWcisnij Enter, aby kontynuowac...");
            getchar();
        }
    }

    return 0;
}