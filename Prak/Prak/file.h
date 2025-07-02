#ifndef FILE_H
#define FILE_H

int* load_array_from_file(const char* filename, int* size);
void save_array_to_file(const char* filename, int arr[], int size);
void save_results(int array[], int size);  // Упрощённая функция сохранения

#endif