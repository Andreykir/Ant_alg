#pragma once

/* Подключение модуля */

#include <fstream>
#include <iostream>

#define MAX_COL  100 // максимальный размер матрицы
/* Прототипы функций */
int ReadSize(); // считать размер матрицы
double ReadMatrix(int**, double *); // с матрицу совместности массив весов траекторных гипотез из файла input.csv
void WriteMatrix(int**, double*,int); // выписать 5 лучших глобальных гипотез с их весами и временем работы в файл output.csv
