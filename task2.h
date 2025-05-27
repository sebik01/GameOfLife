#ifndef TASK2
#define TASK2

#include <stdio.h>
#include <stdlib.h>

struct list{
    int x, y;
    struct list *next;
};

struct memory_blocks{
    struct list *cap_de_lista;
    struct memory_blocks *next;
};

void task2(FILE* fisier_iesire, char *matrice, char *copie_matrice, int lungime, int latime, int nr_generatii);

#endif