#include <time.h>
#include "sort.h"

// Сама сортировка Шелла.
SortResult shell_sort(int arr[], int size) {
    SortResult res = { 0, 0.0 };  // Инициализация результатов.
    clock_t start = clock();     // Замер времени.

    // Алгоритм сортировки.
    for (int gap = size / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < size; i++) {
            int temp = arr[i];
            int j;
            // Сдвигаем элементы.
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                arr[j] = arr[j - gap];
                res.swaps++;  // Считаем перестановки.
            }
            arr[j] = temp;
        }
    }

    // Вычисляем время.
    res.time_mcs = ((double)(clock() - start)) / CLOCKS_PER_SEC * 1000000;
    if (res.time_mcs < 0.000001) res.time_mcs = 0.000001;  // Гарантируем не ноль.
    return res;
}