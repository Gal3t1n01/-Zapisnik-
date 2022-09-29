#ifndef UNTITLED5_HEADER_H
#define UNTITLED5_HEADER_H

#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"
#include "string.h"
#include "dataType.h"

int izbornik(char* datoteka);
void kreiranjeDatoteke(char* datoteka);
void dodajMusteriju(char* datoteka);
void* ucitavanjaMusterije(char* datoteka);
void* ucitavanjeDatoteke(char* datoteka,MUSTERIJA* poljeM);
MUSTERIJA * ispisivanjeMusterije(MUSTERIJA* poljeM);
void* pretrazivanjeMusterije(MUSTERIJA* poljeM);
void* sort(MUSTERIJA *x);
void brisanjeMusterije(MUSTERIJA** trazeniM, MUSTERIJA* poljeM, char* datoteka);
int izlazIzPrograma(MUSTERIJA* poljeM);


#endif //UNTITLED5_HEADER_H
