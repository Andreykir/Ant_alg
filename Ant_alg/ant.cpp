#include "ant.h"



AntColonyOptimization::AntColonyOptimization()
{
	/*инициализируем*/
	Data_matrix = NULL;
	Arr_waight = NULL;
	Hyp_waight = new double[5];
	Matrix_pheromone = NULL;
	
	size = 0;
	all_waight = 0;

	/*заполняем начальные матрицы*/
	size = ReadSize(); // добавит чет общего веса
	Matrix_hypothesis = new int* [5];
	Hyp_waight = new double[5];
	Data_matrix = new int* [size];
	Arr_waight = new double[size];
	Matrix_pheromone = new double* [size];

	/* Создание двумерного массива */
	for (int t = 0; t < size; ++t) {
		Data_matrix[t] = new int[size];
		Matrix_pheromone[t] = new double[size];
	}
	for (int k = 0; k < 5; k++) {
		Matrix_hypothesis[k] = new int[size];
	}
	/* заполнение полученного массива */
	for (int k = 0; k < size; k++) {
		for (int r = 0; r < size; r++) {
			Data_matrix[k][r] = 0;
			Matrix_pheromone[k][r] = 0.5;
		}
		Arr_waight[k] = 0.0;
	}
	for (int k = 0; k < 5; k++) {
		for (int r = 0; r < size; r++) {
			Matrix_hypothesis[k][r] = 0;
		}
		Hyp_waight[k] = 0.0;
	}
	all_waight = ReadMatrix(Data_matrix, Arr_waight);

}

void AntColonyOptimization::SolveSalesmansProblem()
{
	/*Основной метод прохода колонии муравьев
	1)паралелим создание 5 муравьев(= кол-ву гипотез)
	2) цикл из условных 50-200 итераций
	3)отправляем муровья в путь, где он по циклу 
	wile(can_continue) {
		getNeighborVertexes(данные); - подсчет возможных вариантов перехода (в вероятностях)
		MakeChoice(данные); - метод выбора пути
	}
	UpdateGlobalPheromone(); - обновление феромонов
	4) сравнес топ 5 гипотез
	возвращаем матрицу из 5 гипотез с сумарным весом
	*/
	
	int counter = 0;

	
	while (counter++ != kLife_colony) {
		// инициализация начальных муравьев
		CreateAnts(Antanina, size, all_waight, Data_matrix, Matrix_pheromone, Arr_waight);// переделать функцию инициализации муравьев
			Antanina.can_continue = true;
			Antanina.waight = 0.0;
			for (int i = 0; i < size; i++) {
				Antanina.hypothesis[i] = 0;
			}
			while (Antanina.can_continue) {
				Antanina.MakeChoice(Data_matrix, Matrix_pheromone, Arr_waight, all_waight, size, kAlpha_, kBeta_);
			}
			Antanina.waight -= Arr_waight[Antanina.current_location];
			bool povtor = false;
			for (int i = 0; i < 5; i++) {
				if (Antanina.waight == Hyp_waight[i]) {
					povtor = true;
					Antanina.waight = 0.0;
					break;
				}
			}
			if (!povtor) {
				if (Antanina.waight > Hyp_waight[4]) {
					for (int col = 0; col < size; col++) {
						Matrix_hypothesis[4][col] = Antanina.hypothesis[col];
					}
					Hyp_waight[4] = Antanina.waight;
				}
				for (int i = 3; i >= 0; i--) {
					if (Antanina.waight > Hyp_waight[i]) {
						for (int col = 0; col < size; col++) {
							Matrix_hypothesis[i + 1][col] = Matrix_hypothesis[i][col];
							Matrix_hypothesis[i][col] = Antanina.hypothesis[col];
						}
						Hyp_waight[i + 1] = Hyp_waight[i];
						Hyp_waight[i] = Antanina.waight;
					}
				}
				}
			UpdateGlobalPheromone(Antanina.hypothesis);// обновить ферамоны	
	}
}

void AntColonyOptimization::ShowResault()
{	//вывод в файл
	WriteMatrix(Matrix_hypothesis, Hyp_waight, size);
	//для вывода в консоль
	/*for (int i = 0; i < 5; i++) {
		for (int j = 0; j < size; j++) {
			cout << Matrix_hypothesis[i][j] << " ";
		}
		cout << Hyp_waight[i] << "\n";
	}*/
}

