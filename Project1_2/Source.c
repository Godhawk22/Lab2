#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>

#define SIZE 1000
int main(void)
{
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);

    clock_t start, end;
    double cpu_time_used;
    int** a = (int**)malloc(SIZE * sizeof(int*));
    int** b = (int**)malloc(SIZE * sizeof(int*));
    int** c = (int**)malloc(SIZE * sizeof(int*));
    
    if (a == NULL || b == NULL || c == NULL) {
        printf("Ошибка выделения памяти!\n");
        return 1;
    }
    int i = 0, j = 0, r;
    int helping = 1000;
    int elem_c;
    for (int i = 0; i < SIZE; i++) {
        a[i] = (int*)malloc(SIZE * sizeof(int));
        b[i] = (int*)malloc(SIZE * sizeof(int));
        c[i] = (int*)malloc(SIZE * sizeof(int));
    }
    if (a[i] == NULL || b[i] == NULL || c[i] == NULL) {
        printf("Ошибка выделения памяти в строке %d!\n", i);
        return 1;
    }

    long long op_count = 0; // счётчик операций
    start = clock();
    srand(time(NULL));
    while (i < helping)
    {
        j = 0;
        while (j < helping)
        {
            a[i][j] = rand() % 100 + 1;
            j++;
            op_count++; // одна операция присвоения
        }
        i++;
    }

    srand(time(NULL));
    i = 0;
    j = 0;
    while (i < helping)
    {
        j = 0;
        while (j < helping)
        {
            b[i][j] = rand() % 100 + 1;
            j++;
            op_count++; // одна операция присвоения
        }
        i++;
    }

    // Умножение матриц
    for (i = 0; i < helping; i++)
    {
        for (j = 0; j < helping; j++)
        {
            elem_c = 0;
            for (r = 0; r < helping; r++)
            {
                elem_c = elem_c + a[i][r] * b[r][j];
                c[i][j] = elem_c;
                op_count += 3; // одна операция сложения, умножения и присвоения
            }
        }
    }

    for (int i = 0; i < SIZE; i++) {
        free(a[i]);
        free(b[i]);
        free(c[i]);
    }
    free(a);
    free(b);
    free(c);

    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("Время выполнения программы: %f секунд\n", cpu_time_used);
    printf("Кол-во операций: %lld\n", op_count);

    return 0;
}