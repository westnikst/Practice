#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file.h"

// �������� ������� �� �����
int* load_array_from_file(const char* input_filename, int* size) {
    char filename[260]; // ����� ��� ����� �����

    // �������� �������� ���
    strcpy_s(filename, sizeof(filename), input_filename);

    // ��������� .txt ���� ��� ����������
    if (strchr(filename, '.') == NULL) {
        strcat_s(filename, sizeof(filename), ".txt");
    }

    FILE* file;
    if (fopen_s(&file, filename, "r") != 0) {
        printf("������ �������� ����� %s!\n", filename);
        return NULL;
    }

    // ���������� ������ �����
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    // ������ �����
    char* buffer = (char*)malloc(file_size + 1);
    fread(buffer, 1, file_size, file);
    buffer[file_size] = '\0';
    fclose(file);

    // ������� ������ ����� ������
    if (file_size > 0 && buffer[file_size - 1] == '\n') {
        buffer[file_size - 1] = '\0';
    }

    // ������� ���������� �����
    *size = 1;
    for (char* p = buffer; *p; p++) {
        if (*p == ',') (*size)++;
    }

    // ������ ������ �����
    int* arr = (int*)malloc(*size * sizeof(int));
    if (!arr) {
        free(buffer);
        return NULL;
    }

    // ��������� ������
    char* next_token = NULL;
    char* token = strtok_s(buffer, ",", &next_token);

    for (int i = 0; token && i < *size; i++) {
        arr[i] = atoi(token);
        token = strtok_s(NULL, ",", &next_token);
    }

    free(buffer);
    return arr;
}

// ���������� ������� � ����
void save_array_to_file(const char* filename, int arr[], int size) {
    FILE* file;
    if (fopen_s(&file, filename, "w") != 0) {
        printf("������ �������� �����!\n");
        return;
    }

    for (int i = 0; i < size; i++) {
        fprintf(file, "%d", arr[i]);
        if (i < size - 1) fprintf(file, ",");
    }

    fclose(file);
}

// ���������� ����������� (���������� ������)
void save_results(int array[], int size) {
    char filename[100];
    printf("������� ��� ����� (��� ����������): ");
    scanf_s("%99s", filename, (unsigned)sizeof(filename));

    // ������� ������ ����� scanf_s
    int c;
    while ((c = getchar()) != '\n');

    // ��������� ���������� .txt
    char fullname[120];
    sprintf_s(fullname, sizeof(fullname), "%s.txt", filename);

    save_array_to_file(fullname, array, size);
    printf("���� ��������: %s\n", fullname);
}