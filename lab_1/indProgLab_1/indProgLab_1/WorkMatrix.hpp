#ifndef WorkMatrix_hpp
#define WorkMatrix_hpp

#include <iostream>
#include <random>
using namespace std;

// фукнция для изменения текущей матрицы
void change_numMatrix(int&);
// функция для ввода параметров матрицы
void enterMatrixParameters(int&, int&, int&);
// функция для создания матрицы
int** createMatrix(int, int);
// функция для выбора способа заполнения матрицы
int chooseFillingMethod();
// функция для заполнения матрицы
void fillingMatrix(int, int, int**, int);
// функция для вывода матрицы
void printMatrix(int, int, int**, int&);
// функция для копирования значений одной матрицы в другую
void copyValues(int**, int**, int, int, int, int);
// функция для создания подматрицы
int** submatrixPartition(int, int, int, int, int**);

#endif /* WorkMatrix_hpp */
