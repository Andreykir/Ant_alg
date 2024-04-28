#include "ant.h"
#include "matrix.h"
//#include <locale>
#include <ctime>
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <malloc.h>
#include <conio.h>

/* Подключение пространства имен */
using namespace std;


int main() 
{	
	/* Использование муравьиного алгоритма - неполная функция !!!выдаст ошибку*/
	AntColonyOptimization AntColony = AntColonyOptimization();
	AntColony.SolveSalesmansProblem();
	/* Вывод результата на экран для контроля работы программы */
	AntColony.ShowResault();
	//cout << "Time= " << (clock() / 1000.0) << "c" << endl;

	//_getch();

	return 0;
}