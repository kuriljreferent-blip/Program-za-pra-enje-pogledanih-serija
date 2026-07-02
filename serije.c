#define _CRT_SECURE_NO_WARNINGS

#include "serije.h"

/* GLOBALNA VARIJABLA */
int ukupnoSerija = 0;

/* STATIC VARIJABLA */
static int brojPokretanja = 0;

/* PROTOTIP LOKALNE FUNKCIJE */
static int compare(const void* a, const void* b);

/* SPREMANJE U DATOTEKU */
void spremiSerije(const Serija* serije, int broj)
{
    if (serije == NULL || broj < 0)
    {
        return;
    }

    FILE* fp = fopen(DATOTEKA, "wb");

    if (fp == NULL)
    {
        perror("fopen");
        printf("%s\n", strerror(errno));
        return;
    }

    size_t zapisano = fwrite(
        serije,
        sizeof(Serija),
        broj,
        fp
    );

    if (zapisano != (size_t)broj)
    {
        perror("fwrite");
    }

    if (ferror(fp))
    {
        perror("Greska pri pisanju datoteke");
    }

    fclose(fp);
}

/* UCITAVANJE IZ DATOTEKE */
void ucitajSerije(Serija** serije, int* broj)
{
    if (serije == NULL || broj == NULL)
    {
        return;
    }

    FILE* fp = fopen(DATOTEKA, "rb");

    if (fp == NULL)
    {
        *serije = NULL;
        *broj = 0;

        perror("Datoteka nije pronadena");
        return;
    }

    fseek(fp, 0, SEEK_END);

    long velicina = ftell(fp);

    rewind(fp);

    *broj = (int)(velicina / sizeof(Serija));

    if (*broj <= 0)
    {
        *serije = NULL;

        fclose(fp);
        return;
    }

    *serije = (Serija*)calloc(*broj, sizeof(Serija));

    if (*serije == NULL)
    {
        perror("calloc");

        fclose(fp);
        return;
    }

    size_t procitano = fread(
        *serije,
        sizeof(Serija),
        *broj,
        fp
    );

    if (procitano != (size_t)(*broj))
    {
        if (!feof(fp))
        {
            perror("fread");
        }
    }

    if (ferror(fp))
    {
        perror("Greska pri citanju");
    }

    fclose(fp);

    ukupnoSerija = *broj;
}

/* DODAVANJE */
void dodajSeriju(Serija** serije, int* broj)
{
    if (serije == NULL || broj == NULL)
    {
        return;
    }

    Serija nova = { 0 };

    printf("Naziv: ");
    fgets(nova.naziv, MAX_NAZIV, stdin);
    nova.naziv[strcspn(nova.naziv, "\n")] = '\0';

    printf("Zanr: ");
    fgets(nova.zanr, MAX_ZANR, stdin);
    nova.zanr[strcspn(nova.zanr, "\n")] = '\0';

    printf("Broj sezona: ");
    scanf("%d", &nova.brojSezona);

    printf("Pogledane sezone: ");
    scanf("%d", &nova.pogledaneSezone);

    printf("Godina: ");
    scanf("%d", &nova.godina);

    printf("Status (0-Planiram, 1-Gledam, 2-Zavrseno, 3-Odustao): ");
    scanf("%d", (int*)&nova.status);

    printf("Ocjena: ");
    scanf("%f", &nova.ocjena);

    getchar();

    printf("Platforma: ");
    fgets(nova.platforma, MAX_PLATFORMA, stdin);
    nova.platforma[strcspn(nova.platforma, "\n")] = '\0';

    Serija* temp = realloc(
        *serije,
        (*broj + 1) * sizeof(Serija)
    );

    if (temp == NULL)
    {
        perror("realloc");
        return;
    }

    *serije = temp;

    (*serije)[*broj] = nova;

    (*broj)++;
    ukupnoSerija++;

    spremiSerije(*serije, *broj);

    brojPokretanja++;

    printf("Serija uspjesno dodana.\n");
}

/* PRIKAZ */
void prikaziSerije(const Serija* serije, int broj)
{
    if (serije == NULL || jePrazanNiz(broj))
    {
        printf("Nema spremljenih serija.\n");
        return;
    }

    for (int i = 0; i < broj; i++)
    {
        printf("\n========================\n");

        printf("Naziv: %s\n",
            serije[i].naziv);

        printf("Zanr: %s\n",
            serije[i].zanr);

        printf("Broj sezona: %d\n",
            serije[i].brojSezona);

        printf("Pogledane sezone: %d\n",
            serije[i].pogledaneSezone);

        printf("Godina: %d\n",
            serije[i].godina);

        printf("Status: %s\n",
            statusToString(serije[i].status));

        printf("Ocjena: %.1f\n",
            serije[i].ocjena);

        printf("Platforma: %s\n",
            serije[i].platforma);
    }

    printf("\nUkupno serija: %d\n",
        ukupnoSerija);
}

