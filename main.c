#include <stdio.h>
#include "header.h"

int main() {
    int uvijet = 1;
    char datoteka[20] = { '\0' };
    printf("Unesite ime datoteke s kojom se treba raditi!\n");
    scanf("%19s", datoteka);
    while (uvijet) {
        uvijet = izbornik(datoteka);
    }
    printf("Zavrsetak programa!\n");
    return 0;
}
