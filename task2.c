#include "task2.h"
#include "task1.h"


void creare_liste(FILE *iesire, char *matrice, char *copie_matrice, int lungime, int latime, struct memory_blocks **bloc_curent){
    int answer;
    struct memory_blocks *bloc_nou = (struct memory_blocks*)malloc(sizeof(struct memory_blocks));
    bloc_nou->next = *bloc_curent;
    *bloc_curent = bloc_nou;

    (*bloc_curent)->cap_de_lista = NULL;
    struct list **lista_intermediara = &(*bloc_curent)->cap_de_lista;

    for (int i = 0; i < latime; i++){
        for (int j = 0; j < lungime; j++){
            answer = numar_vecini(matrice, lungime, latime, j, i);

            if (answer < 2 || answer > 3) copie_matrice[i * lungime + j] = '+';
            else if (answer == 2) copie_matrice[i * lungime + j] = matrice[i * lungime + j];
            else copie_matrice[i * lungime + j] = 'X';
        }
    }

    for (int i = 0; i < latime; i++){
        for (int j = 0; j < lungime; j++){
            if (matrice[i * lungime + j] != copie_matrice[i * lungime + j]){
                *lista_intermediara = (struct list *)malloc(sizeof(struct list));
                (*lista_intermediara)->y = i;
                (*lista_intermediara)->x = j;
                (*lista_intermediara)->next = NULL;

                lista_intermediara = &(*lista_intermediara)->next;
            }
            matrice[i * lungime + j] = copie_matrice[i * lungime + j];
        }
    }
}


void afisare_recursiva(FILE *fisier_iesire, struct memory_blocks *bloc_curent, int generatie){
    if (bloc_curent == NULL) return;
    afisare_recursiva(fisier_iesire, bloc_curent->next, generatie - 1);


    fprintf(fisier_iesire, "%d", generatie);

    struct list *lista_intermediara = bloc_curent->cap_de_lista;
    while (lista_intermediara != NULL)
    {
        fprintf(fisier_iesire, " %d %d", lista_intermediara->y, lista_intermediara->x);
        lista_intermediara = lista_intermediara->next;
    }
    fprintf(fisier_iesire, "\n");
}

void eliberare_memorie(struct memory_blocks *bloc_intrare){
    if(bloc_intrare == NULL) return;
    struct memory_blocks *bloc_intermediar = bloc_intrare;
    struct memory_blocks *eliberare_bloc;

    struct list *lista_intermediara;
    struct list *eliberare_lista;

    while (bloc_intermediar != NULL)
        {
            lista_intermediara = bloc_intermediar->cap_de_lista;

            while (lista_intermediara != NULL)
            {
                eliberare_lista = lista_intermediara;
                lista_intermediara = lista_intermediara->next;
                free(eliberare_lista);
            }

            eliberare_bloc = bloc_intermediar;
            bloc_intermediar = bloc_intermediar->next;
            free(eliberare_bloc);
        }
}

void task2(FILE* fisier_iesire, char *matrice, char *copie_matrice, int lungime, int latime, int nr_generatii){
    struct memory_blocks *bloc_intrare = NULL;
    int copie_generatii = nr_generatii;

    while(nr_generatii--){
        creare_liste(fisier_iesire, matrice, copie_matrice, lungime, latime, &bloc_intrare);
    }
    afisare_recursiva(fisier_iesire, bloc_intrare, copie_generatii);
    eliberare_memorie(bloc_intrare);
}