/* BRISANJE */
void obrisiSeriju(Serija** serije, int* broj)
{
    if (serije == NULL ||
        *serije == NULL ||
        broj == NULL ||
        *broj <= 0)
    {
        return;
    }

    char naziv[MAX_NAZIV];

    printf("Naziv za brisanje: ");

    fgets(naziv, MAX_NAZIV, stdin);

    naziv[strcspn(naziv, "\n")] = '\0';

    for (int i = 0; i < *broj; i++)
    {
        if (strcmp((*serije)[i].naziv, naziv) == 0)
        {
            for (int j = i; j < *broj - 1; j++)
            {
                (*serije)[j] =
                    (*serije)[j + 1];
            }

            (*broj)--;
            ukupnoSerija--;

            if (*broj > 0)
            {
                Serija* temp =
                    realloc(
                        *serije,
                        (*broj) * sizeof(Serija)
                    );

                if (temp != NULL)
                {
                    *serije = temp;
                }
            }
            else
            {
                free(*serije);
                *serije = NULL;
            }

            spremiSerije(*serije, *broj);

            printf("Serija obrisana.\n");

            return;
        }
    }

    printf("Serija nije pronadena.\n");
}

/* AZURIRANJE */
void azurirajSeriju(Serija* serije, int broj)
{
    if (serije == NULL || broj <= 0)
    {
        return;
    }

    char naziv[MAX_NAZIV];

    printf("Naziv za azuriranje: ");

    fgets(naziv, MAX_NAZIV, stdin);

    naziv[strcspn(naziv, "\n")] = '\0';

    for (int i = 0; i < broj; i++)
    {
        if (strcmp(serije[i].naziv, naziv) == 0)
        {
            printf("Nova ocjena: ");

            scanf("%f",
                &serije[i].ocjena);

            getchar();

            spremiSerije(
                serije,
                broj
            );

            printf("Azurirano.\n");

            return;
        }
    }

    printf("Serija nije pronadena.\n");
}

/* USPOREDBA ZA QSORT I BSEARCH */
static int compare(
    const void* a,
    const void* b)
{
    const Serija* s1 =
        (const Serija*)a;

    const Serija* s2 =
        (const Serija*)b;

    return strcmp(
        s1->naziv,
        s2->naziv
    );
}

/* SORTIRANJE */
void sortirajSerije(
    Serija* serije,
    int broj)
{
    if (serije == NULL ||
        broj <= 1)
    {
        return;
    }

    qsort(
        serije,
        broj,
        sizeof(Serija),
        compare
    );

    printf("Sortiranje zavrseno.\n");
}

/* PRETRAZIVANJE */
void pretraziSeriju(
    Serija* serije,
    int broj)
{
    if (serije == NULL ||
        broj <= 0)
    {
        return;
    }

    char trazeniNaziv[MAX_NAZIV];

    printf("Naziv za pretragu: ");

    fgets(
        trazeniNaziv,
        MAX_NAZIV,
        stdin
    );

    trazeniNaziv[
        strcspn(
            trazeniNaziv,
            "\n")
    ] = '\0';

    Serija key = { 0 };

    strcpy(
        key.naziv,
        trazeniNaziv
    );

    Serija* pronadena =
        bsearch(
            &key,
            serije,
            broj,
            sizeof(Serija),
            compare
        );

    if (pronadena != NULL)
    {
        printf("\nPronadena serija:\n");

        printf("Naziv: %s\n",
            pronadena->naziv);

        printf("Ocjena: %.1f\n",
            pronadena->ocjena);

        printf("Platforma: %s\n",
            pronadena->platforma);
    }
    else
    {
        printf("Serija nije pronadena.\n");
    }
}

/* REKURZIJA */
void rekurzivniIspis(
    const Serija* serije,
    int broj,
    int index)
{
    if (serije == NULL)
    {
        return;
    }

    if (index >= broj)
    {
        return;
    }

    printf("%s\n",
        serije[index].naziv);

    rekurzivniIspis(
        serije,
        broj,
        index + 1
    );
}

/* REMOVE */
void obrisiDatoteku(void)
{
    if (remove(DATOTEKA) == 0)
    {
        printf("Datoteka obrisana.\n");
    }
    else
    {
        perror("remove");
    }
}

/* RENAME */
void preimenujDatoteku(void)
{
    if (rename(
        DATOTEKA,
        "backup_serije.dat"
    ) == 0)
    {
        printf("Datoteka preimenovana.\n");
    }
    else
    {
        perror("rename");
    }
}

/* STATUS -> STRING */
const char* statusToString(
    Status status)
{
    switch (status)
    {
    case PLANIRAM:
        return "Planiram";

    case GLEDAM:
        return "Gledam";

    case ZAVRSENO:
        return "Zavrseno";

    case ODUSTAO:
        return "Odustao";

    default:
        return "Nepoznato";
    }
}
