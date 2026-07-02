#define _CRT_SECURE_NO_WARNINGS

#include "serije.h"

int main(void)
{
    Serija* serije = NULL;
    int brojSerija = 0;
    int izbor = -1;

    ucitajSerije(&serije, &brojSerija);

    do
    {
        printf("\n=============================\n");
        printf("      PRACENJE SERIJA\n");
        printf("=============================\n");

        printf("1. Dodaj seriju\n");
        printf("2. Prikazi serije\n");
        printf("3. Azuriraj seriju\n");
        printf("4. Obrisi seriju\n");
        printf("5. Sortiraj serije\n");
        printf("6. Pretrazi seriju\n");
        printf("7. Rekurzivni ispis\n");
        printf("8. Obrisi datoteku\n");
        printf("9. Preimenuj datoteku\n");
        printf("0. Izlaz\n");

        printf("Odabir: ");

        if (scanf("%d", &izbor) != 1)
        {
            while (getchar() != '\n');
            izbor = -1;
        }

        getchar();

        switch ((Izbornik)izbor)
        {
        case DODAJ:
            dodajSeriju(&serije, &brojSerija);
            break;

        case PRIKAZI:
            prikaziSerije(serije, brojSerija);
            break;

        case AZURIRAJ:
            azurirajSeriju(serije, brojSerija);
            break;

        case OBRISI:
            obrisiSeriju(&serije, &brojSerija);
            break;

        case SORTIRAJ:
            sortirajSerije(serije, brojSerija);
            break;

        case PRETRAZI:
            sortirajSerije(serije, brojSerija);
            pretraziSeriju(serije, brojSerija);
            break;

        case REKURZIJA:
            rekurzivniIspis(serije, brojSerija, 0);
            break;

        case OBRISI_DATOTEKU:
            obrisiDatoteku();
            break;

        case PREIMENUJ_DATOTEKU:
            preimenujDatoteku();
            break;

        case IZLAZ:

            spremiSerije(serije, brojSerija);

            if (serije != NULL)
            {
                free(serije);
                serije = NULL;
            }

            printf("Program zavrsen.\n");
            break;

        default:
            printf("Neispravan unos.\n");
            break;
        }

    } while (izbor != 0);

    return 0;
}
