#include "header.h"
//brojMusterija ukupan broj koliko ima upisanih
int brojMusterija = 0;
//poljeM array elemenata
static MUSTERIJA* poljeM = NULL;

int izbornik(char* datoteka) {
    printf("\nOdaberite jednu od ponudenih opcija:\n");
    printf("\t\t\tOpcija 1: Kreiranje datoteke.\n");
    printf("\t\t\tOpcija 2: Dodavanje musterije.\n");
    printf("\t\t\tOpcija 3: Ispisivanje musterija.\n");
    printf("\t\t\tOpcija 4: Pretrazivanje musterija.\n");
    printf("\t\t\tOpcija 5: Brisanje musterije.\n");
    printf("\t\t\tOpcija 6: Sortiranje musterija.\n");
    printf("\t\t\tOpcija 7: Izlaz iz programa.\n");
    printf("======================================\
======================================\n");

    int uvijet = 0;
    MUSTERIJA *arrayM;

    static MUSTERIJA* pronadjenaM = NULL;

    scanf("%d", &uvijet);

    switch (uvijet) {
        case 1:
            kreiranjeDatoteke(datoteka);
            break;
        case 2:
            dodajMusteriju(datoteka);
            arrayM = ucitavanjeDatoteke(datoteka, poljeM);
            ispisivanjeMusterije(arrayM);
            break;
        case 3:
            arrayM = ucitavanjeDatoteke(datoteka, poljeM);
            ispisivanjeMusterije(arrayM);
            break;
        case 4:
            arrayM = ucitavanjeDatoteke(datoteka, poljeM);
            pronadjenaM = (MUSTERIJA*) pretrazivanjeMusterije(arrayM);
            break;
        case 5:
            arrayM = ucitavanjeDatoteke(datoteka, poljeM);
            ispisivanjeMusterije(arrayM);
            pronadjenaM = (MUSTERIJA*)pretrazivanjeMusterije(arrayM);
            brisanjeMusterije(&pronadjenaM, arrayM, datoteka);
            break;
        case 6:
            sort(arrayM);
            break;
        case 7:
            uvijet = izlazIzPrograma(poljeM);
            break;
        default:
            uvijet = 0;
    }
    return uvijet;
}

void kreiranjeDatoteke(char* datoteka){
    FILE* file = fopen(datoteka, "wb");
    if(file == NULL){
        perror("Kreiranje datoteke neuspjelo");
        exit(EXIT_FAILURE);
    }
    fwrite(&brojMusterija, sizeof(int), 1, file);
    fclose(file);
}

void dodajMusteriju(char* datoteka) {
    FILE* file = fopen(datoteka, "rb+");

    if (file == NULL) {
        perror("Error");
        exit(EXIT_FAILURE);
    }

    fread(&brojMusterija, sizeof(int), 1, file);
    printf("Broj musterije: %d\n", brojMusterija);
    MUSTERIJA temp = { 0 };

    temp.id = brojMusterija;

    getchar();
    printf("Unesite ime musterije!\n");
    scanf("%19s", temp.ime);

    getchar();
    printf("Unesite prezime musterije!\n");
    scanf("%19s", temp.prezime);

    getchar();
    printf("Unesite vrstu usluge \nFeniranje\nPeglanje\nPramenovi\n");
    scanf("%s", temp.usluga);

    printf("Datum termina\n");
    scanf("%d/%d/%d", &temp.dan, &temp.mjesec, &temp.godina);

    fseek(file, sizeof(MUSTERIJA) * brojMusterija, SEEK_CUR);
    fwrite(&temp, sizeof(MUSTERIJA), 1, file);
    rewind(file);

    brojMusterija++;

    fwrite(&brojMusterija, sizeof(int), 1, file);
    fclose(file);
}

