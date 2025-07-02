#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "array.h"

// Ручной ввод чисел.
int* create_array_manual(int size) {
    int* arr = (int*)malloc(size * sizeof(int)); // Динамическое выделение памяти.
    if (!arr) return NULL;
    printf("Введите %d целых чисел:\n", size);
    for (int i = 0; i < size; i++) {
        while (scanf_s("%d", &arr[i]) != 1) {
            printf("Ошибка! Введите целое число: ");
            while (getchar() != '\n'); // Очистка буфера.
        }
    }
    return arr;
}

// Генерация случайных чисел.
int* create_array_random(int size, int min, int max) {
    if (min > max) {  // Проверка корректности диапазона
        printf("Ошибка: минимум должен быть меньше максимума!\n");
        return NULL;
    }

    int* arr = (int*)malloc(size * sizeof(int));
    if (!arr) return NULL;

    srand((unsigned int)time(NULL));
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % (max - min + 1) + min;
    }
    return arr;
}