#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

int FuncAntisymmetryc(int **matrix, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if ((matrix[i][j] == 1) && (matrix[j][i] == 1) && (i != j)){
                printf ("Matrix no antisymmetric\n");
                return 0;
            }     
        }
    }
    printf ("Matrix antisymmetric\n");
    return 1;
}

int FuncTransitivity(int **matrix, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {


            if (matrix[i][j] == 1) {
                for (int k = 0; k < n; k++) {

                    if (matrix[j][k] == 1 && matrix[i][k] != 1){
                        printf ("Matrix no transitivity\n");
                        return 0;
                    }
                }
            }
        
        
        }
    }
    printf ("Matrix transitivity\n");
    return 1;
}

int FuncReflexivity(int **matrix, int n) {
    for (int i = 0; i < n; i++) {
        if (matrix[i][i] != 1){
            printf ("Matrix no reflexivity\n");
            return 0; 
        }
    }
    printf ("Matrix reflexivity\n");
    return 1;
}

int FuncAntireflexivity(int **matrix, int n) {
    for (int i = 0; i < n; i++) {
        if (matrix[i][i] != 0){
            printf ("Matrix no antireflexivity\n");
            return 0;
        }
    }
    printf ("Matrix antireflexivity\n ");
    return 1;
}

int main() {
    int **matrix = NULL;
    int n = 0;
    int choice;
    char filename[100];
    FILE *file;

    do {
        if (matrix) {
            for (int i = 0; i < n; i++)
                free(matrix[i]);
            free(matrix);
        }

        printf("Select the matrix input method:\n");
        printf("1. Keyboard input\n");
        printf("2. Input from a file\n");
        printf("Your choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            printf("Enter the size of the matrix: ");
            scanf("%d", &n);

            matrix = (int **)malloc(n * sizeof(int *));
            for (int i = 0; i < n; i++)
                matrix[i] = (int *)malloc(n * sizeof(int));

            printf("Enter the elements of the matrix (%dx%d):\n", n, n);
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    scanf("%d", &matrix[i][j]);
                }
            }
        } else if (choice == 2) {
            
            printf("Enter the file name: ");
            scanf("%s", filename);

            file = fopen(filename, "r");
            if (file == NULL) {
                printf("Error. File can't be opened!\n");
                continue;
            }
            fscanf(file, "%d", &n);

            matrix = (int **)malloc(n * sizeof(int *));
            for (int i = 0; i < n; i++)
                matrix[i] = (int *)malloc(n * sizeof(int));

            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    fscanf(file, "%d", &matrix[i][j]);
                }
            }

            fclose(file);
            printf(".\n");
        } else continue;
        
        printf("The inputed matrix:\n");
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                printf("%d ", matrix[i][j]);
            }
            printf("\n");
        }

        int antisymmetric = FuncAntisymmetryc(matrix, n);
        int transitive = FuncTransitivity(matrix, n);
        int reflexive = FuncReflexivity(matrix, n);
        int antireflexivity = FuncAntireflexivity(matrix, n);
        printf("\nValues: %d.%d.%d.%d\n",antisymmetric, transitive, reflexive, antireflexivity);

        if ((antisymmetric == 1) && (transitive == 1)){
            printf ("the matrix is an order relation\n");
            if (reflexive == 1){
                printf ("the matrix is a non-strict order relation\n");
            }
            if (FuncAntireflexivity == 1){
                printf ("the matrix is a strict order relation\n");
            }
        }
        else printf ("the matrix is an non-order relation\n");

        printf("\nDo you want run programm again? (y/n): ");
        char repeat = getch();
        if (repeat != 'y' && repeat != 'Y') break;
    } while (1);

    if (matrix) {
        for (int i = 0; i < n; i++)
            free(matrix[i]);
        free(matrix);
    }

    getch();
    return 0;
}
//matrix1.txt