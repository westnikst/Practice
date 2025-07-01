#ifndef SORT_H
#define SORT_H

// структура для хранения результатов сортировки (время, количество итерраций)
typedef struct { // typedef для имени структуры
    int swaps;      // количество перестановок
    double time_mcs; // время выполнения
} SortResult; //имя структуры

SortResult shell_sort(int arr[], int size);  // сортировка Шелла

#endif