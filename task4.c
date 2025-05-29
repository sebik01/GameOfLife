#include "task1.h"
#include "task2.h"
#include "task3.h"
#include "task4.h"


void adauga_conex(char *matrice, char *parcurs, int lungime, int latime, int x, int y, int *numar_noduri, struct list **cap){

    if(!viu_sau_mort(matrice, lungime, latime, x, y) || parcurs[y * lungime + x] == 1) return;


    parcurs[y * lungime + x] = 1;

    struct list *nou = (struct list*)malloc(sizeof(struct list));
    nou->x = x;
    nou->y = y;
    nou->next = *cap;
    *cap = nou;

    (*numar_noduri)++; //inca un nod babyyyy


    if (x > 0)                             adauga_conex(matrice, parcurs, lungime, latime, x - 1, y, numar_noduri, cap);
    if (x < lungime - 1)                   adauga_conex(matrice, parcurs, lungime, latime, x + 1, y, numar_noduri, cap);
    if (y > 0)                             adauga_conex(matrice, parcurs, lungime, latime, x, y - 1, numar_noduri, cap);
    if (y < latime - 1)                    adauga_conex(matrice, parcurs, lungime, latime, x, y + 1, numar_noduri, cap);

    if (x > 0 && y > 0)                    adauga_conex(matrice, parcurs, lungime, latime, x - 1, y - 1, numar_noduri, cap);
    if (x < lungime - 1 && y > 0)          adauga_conex(matrice, parcurs, lungime, latime, x + 1, y - 1, numar_noduri, cap);
    if (x > 0 && y < latime - 1)           adauga_conex(matrice, parcurs, lungime, latime, x - 1, y + 1, numar_noduri, cap);
    if (x < lungime - 1 && y < latime - 1) adauga_conex(matrice, parcurs, lungime, latime, x + 1, y + 1, numar_noduri, cap);
   
}


//ordonez celulele pentru ca sa pot sa fac un loop mai usor prin lista, cu potentiale radacini, 
//si sa ma asigur ca primul drum hamiltonian pe care il gasesc este cel care se incadreaza corespunzator cerintei
//ca drumul pleaca dintr-un nod cu y (respectiv x) cele mai mici
void ordonare_celule(struct componenta_conexa *insula){
    struct list* lista1 = insula->cap_de_lista;
    struct list* lista2;

    int xaux, yaux;

    while(lista1 != NULL){
        lista2 = lista1->next;

        while(lista2 != NULL){
            if(lista1->y > lista2->y){
                yaux = lista1->y;
                lista1->y = lista2->y;
                lista2->y = yaux;

                xaux = lista1->x;
                lista1->x = lista2->x;
                lista2->x = xaux;
            }
            else if (lista1->y == lista2->y && (lista1->x > lista2->x)){
                xaux = lista1->x;
                lista1->x = lista2->x;
                lista2->x = xaux;
            }

            lista2 = lista2->next;
        }
        lista1 = lista1->next;
    }
}


void separa_insulele(char *matrice, char *parcurs, int lungime, int latime, struct componenta_conexa **iterator){
    for(int i = 0; i < latime; i++){
        for(int j = 0; j < lungime; j++){
            if(parcurs[i * lungime + j] == 0 && viu_sau_mort(matrice, lungime, latime, j, i)){
            *iterator = (struct componenta_conexa*)malloc(sizeof(struct componenta_conexa));

            (*iterator)->numar_noduri = 0;
            (*iterator)->cap_de_lista = NULL;
            (*iterator)->next = NULL;

            adauga_conex(matrice, parcurs, lungime, latime, j, i, &(*iterator)->numar_noduri, &(*iterator)->cap_de_lista);
            ordonare_celule(*iterator);

            iterator = &(*iterator)->next;
            }
        }
    }
}

void cauta_drum_hamiltonian(char *matrice, char *parcurs, int lungime, int latime, int x, int y, int nr_noduri, 
                            int *lungime_drum, int lungime_maxima, int* pozitii){
    if(!viu_sau_mort(matrice, lungime, latime, x, y) || parcurs[y * lungime + x] == 1) return;

    int step = *lungime_drum;
    (*lungime_drum)++;
    parcurs[y * lungime + x] = 1;

//==========================
    if (x > 0 && y > 0 && *lungime_drum != nr_noduri)                    
    cauta_drum_hamiltonian(matrice, parcurs, lungime, latime, x - 1, y - 1, nr_noduri, lungime_drum, lungime_maxima, pozitii);
   
    if (y > 0 && *lungime_drum != nr_noduri)                             
    cauta_drum_hamiltonian(matrice, parcurs, lungime, latime, x, y - 1, nr_noduri, lungime_drum, lungime_maxima, pozitii);
   
    if (x < lungime - 1 && y > 0 && *lungime_drum != nr_noduri)          
    cauta_drum_hamiltonian(matrice, parcurs, lungime, latime, x + 1, y - 1, nr_noduri, lungime_drum, lungime_maxima, pozitii);
   
    if (x > 0 && *lungime_drum != nr_noduri)                             
    cauta_drum_hamiltonian(matrice, parcurs, lungime, latime, x - 1, y, nr_noduri, lungime_drum, lungime_maxima, pozitii);
  
    if (x < lungime - 1 && *lungime_drum != nr_noduri)                   
    cauta_drum_hamiltonian(matrice, parcurs, lungime, latime, x + 1, y, nr_noduri, lungime_drum, lungime_maxima, pozitii);
   
    if (x > 0 && y < latime - 1 && *lungime_drum != nr_noduri)          
    cauta_drum_hamiltonian(matrice, parcurs, lungime, latime, x - 1, y + 1, nr_noduri, lungime_drum, lungime_maxima, pozitii);
    
    if (y < latime - 1 && *lungime_drum != nr_noduri)                    
    cauta_drum_hamiltonian(matrice, parcurs, lungime, latime, x, y + 1, nr_noduri, lungime_drum, lungime_maxima, pozitii);
    
    if (x < lungime - 1 && y < latime - 1 && *lungime_drum != nr_noduri) 
    cauta_drum_hamiltonian(matrice, parcurs, lungime, latime, x + 1, y + 1, nr_noduri, lungime_drum, lungime_maxima, pozitii);
//==========================
//le ia in urmatoarea ordine
//  1 2 3
//  4   5
//  6 7 8
//pentru ca regula specifica sa le ia de la cea mai mica linie (si coloana)

//daca s-a gasit un drum hamiltonian, atunci lungimea drumului ar fi egala cu numarul de noduri si n-as avea
//de ce sa continui sa caut alte cai de drum
    if(*lungime_drum == nr_noduri && *lungime_drum > lungime_maxima) {
        pozitii[2*step] = x;
        pozitii[2*step + 1] = y;
        return;
    }

    (*lungime_drum)--;
    parcurs[y * lungime + x] = 0;
}


