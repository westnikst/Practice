#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file.h"

// Загрузка массива из файла
int* load_array_from_file(const char* input_filename, int* size) {
    char filename[260]; // Буфер для имени файла

    // Копируем введённое имя
    strcpy_s(filename, sizeof(filename), input_filename);

    // Добавляем .txt если нет расширения
    if (strchr(filename, '.') == NULL) {
        strcat_s(filename, sizeof(filename), ".txt");
    }

    FILE* file;
    if (fopen_s(&file, filename, "r") != 0) {
        printf("Ошибка открытия файла %s!\n", filename);
        return NULL;
    }

    // Определяем размер файла
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    // Чтение файла
    char* buffer = (char*)malloc(file_size + 1);
    fread(buffer, 1, file_size, file);
    buffer[file_size] = '\0';
    fclose(file);

    // Убираем символ новой строки
    if (file_size > 0 && buffer[file_size - 1] == '\n') {
        buffer[file_size - 1] = '\0';
    }

    // Считаем количество чисел
    *size = 1;
    for (char* p = buffer; *p; p++) {
        if (*p == ',') (*size)++;
    }

    // Создаём массив чисел
    int* arr = (int*)malloc(*size * sizeof(int));
    if (!arr) {
        free(buffer);
        return NULL;
    }

    // Разбиение строки
    char* next_token = NULL;
    char* token = strtok_s(buffer, ",", &next_token);

    for (int i = 0; token && i < *size; i++) {
        arr[i] = atoi(token);
        token = strtok_s(NULL, ",", &next_token);
    }

    free(buffer);
    return arr;
}

// Сохранение массива в файл
void save_array_to_file(const char* filename, int arr[], int size) {
    FILE* file;
    if (fopen_s(&file, filename, "w") != 0) {
        printf("Ошибка создания файла!\n");
        return;
    }

    for (int i = 0; i < size; i++) {
        fprintf(file, "%d", arr[i]);
        if (i < size - 1) fprintf(file, ",");
    }

    fclose(file);
}

// Сохранение результатов (упрощённая версия)
void save_results(int array[], int size) {
    char filename[100];
    printf("Введите имя файла (без расширения): ");
    scanf_s("%99s", filename, (unsigned)sizeof(filename));

    // Очистка буфера после scanf_s
    int c;
    while ((c = getchar()) != '\n');

    // Добавляем расширение .txt
    char fullname[120];
    sprintf_s(fullname, sizeof(fullname), "%s.txt", filename);

    save_array_to_file(fullname, array, size);
    printf("Файл сохранен: %s\n", fullname);
}