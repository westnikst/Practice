#ifndef SORT_H
#define SORT_H

// ��������� ��� �������� ����������� ���������� (�����, ���������� ���������)
typedef struct { // typedef ��� ����� ���������
    int swaps;      // ���������� ������������
    double time_mcs; // ����� ����������
} SortResult; //��� ���������

SortResult shell_sort(int arr[], int size);  // ���������� �����

#endif