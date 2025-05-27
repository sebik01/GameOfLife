#ifndef TASK4
#define TASK4

#include "task2.h"

struct componenta_conexa{
    int numar_noduri;
    struct list *cap_de_lista;
    struct componenta_conexa *next;
};  

void task4(FILE *fisier_iesire, char *matrice, int lungime, int latime, int nr_generatii);

#endif