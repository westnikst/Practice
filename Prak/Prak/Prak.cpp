#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "array.h"
#include "sort.h"
#include "file.h"

int main() {
    system("chcp 1251 > nul");
    setlocale(LC_ALL, "RUS");

    int choice, size = 0, min, max;
    int* original = NULL;
    SortResult result;
    char filename[100];

    while (1) {
        printf("\n=== МЕНЮ ===\n");

        // Отображение текущего массива
        if (original && size > 0) {
            printf("Текущий массив (%d элементов): ", size);
            int display_count;
            if (size > 30) {
                display_count = 30;
            }
            else {
                display_count = size;
            }

            for (int i = 0; i < display_count; i++) {
                printf("%d ", original[i]);
            }
            if (size > 30) 
                printf("...");
            printf("\n");
        }

        printf("1. Создать массив (ручной ввод)\n");
        printf("2. Создать массив (случайные числа)\n");
        printf("3. Выполнить сортировку Шелла\n");
        printf("4. Сохранить массив в файл\n");
        printf("5. Загрузить массив из файла\n");
        printf("6. Выход\n");
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
            if (original) free(original);
            original = create_array_manual(size);
        }
        else if (choice == 2) {
            printf("Размер массива: ");
            if (scanf_s("%d", &size) != 1 || size <= 0) {
                printf("Некорректный размер!\n");
                while (getchar() != '\n');
                continue;
            }
            printf("Диапазон (min max): ");
            if (scanf_s("%d %d", &min, &max) != 2 || min > max) {
                printf("Некорректный диапазон! Минимум должен быть меньше максимума.\n");
                while (getchar() != '\n');
                continue;
            }
        
            original = create_array_random(size, min, max);
        }
        else if (choice == 3) {
            if (!original || size <= 0) {
                printf("Ошибка: массив не создан!\n");
                continue;
            }
            // Сортируем массив напрямую
            result = shell_sort(original, size);
            printf("Сортировка завершена. Перестановок: %d, Время: %.6f мкс\n",
                result.swaps, result.time_mcs);
        }
        else if (choice == 4) {
            if (!original) {
                printf("Ошибка: массив не создан!\n");
                continue;
            }
            save_results(original, size);
        }
        else if (choice == 5) {
            printf("Имя файла (без расширения): ");
            if (scanf_s("%99s", filename, (unsigned)_countof(filename)) != 1) {
                printf("Ошибка ввода имени файла!\n");
                while (getchar() != '\n');
                continue;
            }
            if (original) free(original);
            original = load_array_from_file(filename, &size);
        }
        else if (choice == 6) {
            free(original);
            printf("Программа завершена\n");
            break;
        }
        else {
            printf("Неверный выбор!\n");
        }
    }
    return 0;
}