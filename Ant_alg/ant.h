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

//using AntColonyTimed = pair<Ant, double>; - ��� ������������ ������������� ������ ��������

struct Ant {//��������� ������ ������ ������� 
    explicit Ant(std::size_t start_vertex = 0);

    int* hypothesis; // ����������-��������
    int* array_no_way; // ���������� ������� � �� ��� ���������
    double* array_way_probability;// - ������ ������������ ��� ������ ����
    double waight = 0;
    //int number; //- ����� �������
    int start_location = 0, current_location = 0; //��������� � ������� �������
    double* array_probability_choice;

    bool can_continue = true; // ������� ���������� �����������

    void MakeChoice(int** Data_matrix, double** Matrix_pheromone, double* Arr_waight,
        double all_waight, int size, double alfa, double beta); // ����� ������ ����
    double getRandomChoice(); //����� �������� ��������� ����� ��� ������ ����
    double* getNeighborVertexes(int** Data_matrix, int* array_no_way, double* array_way_probability,
        int size, double** Matrix_pheromone, double* Arr_waight, double all_wait, double alfa, double beta); // ����� ������������ ��������� ����
};

class AntColonyOptimization { // ����� ������� ��������
public:
    explicit AntColonyOptimization(); // ����� ����������� ������� ���� ������������� ������

    void SolveSalesmansProblem(); // ����� ������� ���� ��������
    //void SolveSalesmanProblemParallel(bool reset = false);- ��� ������������ ������������� ������ ��������

    void ShowResault(); // ����� ������� ���� ��������

private:
    /*���������*/
    const double kAlpha_ = 1.0;
    const double kBeta_ = 1.6;
    const double kPheromone0_ = 1.0;
    const double kQ_ = 5.0;
    const double kEvaporation_ = 0.2;
    const double kLife_colony = 1000;


    /* ������� ��� ��������*/
    double** Matrix_pheromone;// ������� ���������
    int** Data_matrix;
    double* Arr_waight;
    int size;
    double all_waight;
    int** Matrix_hypothesis;// ������� ��� 5 ������� �� ������ ���� ���� 
    double* Hyp_waight;

    Ant Antanina;// = Ant(1);
    //vector<Ant> ants_; // - ��� ������������ ������������� ������ ��������

    //void CreateAntsPar();- ��� ������������ ������������� ������ ��������
    //void LaunchAntsPar();- ��� ������������ ������������� ������ ��������
    //bool UpdatePathAndLocalPheromonePar(AntPath& path, Matrix<double>& lpu);- ��� ������������ ������������� ������ ��������

    void CreateAnts(Ant Antanina, int size, double all_waight, int** Data_matrix,
        double** Matrix_pheromone, double* Arr_waight); //����� �������� ��������(�)
    void UpdateGlobalPheromone(int* hypothesis);// ����� ���������� ���������
};

