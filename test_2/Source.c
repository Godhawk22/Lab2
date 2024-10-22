#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>

// Реализация сортировки Шелла
void shell(int* items, int count)
{
    int i, j, gap, k;
    int x, a[5];

    a[0] = 9; a[1] = 5; a[2] = 3; a[3] = 2; a[4] = 1;

    for (k = 0; k < 5; k++) {
        gap = a[k];
        for (i = gap; i < count; ++i) {
            x = items[i];
            for (j = i - gap; (j >= 0) && (items[j] > x); j -= gap)
                items[j + gap] = items[j];
            items[j + gap] = x;
        }
    }
}

// Реализация быстрой сортировки
void qs(int* items, int left, int right)
{
    int i, j;
    int x, y;

    i = left;
    j = right;
    x = items[(left + right) / 2];

    do {
        while ((items[i] < x) && (i < right)) i++;
        while ((x < items[j]) && (j > left)) j--;

        if (i <= j) {
            y = items[i];
            items[i] = items[j];
            items[j] = y;
            i++;
            j--;
        }
    } while (i <= j);

    if (left < j) qs(items, left, j);
    if (i < right) qs(items, i, right);
}

// Функция сравнения для qsort
int compare(const void* a, const void* b)
{
    return (*(int*)a - *(int*)b);
}

int main()
{
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    const int count = 10000;
    const int repeat = 100;   // Количество повторений сортировки для точности
    int items1[10000], items2[10000], items3[10000];
    clock_t start, end;
    double shell_time = 0, quicksort_time = 0, qsort_time = 0;

    // Заполняем массивы данными
    for (int i = 0; i < count; i++) {
        items1[i] = i;
        items2[i] = items1[i];
        items3[i] = items1[i];
    }

    // Повторяем сортировку несколько раз для усреднения времени
    for (int r = 0; r < repeat; r++) {
        // Сортировка Шелла
        start = clock();
        shell(items1, count);
        end = clock();
        shell_time += ((double)(end - start)) / CLOCKS_PER_SEC;

        // Обновляем массивы для следующей сортировки
        for (int i = 0; i < count; i++) {
            items1[i] = i;
            items2[i] = i;
            items3[i] = i;
        }

        // Ручная быстрая сортировка
        start = clock();
        qs(items2, 0, count - 1);
        end = clock();
        quicksort_time += ((double)(end - start)) / CLOCKS_PER_SEC;

        // Обновляем массивы для следующей сортировки
        for (int i = 0; i < count; i++) {
            items1[i] = i;
            items2[i] = i;
            items3[i] = i;
        }

        // Стандартная сортировка qsort
        start = clock();
        qsort(items3, count, sizeof(int), compare);
        end = clock();
        qsort_time += ((double)(end - start)) / CLOCKS_PER_SEC;
    }

    // Усредняем время выполнения для каждой сортировки
    shell_time /= repeat;
    quicksort_time /= repeat;
    qsort_time /= repeat;

    // Выводим результаты
    printf("Сортировка Шелла: %f секунд\n", shell_time);
    printf("Быстрая сортировка: %f секунд\n", quicksort_time);
    printf("Cортировка qsort: %f секунд\n", qsort_time);

    return 0;
}
