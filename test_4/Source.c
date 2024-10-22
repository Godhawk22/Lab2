#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

// ������� ��� ���������� �����
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

// ������� ��� ������� ���������� (������������� �������)
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

// ������� ��������� ��� qsort
int compare(const void* a, const void* b)
{
    return (*(int*)a - *(int*)b);
}

int main()
{
    SetConsoleOutputCP(1251); // ��� ������ �� �������
    SetConsoleCP(1251);       // ��� ����� �� �������

    const int count = 10000;
    int items1[10000], items2[10000], items3[10000];
    clock_t start, end;
    double shell_time, quicksort_time, qsort_time;

    // ���������� �������� �������
    for (int i = 0; i < count / 2; i++) {
        items1[i] = i + 1;
        items1[count / 2 + i] = count - i;
        items2[i] = items1[i];
        items2[count / 2 + i] = items1[count / 2 + i];
        items3[i] = items1[i];
        items3[count / 2 + i] = items1[count / 2 + i];
    }

    // ���������� �����
    start = clock();
    shell(items1, count);
    end = clock();
    shell_time = ((double)(end - start)) / CLOCKS_PER_SEC;

    // ������� ����������
    start = clock();
    qs(items2, 0, count - 1);
    end = clock();
    quicksort_time = ((double)(end - start)) / CLOCKS_PER_SEC;

    // ���������� � ������� qsort
    start = clock();
    qsort(items3, count, sizeof(int), compare);
    end = clock();
    qsort_time = ((double)(end - start)) / CLOCKS_PER_SEC;

    // ������� ����������
    printf("���������� �����: %f ������\n", shell_time);
    printf("������� ����������: %f ������\n", quicksort_time);
    printf("C��������� qsort: %f ������\n", qsort_time);

    return 0;
}
