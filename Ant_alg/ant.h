#pragma once

#include <vector>
#include <ctime>
#include <fstream>
#include <random>
#include <iostream>
#include <algorithm>
#include <execution>
#include "matrix.h"

using namespace std;

//using AntColonyTimed = pair<Ant, double>; - для паралельного распределения колони муравьев

struct Ant {//структура данных одного муравья 
    explicit Ant(std::size_t start_vertex = 0);

    int* hypothesis; // траектории-гипотеза
    int* array_no_way; // посещенные вершины и те что огранчены
    double* array_way_probability;// - массив вероятностей при выборе пути
    double waight = 0;
    //int number; //- номер муравья
    int start_location = 0, current_location = 0; //стартовая и текущая локации
    double* array_probability_choice;

    bool can_continue = true; // признак возможного продолжения

    void MakeChoice(int** Data_matrix, double** Matrix_pheromone, double* Arr_waight,
        double all_waight, int size, double alfa, double beta); // метод выбора пути
    double getRandomChoice(); //метод выдающий рандомное число для выбора пути
    double* getNeighborVertexes(int** Data_matrix, int* array_no_way, double* array_way_probability,
        int size, double** Matrix_pheromone, double* Arr_waight, double all_wait, double alfa, double beta); // метод показывающий возможные пути
};

class AntColonyOptimization { // класс колонии муравьев
public:
    explicit AntColonyOptimization(); // метод определения лучшего пути инициализация класса

    void SolveSalesmansProblem(); // метод прохода всех муравьев
    //void SolveSalesmanProblemParallel(bool reset = false);- для паралельного распределения колони муравьев

    void ShowResault(); // метод прохода всех муравьев

private:
    /*константы*/
    const double kAlpha_ = 1.0;
    const double kBeta_ = 1.6;
    const double kPheromone0_ = 1.0;
    const double kQ_ = 5.0;
    const double kEvaporation_ = 0.2;
    const double kLife_colony = 1000;


    /* матрицы для муравьев*/
    double** Matrix_pheromone;// матрица феромонов
    int** Data_matrix;
    double* Arr_waight;
    int size;
    double all_waight;
    int** Matrix_hypothesis;// матрица топ 5 гипотез по версии юрия дудя 
    double* Hyp_waight;

    Ant Antanina;// = Ant(1);
    //vector<Ant> ants_; // - для паралельного распределения колони муравьев

    //void CreateAntsPar();- для паралельного распределения колони муравьев
    //void LaunchAntsPar();- для паралельного распределения колони муравьев
    //bool UpdatePathAndLocalPheromonePar(AntPath& path, Matrix<double>& lpu);- для паралельного распределения колони муравьев

    void CreateAnts(Ant Antanina, int size, double all_waight, int** Data_matrix,
        double** Matrix_pheromone, double* Arr_waight); //метод создания муравьев(я)
    void UpdateGlobalPheromone(int* hypothesis);// метод обновления феромонов
};

