#include <stdio.h>
#include <stdlib.h>

#include "task1.h"
#include "task2.h"
#include "task3.h"


void copiere_matrice(char *matrice, const char *matrice_sablon, int lungime, int latime){
    for(int i = 0; i < latime; i++){
        for(int j = 0; j < lungime; j++){
            matrice[i * lungime + j] = matrice_sablon[i * lungime + j];
        }
    }
}

int main(int argc, const char *argv[])
{
    // initializare resurse
    FILE *fisier_intrare = fopen(argv[1], "rt");
    FILE *fisier_iesire = fopen(argv[2], "wt");

    if (fisier_iesire == NULL || fisier_intrare == NULL)
    {
        printf("Eroare");
        return -1;
    }
    int nr_task, lungime, latime, nr_generatii;

    fscanf(fisier_intrare, "%d", &nr_task);
    fscanf(fisier_intrare, "%d", &latime);
    fscanf(fisier_intrare, "%d", &lungime);
    fscanf(fisier_intrare, "%d", &nr_generatii);

    char *matrice_sablon = (char *)calloc(lungime * latime, sizeof(char));
    char *matrice = (char *)calloc(lungime * latime, sizeof(char));
    char *copie_matrice = (char *)calloc(lungime * latime, sizeof(char));
    
    for(int i = 0; i < latime; i++)
        for(int j = 0; j < lungime; j++)
        fscanf(fisier_intrare," %c", &matrice_sablon[i * lungime + j]);

    
    
    copiere_matrice(matrice, matrice_sablon, lungime, latime);
    if(nr_task == 1) task1(fisier_iesire, matrice, copie_matrice, lungime, latime, nr_generatii);

    copiere_matrice(matrice, matrice_sablon, lungime, latime);
    if(nr_task == 2) task2(fisier_iesire, matrice, copie_matrice, lungime, latime, nr_generatii);

    copiere_matrice(matrice, matrice_sablon, lungime, latime);
    if(nr_task == 3) task3(fisier_iesire, matrice, lungime, latime, nr_generatii);

        // Eliberarea resurselor
        free(matrice_sablon);
        free(matrice);
        free(copie_matrice);

        fclose(fisier_intrare);
        fclose(fisier_iesire);
        return 0;
    
}