void* ucitavanjaMusterije(char* datoteka){

    FILE* file = fopen(datoteka, "rb");
    if(file == NULL){
        perror("Error");
        return NULL;
    }

    fread(&brojMusterija, sizeof(int), 1, file);
    printf("Broj musterije: %d\n", brojMusterija);
    MUSTERIJA* poljeM = (MUSTERIJA *)calloc(brojMusterija, sizeof(MUSTERIJA));
    if (poljeM == NULL) {
        perror("Error");
        return NULL;
//exit(EXIT_FAILURE);
    }
    fread(poljeM, sizeof(MUSTERIJA), brojMusterija, file);
    return poljeM;
}

void* ucitavanjeDatoteke(char* datoteka,MUSTERIJA* poljeM){

    if (poljeM != NULL) {
        free(poljeM);
        poljeM = NULL;
    }
    poljeM = (MUSTERIJA *) ucitavanjaMusterije(datoteka);
    if (poljeM == NULL) {
        exit(EXIT_FAILURE);
    }
    return poljeM;
}

MUSTERIJA * ispisivanjeMusterije(MUSTERIJA* poljeM) {
    if (poljeM == NULL) {
        printf("Polje musterija je prazno!\n");
        return 0;
    }
    int i;
    for (i = 0; i < brojMusterija; i++)
    {
        printf("Broj musterije %d\tID: %d\tIme: %s\tPrezime: %s\tVrsta usluge: %s\tDatum termina: %d/%d/%d\n",
               i + 1,
               (poljeM + i)->id,
               (poljeM + i)->ime,
               (poljeM + i)->prezime,
               (poljeM + i)->usluga,
               (poljeM + i)->dan,
               (poljeM + i)->mjesec,
               (poljeM + i)->godina);
    }
}

void* pretrazivanjeMusterije(MUSTERIJA* const poljeM) {

    if (poljeM == NULL) {
        printf("Polja musterija su prazna!\n");
        return NULL;
    }

    int i;
    char trazenoIme[20] = { '\0' };

    printf("Trazeni kriterij za pronalazak musterija (po imenu).\n");
    getchar();
    scanf("%19s", trazenoIme);
    for (i = 0; i < brojMusterija; i++)
    {
        if (!strcmp(trazenoIme, (poljeM + i)->ime)) {
            printf("Musterija je nadjena!");
            return (poljeM + i);
        }
    }
    if(strcmp(trazenoIme, (poljeM + i)->ime)){
        printf("Musterija nije nadjena!");
        return (poljeM + i);
    }
}

void* sort(MUSTERIJA *x)
{
    int i, j;
    for (i = 0; i < brojMusterija-1; i++)
    {
        for (j = 0; j < brojMusterija-1-i; j++)
        {
            if (strcmp (x[j].ime, x[j + 1].ime) > 0)
            {
                MUSTERIJA temp = x[j+1];
                x[j+1] = x[j];
                x[j] = temp;
            }
        }
    }

    printf ("Sortirano\n");
    for (i = 0; i < brojMusterija; i++)
    {
        printf ("Ime: %s\tPrezime: %s\tDatum: %s\tVrsta usluge: %s\tDatum termina: %d/%d/%d\n", x[i].ime,
                x[i].prezime, x[i].datum, x[i].usluga, x[i].dan, x[i].mjesec, x[i].godina);
    }
}

void brisanjeMusterije(MUSTERIJA** trazeniM, MUSTERIJA* poljeM, char* datoteka) {

    FILE* file = fopen(datoteka, "wb");

    if (datoteka == NULL) {
        perror("Brisanje neuspjelo.");
        exit(EXIT_FAILURE);
    }

    fseek(file, sizeof(int), SEEK_SET);

    int i;
    int noviBrojacP = 0;

    for (i = 0; i < brojMusterija; i++)
    {
        if (*trazeniM != (poljeM + i)) {
            fwrite((poljeM + i), sizeof(MUSTERIJA), 1, file);
            noviBrojacP++;
        }
    }

    rewind(file);
    fwrite(&noviBrojacP, sizeof(int), 1, file);
    fclose(file);
    printf("\nMusterija je obrisana!\n");
    *trazeniM = NULL;
}

int izlazIzPrograma(MUSTERIJA* poljeM) {
    free(poljeM);
    return 0;
}