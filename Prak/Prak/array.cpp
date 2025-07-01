#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "array.h"

// ручной ввод чисел
int* create_array_manual(int size) {
    int* arr = (int*)malloc(size * sizeof(int)); //динамическое выделение пам€ти
    printf("¬ведите %d целых чисел:\n", size);
    for (int i = 0; i < size; i++) {
        while (scanf_s("%d", &arr[i]) != 1) {
            printf("ќшибка! ¬ведите целое число: ");
            while (getchar() != '\n'); //очистка от вечных повторов и невозможности ввести новое значение
        }
    }
    return arr;
}

// генераци€ случайных чисел
int* create_array_random(int size, int min, int max) {
    int* arr = (int*)malloc(size * sizeof(int));  
    srand((unsigned int)time(NULL));
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % (max - min + 1) + min;
    }
    return arr;
}   