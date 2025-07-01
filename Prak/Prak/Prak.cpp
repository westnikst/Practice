#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "array.h"
#include "sort.h"
#include "file.h"

int main() {
    system("chcp 1251 > nul"); // это для русского языка
    setlocale(LC_ALL, "RUS");

    int choice; // цифра выбора
    int size = 0; // размер массива
    int min, max; // для границ максимума и минимума в случайном наборе чисел
    int* original = NULL, * sorted = NULL; //для оригинала и отсортированного
    SortResult result;
    char filename[100]; //имя файла для записи

    while (1) {
        printf("\n=== МЕНЮ ===\n");
        printf("1. Создать массив (ручной ввод)\n");
        printf("2. Создать массив (случайные числа)\n");
        printf("3. Сохранить результаты\n");
        printf("4. Загрузить массив из файла\n");
        printf("5. Выход\n");
        printf("Выберите действие: ");

        if (scanf_s("%d", &choice) != 1) {
            printf("Ошибка ввода! Пожалуйста, введите число.\n");
            while (getchar() != '\n');
            continue;
        }

        if (choice == 1) {
            printf("Размер массива: ");
            if (scanf_s("%d", &size) != 1 || size <= 0) {
                printf("Некорректный размер!\n");
                while (getchar() != '\n');
                continue;
            }
            original = create_array_manual(size); // возвращаем указатель на созданный массив
            if (original) {
                sorted = (int*)malloc(size * sizeof(int));
                for (int i = 0; i < size; i++) 
                    sorted[i] = original[i];
                result = shell_sort(sorted, size);
                printf("Перестановок: %d, Время: %.6f мкс\n", result.swaps, result.time_mcs);
            }
        }
        else if (choice == 2) {
            printf("Размер массива: ");
            if (scanf_s("%d", &size) != 1 || size <= 0) {
                printf("Некорректный размер!\n");
                while (getchar() != '\n');
                continue;
            }
            printf("Диапазон (min max): ");
            if (scanf_s("%d %d", &min, &max) != 2) {
                printf("Некорректный диапазон!\n");
                while (getchar() != '\n');
                continue;
            }
            original = create_array_random(size, min, max);
            if (original) {
                sorted = (int*)malloc(size * sizeof(int));
                for (int i = 0; i < size; i++) sorted[i] = original[i];
                result = shell_sort(sorted, size);
                printf("Перестановок: %d, Время: %.6f мкс\n", result.swaps, result.time_mcs);
            }
        }
        else if (choice == 3) {
            if (!original || !sorted) {
                printf("Ошибка: массивы не созданы!\n");
                continue;
            }
            save_results(original, sorted, size, result);
        }
        else if (choice == 4) {
            printf("Имя файла: ");
            if (scanf_s("%99s", filename, (unsigned)_countof(filename)) != 1) {
                printf("Ошибка ввода имени файла!\n");
                while (getchar() != '\n');
                continue;
            }
            original = load_array_from_file(filename, &size);
            if (original) {
                sorted = (int*)malloc(size * sizeof(int));
                for (int i = 0; i < size; i++) 
                    sorted[i] = original[i];
                result = shell_sort(sorted, size);
                printf("Перестановок: %d, Время: %.3f мс\n", result.swaps, result.time_mcs);
            }
        }
        else if (choice == 5) {
            free(original);
            free(sorted);
            printf("Программа завершена\n");
            break;
        }
        else {
            printf("Неверный выбор!\n");
        }
    }
    return 0;
}
