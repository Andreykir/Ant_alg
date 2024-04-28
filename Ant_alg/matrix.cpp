#include "matrix.h"
#include <locale>
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <malloc.h>
#include <conio.h>
#include <time.h>

/* Подключение пространства имен */
using namespace std;


int ReadSize()
{
	/* Объявление перменных */
	FILE *input = NULL;
	int size = 0;

	/* Окрытие файла на чтение */
	ifstream file("input.csv");
	if (!file.is_open()) {
		cerr << "Error opening file!" << endl;
		return 1;
	}
	// инициализация переменных
	string line;
	int col = 0;
	// считываем строки и парсим по запятым
	getline(file, line);
	stringstream ss(line);
	string cell;
	while (getline(ss, cell, ',') && (col < MAX_COL)) {
		col++;
	}
	size = col;
	// закрываем файл
	file.close();
	/* Возврат размера матрицы */
	return size;
}

                                     
double ReadMatrix(int **Data_matrix, double *Arr_waight) {
	/* Объявление перменной */
	FILE *input = NULL;

	/* Вызов функции readSize */
	int size = ReadSize();
	double all_waight = 0;

	// Открыть CSV 
	ifstream file("input.csv");
	if (!file.is_open()) {
		cerr << "Error opening file!" << endl;
		return 1;
	}

	// считать двумерный массив матриц
	string line;
	int row = 0;
	int col = 0;
	
	while (getline(file, line) && row < size) {
		stringstream ss(line);
		string cell;
		col = 0;
		while (getline(ss, cell, ',') && col < size) {
			Data_matrix[row][col] = stoi(cell);
			col++;
		}
		row++;
	}
	//отдельно считываем матрицу весов
	getline(file, line);
	stringstream ss(line);
	string cell;
	col = 0;
	while (getline(ss, cell, ',') && col < size) {
		Arr_waight[col] = stod(cell);
		all_waight += Arr_waight[col];
		col++;
	}
	// матрицу в симетричную
	for (int row = 0; row < size; row++) {
		for (int col = row; col < size; col++) {
			Data_matrix[col][row] = Data_matrix[row][col];
		}
	}
	// закрываем файл
	file.close();
	return all_waight;
}

void WriteMatrix(int** Matrix_hypothesis, double* Hyp_waight, int size)
{
	ofstream out("output.csv");
	if (!out) {
		std::cout << "Cannot open file.\n";
		std::system("pause");
		exit(1);
	}
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < size; j++) {
			out << Matrix_hypothesis[i][j] << ",";
		}
		out << Hyp_waight[i] << "\n";
	}
	out << "Time= " << (clock() / 1000.0) << "c" << endl;
	out.close();
}
