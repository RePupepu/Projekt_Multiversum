#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "multiwersum.h"

// Implementacja funkcji pomocniczej
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
    setlocale(LC_ALL, ""); 

    if (argc < 2) {
        printf("BLAD: Nie podano nazwy pliku bazy danych!\n");
        printf("Uzycie: %s <nazwa_pliku.txt>\n", argv[0]);
        printf("UWAGA: Uruchomiono w trybie testowym (bez zapisu).\n");
    }

    Przedmiot* baza = NULL;
    int wybor = -1;

    while (wybor != 0) {
        naglowek_aplikacji();
        if (baza != NULL) printf("  [Aktualnie w bazie sa dane]\n");
        else printf("  [Baza jest pusta]\n");
        
        printf("------------------------------------------------------\n");
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
        
        switch (wybor) {
            case 1:
                dodaj_przedmiot(&baza);
                break;
            case 2:
                wyswietl_liste(baza);
                break;
            case 3:
                edytuj_przedmiot(baza);
                break;
            case 4:
                usun_przedmiot(&baza);
                break;
            case 0:
                printf("\nZamykanie systemu...\n");
                break;
            case 5:
                wyszukaj_przedmioty(baza);
                break;
            case 6:
                sortuj_przedmioty(baza);
                break;
            default:
                printf("\nNieznana opcja.\n");
        }

        if (wybor != 0) {
            printf("\nWcisnij Enter, aby kontynuowac...");
            getchar();
            getchar();
        }
    }


    return 0;
}