void AntColonyOptimization::CreateAnts(Ant Antanina, int size, double all_waight, int** Data_matrix, double** Matrix_pheromon, double* Arr_waight)
{
		double choice = Antanina.getRandomChoice();
		Antanina.array_way_probability[0] = Arr_waight[0] / all_waight;
		for (int j = 1; j < size; j++) {
			Antanina.array_way_probability[j] = Antanina.array_way_probability[j-1] + (Arr_waight[j] / all_waight);
		}
		
		int i = 0;
		while ((choice >= Antanina.array_way_probability[i]) && (i < size)) {
			i++;
		}
		Antanina.start_location = i;
		Antanina.can_continue = true;
		Antanina.current_location = i;
		for (int j = 0; j < size; j++) {
			Antanina.hypothesis[j] = 0;
			Antanina.array_no_way[j] = Data_matrix[i][j];
		}
		Antanina.waight = Arr_waight[i];
		Antanina.hypothesis[Antanina.start_location] = i;
}

void AntColonyOptimization::UpdateGlobalPheromone(int* hypothesis)
{
	/*функция обновления феромонов идет после того как муровей закончил путь
	1 -испаряем старые феромоны
	2 -выставляем новые(в зависимости от количества пройденных тут муравьев)*/
	for (int i = 0; i < size; i++) {
		for (int j = i; j < size; j++) {
			Matrix_pheromone[i][j] = Matrix_pheromone[i][j] - kEvaporation_ + kPheromone0_ * hypothesis[j];
			if (Matrix_pheromone[i][j] < 0.1) Matrix_pheromone[i][j] = 0.1;
			Matrix_pheromone[j][i] = Matrix_pheromone[i][j];
		}
	}
}

Ant::Ant(std::size_t start_vertex)
{
	int size = ReadSize(); // добавит чет общего веса

	hypothesis = new int[size];; // траектории-гипотеза
	array_no_way = new int[size]; // посещенные вершины и те что огранчены
	array_way_probability = new double[size];// - массив вероятностей при выборе пути
	waight = 0;
	start_location = 0;
	current_location = 0; //стартовая и текущая локации
	array_probability_choice = new double[size];
	for (int i = 0; i < size; i++) {
		hypothesis[i] = 0;
		array_no_way[i] = 0;
		array_way_probability[i] = 0.0;
		array_probability_choice[i] = 0.0;
	}
	can_continue = true; // признак возможного продолжения

}

void Ant::MakeChoice(int** Data_matrix, double** Matrix_pheromone, double* Arr_waight, double all_waight,
	int size, double alfa, double beta)
{
	/*получаем случайный выбор
	определяем возможные пути(метод возвращает массив(траектория-вероятность туда попасть(+предыдущая вероятность, в виде отрезка)
	записываем его в уже пройденный путь
	добавляем вероятность(пройденный путь)
	увеличиваем итератор(перескакиваем на новый замер)
	проверяем условие конца*/

	//1
	double choice = getRandomChoice();
	//2
	int i = 0; 
	double* array_probability_choice = getNeighborVertexes(Data_matrix, array_no_way, array_way_probability,
		size, Matrix_pheromone, Arr_waight, all_waight, alfa, beta);
	while (choice > array_probability_choice[i] && i <= size) {
		i++;
		if (i == size) { //4
			i = current_location;
			can_continue = false;
			break;
		}
	}
	//3
	hypothesis[i] = 1;
	current_location = i;
	waight += Arr_waight[i];
	for (i = 0; i < size; i++) {
		array_no_way[i] = array_no_way[i] * Data_matrix[current_location][i];
	}
}


double Ant::getRandomChoice()
{
	random_device rd;
	mt19937 fort(rd());
	uniform_real_distribution<> apex(0, 1.0);
	return apex(fort);
}

double* Ant::getNeighborVertexes(int** Data_matrix, int* array_no_way, double* array_way_probability,
	int size, double** Data_pheromon, double* Arr_waight, 
	double all_waight, double alpha, double beta)
{
	double* array_probability = new double[size];
	double Psum = 0;
	for (int i = 0; i < size; i++) {
		array_probability[i] = array_no_way[i] * pow(Data_pheromon[current_location][i], alpha) * Data_matrix[current_location][i] * pow((Arr_waight[i] / all_waight),beta);
		Psum += array_probability[i];
	}
	if (Psum != 0) {
		array_probability[0] = array_probability[0] / Psum;
		for (int i = 1; i < size; i++) {
			array_probability[i] = array_probability[i-1] + array_probability[i] / Psum;//для подсчета вероятностей используем коэффициенты
		};
	} 
	return array_probability;
}
