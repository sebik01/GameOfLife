#include<stdio.h>
#include<stdlib.h>

void print_grid(FILE* fisier_iesire, char *matrix, int length, int width)
{
    for(int i = 0; i < width; i++){
    for(int j = 0; j < length; j++)
        fprintf(fisier_iesire, "%c", matrix[i * length + j]);

        fprintf(fisier_iesire, "\n");
    }   


    fprintf(fisier_iesire,"\n");
}

void console_print_grid(FILE* fisier_iesire, char *matrix, int length, int width)
{
    for(int i = 0; i < width; i++){
    for(int j = 0; j < length; j++)
        printf("%c", matrix[i * length + j]);

        printf("\n");
    }   


    printf("\n");
}

int alive_or_not(char *matrix, int length, int width, int x, int y){
    if(matrix[y * length + x] == 'X') return 1;
    return 0;
}

int gamerule(char* matrix, int length, int width, int x, int y) {
	int neighbour_count = 0;
	//next to
	if (x > 0)          neighbour_count += alive_or_not(matrix, length, width, x - 1, y);
	if (x < length - 1) neighbour_count += alive_or_not(matrix, length, width, x + 1, y);
	if (y > 0)          neighbour_count += alive_or_not(matrix, length, width, x, y - 1);
	if (y < width - 1)  neighbour_count += alive_or_not(matrix, length, width, x, y + 1);

	//diagonal to
	if (x > 0 && y > 0)                  neighbour_count += alive_or_not(matrix, length, width, x - 1, y - 1);
	if (x < length - 1 && y > 0)         neighbour_count += alive_or_not(matrix, length, width, x + 1, y - 1);
	if (x > 0 && y < width - 1)          neighbour_count += alive_or_not(matrix, length, width, x - 1, y + 1);
	if (x < length - 1 && y < width - 1) neighbour_count += alive_or_not(matrix, length, width, x + 1, y + 1);


	return neighbour_count;
}


void loop_through(char* matrix, char* copy_matrix, int length, int width) {
	int answer = 0;
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < length; j++) {
			answer = gamerule(matrix, length, width, j, i);
			if (answer < 2 || answer > 3) copy_matrix[i * length + j] = '+';
			else if (answer == 2) copy_matrix[i * length + j] = matrix[i * length + j];
			else if (answer == 3) copy_matrix[i * length + j] = 'X';
		}
	}

	for (int i = 0; i < width; i++) {
		for (int j = 0; j < length; j++) {
			matrix[i * length + j] = copy_matrix[i * length + j];
		}
	}
}

int main(int argc, const char *argv[])
{
    FILE *fisier_intrare = fopen(argv[1], "rt");
    FILE *fisier_iesire = fopen(argv[2], "wt");

    if (fisier_iesire == NULL  || fisier_intrare == NULL) {
        printf("Eroare");
        return -1;
    }
    int nr_task, length, width, generatii;

    fscanf(fisier_intrare, "%d", &nr_task);
    fscanf(fisier_intrare, "%d", &width);
    fscanf(fisier_intrare, "%d", &length);
    fscanf(fisier_intrare, "%d", &generatii);

    char* matrix = (char*)calloc(length * width, sizeof(char));
	char* copy_matrix = (char*)calloc(length * width, sizeof(char));

    for(int i = 0; i < width; i++)
        for(int j = 0; j < length; j++)
        fscanf(fisier_intrare," %c", &matrix[i * length + j]);


        print_grid(fisier_iesire, matrix, length, width);
        console_print_grid(fisier_iesire, matrix, length, width);
	
	while (generatii--) {
		loop_through(matrix, copy_matrix, length, width);
        print_grid(fisier_iesire, matrix, length, width);
	}

	free(matrix);
	free(copy_matrix);
 

    fclose(fisier_intrare);
    fclose(fisier_iesire);
    return 0;
}

