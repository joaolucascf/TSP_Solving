#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include <math.h>

int min_dist = INT_MAX;
int matrix_size = 0;


void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void permute(int a[], int l, int **adj)
{
    int r = matrix_size - 1;
    if (l == r)
    {
        int dist = 0;
        for (int i = 0; i < r; i++)
        {
            dist += adj[a[i]][a[i + 1]];
        }
        dist += adj[a[r]][a[0]];

        if (dist < min_dist)
        {
            min_dist = dist;
        }
    }
    else
    {
        for (int i = l; i <= r; i++)
        {
            swap(&a[l], &a[i]);
            permute(a, l + 1, adj);
            swap(&a[l], &a[i]);
        }
    }
}

int main()
{
    FILE *fp;
    char filename[] = "tsp2_1248.txt.txt";
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

    int value;
    while (fscanf(fp, "%d", &value) == 1) {
        matrix_size++;
    }

    matrix_size = (int) sqrt(matrix_size);
    int vertex_list[matrix_size];

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

    permute(vertex_list, 0, adj_matrix);
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