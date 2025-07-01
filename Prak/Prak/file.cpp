#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sort.h"

// загрузка массива из файла
int* load_array_from_file(const char* filename, int* size) {
    FILE* file;
    fopen_s(&file, filename, "r");

    // определяем размер файла
    fseek(file, 0, SEEK_END); //переносимся в конец
    long file_size = ftell(file);// считываем всю длину файла
    fseek(file, 0, SEEK_SET); // обратно в начало

    // выделяем динамический буфер под файл
    char* buffer = (char*)malloc(file_size + 1);
    fread(buffer, 1, file_size, file);
    buffer[file_size] = '\0';
    fclose(file);

    // убираем символ новой строки
    if (buffer[file_size - 1] == '\n') {
        buffer[file_size - 1] = '\0';
    }

    // считаем количество чисел
    *size = 1;
    for (char* p = buffer; *p; p++) {
        if (*p == ',') (*size)++; // 1+ количество запятых
    }

    // создаём массив чисел
    int* arr = (int*)malloc(*size * sizeof(int));

    //разбиение строки
    char* next_token = NULL; //нужно для безопасной версии strtok (для strtok_s)
    char* token = strtok_s(buffer, ",", &next_token);

    for (int i = 0; token && i < *size; i++) {
        arr[i] = atoi(token); // преобразовать в число
        token = strtok_s(NULL, ",", &next_token);
    }

    free(buffer);  // о свобождаем буфер файла
    return arr;
}

// сохранение массива в файл
void save_array_to_file(const char* filename, int arr[], int size) {
    FILE* file;
    fopen_s(&file, filename, "w");

    for (int i = 0; i < size; i++) {
        fprintf(file, "%d", arr[i]);
        if (i < size - 1) fprintf(file, ","); //что бы запятая после каждого числа кроме последнего
    }

    fclose(file);
}

// Сохранение результатов
void save_results(int original[], int sorted[], int size, SortResult result) {
    char name[100];
    printf("Введите базовое имя файлов: ");
    scanf_s("%99s", name, (unsigned)sizeof(name));
    //имена файлов
    char orig_name[120], sorted_name[120];
    sprintf_s(orig_name, sizeof(orig_name), "%s_original.txt", name);
    sprintf_s(sorted_name, sizeof(sorted_name), "%s_sorted.txt", name);
    //данные файлов
    save_array_to_file(orig_name, original, size);
    save_array_to_file(sorted_name, sorted, size);

    printf("Файлы сохранены:\n%s\n%s\n", orig_name, sorted_name);
    printf("Перестановок: %d\nВремя: %.3f мс\n", result.swaps, result.time_mcs);
}