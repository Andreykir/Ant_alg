#pragma once

/* ����������� ������ */

#include <fstream>
#include <iostream>

#define MAX_COL  100 // ������������ ������ �������
/* ��������� ������� */
int ReadSize(); // ������� ������ �������
double ReadMatrix(int**, double *); // � ������� ������������ ������ ����� ����������� ������� �� ����� input.csv
void WriteMatrix(int**, double*,int); // �������� 5 ������ ���������� ������� � �� ������ � �������� ������ � ���� output.csv
