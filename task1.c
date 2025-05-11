#include "task1.h"


void afisare_matrice(FILE *fisier_iesire, const char *matrice, int lungime, int latime){
    for (int i = 0; i < latime; i++){ 
        for (int j = 0; j < lungime; j++){
            fprintf(fisier_iesire, "%c", matrice[i * lungime + j]);
        }

        fprintf(fisier_iesire, "\n");
    }

    fprintf(fisier_iesire, "\n");
}


int viu_sau_mort(const char *matrice, int lungime, int latime, int x, int y){
    if (matrice[y * lungime + x] == 'X')
        return 1;
    return 0;
}


int numar_vecini(const char *matrice, int lungime, int latime, int x, int y){
    int numar_vecini = 0;
    // next to
    if (x > 0)
        numar_vecini += viu_sau_mort(matrice, lungime, latime, x - 1, y);
    if (x < lungime - 1)
        numar_vecini += viu_sau_mort(matrice, lungime, latime, x + 1, y);
    if (y > 0)
        numar_vecini += viu_sau_mort(matrice, lungime, latime, x, y - 1);
    if (y < latime - 1)
        numar_vecini += viu_sau_mort(matrice, lungime, latime, x, y + 1);

    // diagonal to
    if (x > 0 && y > 0)
        numar_vecini += viu_sau_mort(matrice, lungime, latime, x - 1, y - 1);
    if (x < lungime - 1 && y > 0)
        numar_vecini += viu_sau_mort(matrice, lungime, latime, x + 1, y - 1);
    if (x > 0 && y < latime - 1)
        numar_vecini += viu_sau_mort(matrice, lungime, latime, x - 1, y + 1);
    if (x < lungime - 1 && y < latime - 1)
        numar_vecini += viu_sau_mort(matrice, lungime, latime, x + 1, y + 1);

    return numar_vecini;
}


void regula(char *matrice, char *copie_matrice, int lungime, int latime){
    int answer;

    for (int i = 0; i < latime; i++){
        for (int j = 0; j < lungime; j++){
            answer = numar_vecini(matrice, lungime, latime, j, i);

            if (answer < 2 || answer > 3) copie_matrice[i * lungime + j] = '+';
            else if (answer == 2) copie_matrice[i * lungime + j] = matrice[i * lungime + j];
            else copie_matrice[i * lungime + j] = 'X';
        }
    }

    for(int i = 0; i < latime; i++)
        for(int j = 0; j < lungime; j++)
            matrice[i * lungime + j] = copie_matrice[i * lungime + j];
    
}

void task1(FILE* fisier_iesire, char* matrice, char* copie_matrice, int lungime, int latime, int nr_generatii){
     afisare_matrice(fisier_iesire, matrice, lungime, latime); 
     while(nr_generatii--){
        regula(matrice, copie_matrice, lungime, latime);
        afisare_matrice(fisier_iesire, matrice, lungime, latime); 
     }
}