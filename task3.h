#ifndef TASK3
#define TASK3

#include "task1.h"
#include <stdlib.h>

#define REGULA_CLASICA 1
#define REGULA_NOUA 2


struct binary_data_tree{
    struct list *cap_de_lista;
    struct binary_data_tree *left;
    struct binary_data_tree *right;
};

struct binary_data_tree *creare_arbore(char *matrice_precedenta, int regula, int lungime, int latime, int generatie);
void eliberare_arbore(struct binary_data_tree *radacina);
void task3(FILE* fisier_iesire, char *matrice, int lungime, int latime, int nr_generatii);

#endif