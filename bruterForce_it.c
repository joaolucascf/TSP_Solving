#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include <math.h>

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int main()
{
    FILE *fp;
    char filename[] = "tsp2_1248.txt";
    int **adj_matrix;
    int i, j;
    clock_t start_time, end_time;
    double cpu_time_used;

    start_time = clock();

    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        exit(1);
    }

    int matrix_size = 0;
    int value;
    while (fscanf(fp, "%d", &value) == 1) {
        matrix_size++;
    }

    matrix_size = (int) sqrt(matrix_size);
    int vertex_list[matrix_size];
    int min_dist = INT_MAX;

    adj_matrix = (int **) malloc(matrix_size * sizeof(int *));
    for (i = 0; i < matrix_size; i++) {
        adj_matrix[i] = (int *) malloc(matrix_size * sizeof(int));
    }

    rewind(fp);
    for (i = 0; i < matrix_size; i++) {
        for (j = 0; j < matrix_size; j++) {
            fscanf(fp, "%d", &adj_matrix[i][j]);
        }
    }
    fclose(fp);

    printf("Matriz de adjacência:\n");
    for (i = 0; i < matrix_size; i++) {
        for (j = 0; j < matrix_size; j++) {
            printf("%d ", adj_matrix[i][j]);
        }
        printf("\n");
    }

    for (int i = 0; i < matrix_size; i++)
    {
        vertex_list[i] = i;
    }

    // Iterative permutation algorithm
    int c[matrix_size];
    for (i = 0; i < matrix_size; i++) {
        c[i] = 0;
    }

    i = 0;
    while (i < matrix_size) {
        if (c[i] < i) {
            if (i % 2 == 0) {
                swap(&vertex_list[0], &vertex_list[i]);
            } else {
                swap(&vertex_list[c[i]], &vertex_list[i]);
            }
            int dist = 0;
            for (int j = 0; j < matrix_size - 1; j++)
            {
                dist += adj_matrix[vertex_list[j]][vertex_list[j+1]];
            }
            dist += adj_matrix[vertex_list[matrix_size-1]][vertex_list[0]];

            if (dist < min_dist)
            {
                min_dist = dist;
            }
            c[i]++;
            i = 0;
        } else {
            c[i] = 0;
            i++;
        }
    }

    end_time = clock();
    cpu_time_used = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;

    printf("Distância mínima: %d\n", min_dist);
    printf("Tempo de execução: %lf\n", cpu_time_used);

    for (i = 0; i < matrix_size; i++)
    {
        free(adj_matrix[i]);
    }

    free(adj_matrix);

    system("pause");

    return 0;
}
