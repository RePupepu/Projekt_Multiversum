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
    setlocale(LC_ALL, ""); 

    char* nazwa_pliku = "baza_domyslna.txt";

    if (argc < 2) {
        printf("UWAGA: Nie podano nazwy pliku w parametrach!\n");
        printf("System uzyje pliku domyslnego: %s\n", nazwa_pliku);
        printf("Aby podac wlasny plik, uruchom: %s <nazwa_pliku.txt>\n", argv[0]);
        printf("\nWcisnij Enter, aby rozpoczac...");
        getchar();
    } else {
        nazwa_pliku = argv[1];
    }

    Przedmiot* baza = NULL;

    wczytaj_z_pliku(&baza, nazwa_pliku);

    int wybor = -1;

    while (wybor != 0) {
        naglowek_aplikacji();
        printf("PLIK BAZY DANYCH: %s\n", nazwa_pliku);
        if (baza != NULL) printf("  [Stan: W pamieci znajduja sie dane]\n");
        else printf("  [Stan: Baza jest pusta]\n");
        
        printf("------------------------------------------------------\n");
        printf("1. Dodaj nowy przedmiot\n");
        printf("2. Wyswietl liste przedmiotow\n");
        printf("3. Edytuj przedmiot\n");
        printf("4. Usun przedmiot\n");
        printf("5. Wyszukiwanie i Filtry\n");
        printf("6. Sortowanie\n");
        printf("7. Zapisz zmiany do pliku\n");
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
            case 5:
                wyszukaj_przedmioty(baza);
                break;
            case 6:
                sortuj_przedmioty(baza);
                break;
            case 7:
                zapisz_do_pliku(baza, nazwa_pliku);
                break;
            case 0:
                printf("\nCzy chcesz zapisac zmiany przed wyjsciem? (1-Tak, 0-Nie): ");
                int decyzja;
                scanf("%d", &decyzja);
                if (decyzja == 1) {
                    zapisz_do_pliku(baza, nazwa_pliku);
                }
                zwolnij_pamiec(&baza);
                printf("\nZamykanie systemu... Do widzenia!\n");
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