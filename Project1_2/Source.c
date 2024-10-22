#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>


int main(void)
{
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);
    
    int size_m[] = {100, 200, 400, 1000, 2000, 4000, 10000};
    size_t count = sizeof(size_m) / sizeof(size_m[0]);

    for (size_t m = 0; m < count; m++)
    {
        clock_t start, end;
        double cpu_time_used;
        int** a = (int**)malloc(size_m[m] * sizeof(int*));
        int** b = (int**)malloc(size_m[m] * sizeof(int*));
        int** c = (int**)malloc(size_m[m] * sizeof(int*));

        if (a == NULL || b == NULL || c == NULL) {
            printf("Ошибка выделения памяти!\n");
            return 1;
        }

        int i = 0, j = 0, r;
        int elem_c;

        for (int i = 0; i < size_m[m]; i++) {
            a[i] = (int*)malloc(size_m[m] * sizeof(int));
            b[i] = (int*)malloc(size_m[m] * sizeof(int));
            c[i] = (int*)malloc(size_m[m] * sizeof(int));
        }
        if (a[i] == NULL || b[i] == NULL || c[i] == NULL) {
            printf("Ошибка выделения памяти в строке %d!\n", i);
            return 1;
        }

        long long op_count = 0; // счётчик операций
        int cycle = size_m[m];

        srand(time(NULL));
        while (i < cycle)
        {
            j = 0;
            while (j < cycle)
            {
                a[i][j] = 1 + rand() % 100;
                j++;
                op_count++; // одна операция присвоения
            }
            i++;
        }

        srand(time(NULL));
        i = 0;
        j = 0;
        while (i < cycle)
        {
            j = 0;
            while (j < cycle)
            {
                b[i][j] = 1 + rand() % 100;
                j++;
                op_count++; // одна операция присвоения
            }
            i++;
        }
        start = clock();
        // Умножение матриц
        for (i = 0; i < cycle; i++)
        {
            for (j = 0; j < cycle; j++)
            {
                elem_c = 0;
                for (r = 0; r < cycle; r++)
                {
                    elem_c = elem_c + a[i][r] * b[r][j];
                    c[i][j] = elem_c;
                    op_count += 3; // одна операция сложения, умножения и присвоения
                }
            }
        }
        end = clock();
        for (int i = 0; i < count; i++) {
            free(a[i]);
            free(b[i]);
            free(c[i]);
        }
        free(a);
        free(b);
        free(c);

        cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

        printf("Время выполнения программы: %f секунд\n", cpu_time_used);
        printf("Кол-во операций: %lld\n", op_count);
    }
    return 0;
}