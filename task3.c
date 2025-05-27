#include <stdio.h>

#include "task3.h"
#include "task2.h"
#include "task1.h"

struct binary_data_tree *creare_arbore(char *matrice_precedenta, int regula, int lungime, int latime, int generatie)
{
    if (generatie < 0) return NULL;
    char *matrice_curenta = (char *)calloc(lungime * latime, sizeof(char));
    int answer;

    struct binary_data_tree *nod_nou = (struct binary_data_tree *)malloc(sizeof(struct binary_data_tree));
    nod_nou->cap_de_lista = NULL;

    struct list **lista_intermediara = &nod_nou->cap_de_lista;

    // determinarea regulii dupa care vom face noua matrice
    if (regula == REGULA_CLASICA)
    {
        for (int i = 0; i < latime; i++){
            for (int j = 0; j < lungime; j++){
                answer = numar_vecini(matrice_precedenta, lungime, latime, j, i);

                if (answer < 2 || answer > 3) matrice_curenta[i * lungime + j] = '+';
                else if (answer == 2) matrice_curenta[i * lungime + j] = matrice_precedenta[i * lungime + j];
                else matrice_curenta[i * lungime + j] = 'X';
            }
        }
    }
    else if (regula == REGULA_NOUA)
    {
        for (int i = 0; i < latime; i++){
            for (int j = 0; j < lungime; j++){
                answer = numar_vecini(matrice_precedenta, lungime, latime, j, i);
                if (answer == 2) matrice_curenta[i * lungime + j] = 'X';
                else matrice_curenta[i * lungime + j] = matrice_precedenta[i * lungime + j];
            }
        }
    }
    else if (regula == 0)
    for (int i = 0; i < latime; i++) {
        for (int j = 0; j < lungime; j++){
            matrice_curenta[i * lungime + j] = matrice_precedenta[i * lungime + j];
            matrice_precedenta[i * lungime + j] = '+';
        }
    }
    
    // crearea listei
    for (int i = 0; i < latime; i++)
    {
        for (int j = 0; j < lungime; j++)
        {
            if (matrice_precedenta[i * lungime + j] != matrice_curenta[i * lungime + j])
            {
                *lista_intermediara = (struct list *)malloc(sizeof(struct list));
                (*lista_intermediara)->y = i;
                (*lista_intermediara)->x = j;
                (*lista_intermediara)->next = NULL;
                lista_intermediara = &(*lista_intermediara)->next;
            }
        }
    }

    nod_nou->left = creare_arbore(matrice_curenta, REGULA_NOUA, lungime, latime, generatie - 1);
    nod_nou->right = creare_arbore(matrice_curenta, REGULA_CLASICA, lungime, latime, generatie - 1);

    free(matrice_curenta);
    free(lista_intermediara);

    return nod_nou;
}


void afiseaza_arbore(FILE *fisier_iesire, struct binary_data_tree *nod_curent, const char *matrice_precedenta, int lungime, int latime)
{
    if (nod_curent == NULL) return;

    char *matrice_curenta = (char *)calloc(lungime * latime, sizeof(char));
    struct list *lista_intermediara = nod_curent->cap_de_lista;

    for (int i = 0; i < latime; i++)
    {
        for (int j = 0; j < lungime; j++)
        {
            matrice_curenta[i * lungime + j] = matrice_precedenta[i * lungime + j];
        }
    }

    int x, y;

    while (lista_intermediara != NULL)
    {
        x = lista_intermediara->x;
        y = lista_intermediara->y;
        if (matrice_curenta[y * lungime + x] == '+')
            matrice_curenta[y * lungime + x] = 'X';
        else
            matrice_curenta[y * lungime + x] = '+';

        lista_intermediara = lista_intermediara->next;
    }
    
    for (int i = 0; i < latime; i++)
    {
        for (int j = 0; j < lungime; j++)
        {
            fprintf(fisier_iesire, "%c", matrice_curenta[i * lungime + j]);
        }
        fprintf(fisier_iesire, "\n");
    }

    fprintf(fisier_iesire, "\n");

    afiseaza_arbore(fisier_iesire, nod_curent->left, matrice_curenta, lungime, latime);
    afiseaza_arbore(fisier_iesire, nod_curent->right, matrice_curenta, lungime, latime);

    free(matrice_curenta);
}

void eliberare_arbore(struct binary_data_tree *radacina){
    if(radacina->left != NULL) eliberare_arbore(radacina->left);
    if(radacina->right != NULL) eliberare_arbore(radacina->right);

    struct list *lista_intermediara = radacina->cap_de_lista;
    struct list *eliberare_lista;
    

    while (lista_intermediara != NULL)
    {
        eliberare_lista = lista_intermediara;
        lista_intermediara = lista_intermediara->next;
        free(eliberare_lista);
    }
    free(radacina);
}


void task3(FILE* fisier_iesire, char *matrice, int lungime, int latime, int nr_generatii){
    struct binary_data_tree *radacina = creare_arbore(matrice, 0, lungime, latime, nr_generatii);

    afiseaza_arbore(fisier_iesire, radacina, matrice, lungime, latime);
    eliberare_arbore(radacina);
}