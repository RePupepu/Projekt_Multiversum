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

void wyswietl_liste(Przedmiot* baza) {
    if (baza == NULL) {
        printf("\n[INFO] Archiwum jest puste. Brak zarejestrowanych przedmiotow.\n");
        return;
    }

    printf("\n%-30s | %-15s | %-5s | %-15s\n", "Nazwa", "Swiat", "Chaos", "Stabilnosc");
    printf("-------------------------------------------------------------------------------\n");

    Przedmiot* aktualny = baza;
    while (aktualny != NULL) {
        // Zamiana numerka (enum) na tekst
        char stan[20];
        switch(aktualny->stabilnosc) {
            case STABILNY: strcpy(stan, "Stabilny"); break;
            case CHWIEJNY: strcpy(stan, "Chwiejny"); break;
            case NIESTABILNY: strcpy(stan, "!NIESTABILNY!"); break;
            default: strcpy(stan, "Nieznany"); break;
        }

        printf("%-30s | %-15s | %-5d | %-15s\n", 
            aktualny->nazwa, aktualny->swiat_pochodzenia, aktualny->poziom_chaosu, stan);
        
        aktualny = aktualny->nastepny;
    }
    printf("-------------------------------------------------------------------------------\n");
}
void edytuj_przedmiot(Przedmiot* baza) {
    if (baza == NULL) {
        printf("\n[BLAD] Baza jest pusta. Nie ma czego edytowac.\n");
        return;
    }

    char szukana_nazwa[MAX_NAZWA];
    printf("\nPodaj nazwe przedmiotu do edycji: ");
    wyczysc_bufor();
    wczytaj_tekst(szukana_nazwa, MAX_NAZWA);

    Przedmiot* aktualny = baza;
    while (aktualny != NULL) {
        if (strcmp(aktualny->nazwa, szukana_nazwa) == 0) {
            printf("\n--- EDYCJA PRZEDMIOTU: %s ---\n", aktualny->nazwa);
            printf("Aktualny poziom chaosu: %d\n", aktualny->poziom_chaosu);
            printf("Aktualny opis: %s\n", aktualny->opis_efektu);
            
            //1. Zmiana chaosu
            int nowy_chaos;
            printf("\nPodaj nowy poziom chaosu (0-10): ");
            while (scanf("%d", &nowy_chaos) != 1 || nowy_chaos < 0 || nowy_chaos > 10) {
                printf("Blad! Podaj liczbe 0-10: ");
                wyczysc_bufor();
            }
            aktualny->poziom_chaosu = nowy_chaos;
            wyczysc_bufor();

            // 2. Zmiana opisu
            printf("Podaj nowy opis efektu: ");
            wczytaj_tekst(aktualny->opis_efektu, MAX_OPIS);

            printf("[SUKCES] Dane przedmiotu zostaly zaktualizowane.\n");
            return;
        }
        aktualny = aktualny->nastepny;
    }

    printf("\n[INFO] Nie znaleziono przedmiotu o nazwie '%s'.\n", szukana_nazwa);
}

void usun_przedmiot(Przedmiot** baza) {
    if (*baza == NULL) {
        printf("\n[BLAD] Baza jest pusta. Nie ma czego usuwac.\n");
        return;
    }

    char nazwa_do_usuniecia[MAX_NAZWA];
    printf("\nPodaj nazwe przedmiotu do usuniecia: ");
    wyczysc_bufor();
    wczytaj_tekst(nazwa_do_usuniecia, MAX_NAZWA);

    Przedmiot* obecny = *baza;
    Przedmiot* poprzedni = NULL;

    while (obecny != NULL) {
        if (strcmp(obecny->nazwa, nazwa_do_usuniecia) == 0) {
            
            if (obecny->stabilnosc == NIESTABILNY) {
                printf("\n[OSTRZEZENIE] Nie mozna usunac przedmiotu '%s'!", obecny->nazwa);
                printf("\nStatus: NIESTABILNY. Ryzyko zapasci czasoprzestrzennej!\n");
                return; 
            }

            if (poprzedni == NULL) {
                *baza = obecny->nastepny;
            } else {
                poprzedni->nastepny = obecny->nastepny;
            }

            free(obecny); 
            printf("\n[SUKCES] Przedmiot '%s' zostal usuniety z ewidencji.\n", nazwa_do_usuniecia);
            return;
        }

        poprzedni = obecny;
        obecny = obecny->nastepny;
    }

    printf("\n[INFO] Nie znaleziono przedmiotu o nazwie '%s'.\n", nazwa_do_usuniecia);
}

void wyszukaj_przedmioty(Przedmiot* baza) {
    if (baza == NULL) {
        printf("\n[INFO] Baza jest pusta. Nie ma czego szukac.\n");
        return;
    }

    int opcja;
    printf("\n--- WYSZUKIWANIE ---\n");
    printf("1. Szukaj po nazwie (zawiera tekst)\n");
    printf("2. Filtruj po poziomie chaosu (>= wartosc)\n");
    printf("Wybierz kryterium: ");
    
    if (scanf("%d", &opcja) != 1) {
        printf("Blad wejscia.\n");
        wyczysc_bufor();
        return;
    }
    wyczysc_bufor();

    printf("\n%-30s | %-15s | %-5s | %-15s\n", "Nazwa", "Swiat", "Chaos", "Stabilnosc");
    printf("-------------------------------------------------------------------------------\n");

    Przedmiot* aktualny = baza;
    int znaleziono = 0;

    if (opcja == 1) {
        char szukany_tekst[MAX_NAZWA];
        printf("Podaj fragment nazwy: ");
        wczytaj_tekst(szukany_tekst, MAX_NAZWA);

        while (aktualny != NULL) {
            if (strstr(aktualny->nazwa, szukany_tekst) != NULL) {
                char stan[20];
                if (aktualny->stabilnosc == STABILNY) strcpy(stan, "Stabilny");
                else if (aktualny->stabilnosc == CHWIEJNY) strcpy(stan, "Chwiejny");
                else if (aktualny->stabilnosc == NIESTABILNY) strcpy(stan, "!NIESTABILNY!");
                else strcpy(stan, "Nieznany");

                printf("%-30s | %-15s | %-5d | %-15s\n", 
                    aktualny->nazwa, aktualny->swiat_pochodzenia, aktualny->poziom_chaosu, stan);
                znaleziono++;
            }
            aktualny = aktualny->nastepny;
        }

    } else if (opcja == 2) {
        int min_chaos;
        printf("Pokaz przedmioty o poziomie chaosu wiekszym lub rownym: ");
        scanf("%d", &min_chaos);
        wyczysc_bufor();

        while (aktualny != NULL) {
            if (aktualny->poziom_chaosu >= min_chaos) {
                char stan[20];
                if (aktualny->stabilnosc == STABILNY) strcpy(stan, "Stabilny");
                else if (aktualny->stabilnosc == CHWIEJNY) strcpy(stan, "Chwiejny");
                else if (aktualny->stabilnosc == NIESTABILNY) strcpy(stan, "!NIESTABILNY!");
                else strcpy(stan, "Nieznany");

                printf("%-30s | %-15s | %-5d | %-15s\n", 
                    aktualny->nazwa, aktualny->swiat_pochodzenia, aktualny->poziom_chaosu, stan);
                znaleziono++;
            }
            aktualny = aktualny->nastepny;
        }
    } else {
        printf("Nieznana opcja wyszukiwania.\n");
    }

    printf("-------------------------------------------------------------------------------\n");
    if (znaleziono == 0) printf("[INFO] Brak wynikow spelniajacych kryteria.\n");
}