#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "array.h"

// ������ ���� �����.
int* create_array_manual(int size) {
    int* arr = (int*)malloc(size * sizeof(int)); // ������������ ��������� ������.
    if (!arr) return NULL;
    printf("������� %d ����� �����:\n", size);
    for (int i = 0; i < size; i++) {
        while (scanf_s("%d", &arr[i]) != 1) {
            printf("������! ������� ����� �����: ");
            while (getchar() != '\n'); // ������� ������.
        }
    }
    return arr;
}

// ��������� ��������� �����.
int* create_array_random(int size, int min, int max) {
    if (min > max) {  // �������� ������������ ���������
        printf("������: ������� ������ ���� ������ ���������!\n");
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