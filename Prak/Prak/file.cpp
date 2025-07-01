#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sort.h"

// �������� ������� �� �����
int* load_array_from_file(const char* filename, int* size) {
    FILE* file;
    fopen_s(&file, filename, "r");

    // ���������� ������ �����
    fseek(file, 0, SEEK_END); //����������� � �����
    long file_size = ftell(file);// ��������� ��� ����� �����
    fseek(file, 0, SEEK_SET); // ������� � ������

    // �������� ������������ ����� ��� ����
    char* buffer = (char*)malloc(file_size + 1);
    fread(buffer, 1, file_size, file);
    buffer[file_size] = '\0';
    fclose(file);

    // ������� ������ ����� ������
    if (buffer[file_size - 1] == '\n') {
        buffer[file_size - 1] = '\0';
    }

    // ������� ���������� �����
    *size = 1;
    for (char* p = buffer; *p; p++) {
        if (*p == ',') (*size)++; // 1+ ���������� �������
    }

    // ������ ������ �����
    int* arr = (int*)malloc(*size * sizeof(int));

    //��������� ������
    char* next_token = NULL; //����� ��� ���������� ������ strtok (��� strtok_s)
    char* token = strtok_s(buffer, ",", &next_token);

    for (int i = 0; token && i < *size; i++) {
        arr[i] = atoi(token); // ������������� � �����
        token = strtok_s(NULL, ",", &next_token);
    }

    free(buffer);  // � ���������� ����� �����
    return arr;
}

// ���������� ������� � ����
void save_array_to_file(const char* filename, int arr[], int size) {
    FILE* file;
    fopen_s(&file, filename, "w");

    for (int i = 0; i < size; i++) {
        fprintf(file, "%d", arr[i]);
        if (i < size - 1) fprintf(file, ","); //��� �� ������� ����� ������� ����� ����� ����������
    }

    fclose(file);
}

// ���������� �����������
void save_results(int original[], int sorted[], int size, SortResult result) {
    char name[100];
    printf("������� ������� ��� ������: ");
    scanf_s("%99s", name, (unsigned)sizeof(name));
    //����� ������
    char orig_name[120], sorted_name[120];
    sprintf_s(orig_name, sizeof(orig_name), "%s_original.txt", name);
    sprintf_s(sorted_name, sizeof(sorted_name), "%s_sorted.txt", name);
    //������ ������
    save_array_to_file(orig_name, original, size);
    save_array_to_file(sorted_name, sorted, size);

    printf("����� ���������:\n%s\n%s\n", orig_name, sorted_name);
    printf("������������: %d\n�����: %.3f ��\n", result.swaps, result.time_mcs);
}