void alege_drum(FILE *fisier_iesire, char *matrice, char *parcurs, int lungime, int latime, struct componenta_conexa* insula_curenta){
    int lungime_maxima = 0;
    int lungime_temp = 0;

    int *pozitii = NULL;
    int max_size = 0;


    struct list *temp;
    struct componenta_conexa *iterator = insula_curenta;

//vreau sa aloc un singur bloc de memorie in care sa stochez drumul ce urmeaza sa-l gasesc, deci trebuie sa-i stiu 
//posibila maxima dimensiune
//
//desigur, un drum valid poate sa aiba mai putine noduri decat o componenta conexa cu cele mai multe noduri
//dar daca nu are?

    while(iterator != NULL){
        if(max_size < iterator->numar_noduri) max_size = iterator->numar_noduri;
        iterator = iterator->next;
    }
    pozitii = (int *)malloc(2 * max_size * sizeof(int));

//2 * pentru ca stochez perechi de x si y, adica 2 numere;
    

    for(int i = 0; i < latime; i++)
        for(int j = 0; j < lungime; j++)
            parcurs[i * lungime + j] = 0;

    while(insula_curenta != NULL){
        temp = insula_curenta->cap_de_lista;
        
        while(temp != NULL){
            lungime_temp = 0;
            cauta_drum_hamiltonian(matrice, parcurs, lungime, latime, temp->x, temp->y, insula_curenta->numar_noduri,
                                   &lungime_temp, lungime_maxima, pozitii);
            
            if(lungime_temp > lungime_maxima)
            lungime_maxima = lungime_temp;

            if(lungime_temp == insula_curenta->numar_noduri)
            break;
            
            //dupa terminarea functiei, daca se gaseste drum valid (si primul gasit) atunci lungime_temp nu va iesi 0
            //daca nu, cautam alt drum care incepe din urmatorul nod, in ordine!
            temp = temp->next;
        }
        insula_curenta = insula_curenta->next;
        
    
        if(lungime_maxima == max_size) break;
        //daca se intampla ca drumul pe care-l gasesc sa fie cel pe care il stiu ca e de lungime maxima, ma opresc aici
    }
    if(lungime_maxima > 0){
    fprintf(fisier_iesire, "%d\n", lungime_maxima - 1); 
    //drumul e nr de noduri - 1
    //insa eu creez identitatea de existenta a unui drum raportat la nr de noduri

    for(int i = 0; i < lungime_maxima; i++){
        fprintf(fisier_iesire, "(%d,%d)", pozitii[2 * i + 1], pozitii[2 * i]);
        if(i < lungime_maxima - 1) fprintf(fisier_iesire, " ");
    }
    fprintf(fisier_iesire, "\n");
    }
    else fprintf(fisier_iesire, "-1\n");

    free(pozitii);
}

void eliberare_memorie_grafuri(struct componenta_conexa* insula) {
    struct list* curent;

    
    while(insula != NULL){
    curent = insula->cap_de_lista;
        
    while (curent != NULL) {
        struct list *temp = curent;
        curent = curent->next;
        free(temp);
    }
    struct componenta_conexa *temp = insula;
    insula = insula->next;
    free(temp);
}
}

void cauta_drumuri_arbore(FILE* fisier_iesire, struct binary_data_tree *nod_curent, char* matrice_precedenta, int lungime, int latime){
    if(nod_curent == NULL) return;

    char *matrice_curenta = (char *)calloc(lungime * latime, sizeof(char));
    char *parcurs = (char *)calloc(lungime * latime, sizeof(char));


    struct componenta_conexa *insule = NULL;
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

    separa_insulele(matrice_curenta, parcurs, lungime, latime, &insule);
    alege_drum(fisier_iesire, matrice_curenta, parcurs, lungime, latime, insule);

    cauta_drumuri_arbore(fisier_iesire, nod_curent->left, matrice_curenta, lungime, latime);
    cauta_drumuri_arbore(fisier_iesire, nod_curent->right, matrice_curenta, lungime, latime);



    eliberare_memorie_grafuri(insule);
    free(parcurs);
    free(matrice_curenta);
}


void task4(FILE *fisier_iesire, char *matrice, int lungime, int latime, int nr_generatii){
    
    char *parcurs = (char*)calloc(lungime * latime, sizeof(char));
    struct binary_data_tree *root = creare_arbore(matrice, 0, lungime, latime, nr_generatii);

    cauta_drumuri_arbore(fisier_iesire, root, matrice, lungime, latime);

    eliberare_arbore(root);
    free(parcurs);
}
