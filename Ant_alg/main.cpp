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

/* ����������� ������������ ���� */
using namespace std;


int main() 
{	
	/* ������������� ����������� ��������� - �������� ������� !!!������ ������*/
	AntColonyOptimization AntColony = AntColonyOptimization();
	AntColony.SolveSalesmansProblem();
	/* ����� ���������� �� ����� ��� �������� ������ ��������� */
	AntColony.ShowResault();
	//cout << "Time= " << (clock() / 1000.0) << "c" << endl;

	//_getch();

	return 0;
}