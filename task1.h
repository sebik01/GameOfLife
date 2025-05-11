#ifndef TASK1
#define TASK1
#include <stdio.h>

void afisare_matrice(FILE *fisier_iesire, const char *matrice, int lungime, int latime);
int viu_sau_mort(const char *matrice, int lungime, int latime, int x, int y);
int numar_vecini(const char *matrice, int lungime, int latime, int x, int y);
void regula(char *matrice, char *copie_matrice, int lungime, int latime);
void task1(FILE* fisier_iesire, char *matrice, char *copie_matrice, int lungime, int latime, int nr_generatii);


#endif