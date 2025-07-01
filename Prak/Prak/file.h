// Функции для работы с файлами
#ifndef FILE_H
#define FILE_H

int* load_array_from_file(const char* filename, int* size);  // Загрузка из файла
void save_array_to_file(const char* filename, int arr[], int size);  // Сохранение в файл
void save_results(int original[], int sorted[], int size, SortResult result);  // Сохранение результатов

#endif