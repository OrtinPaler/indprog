#include "WorkMatrix.hpp"

void change_numMatrix(int& number_of_matrix) {
    number_of_matrix++;
    if (number_of_matrix == 3)
        number_of_matrix -= 2;
}

void enterMatrixParameters(int& rows, int& columns, int& number_of_matrix) {
    change_numMatrix(number_of_matrix);

    string name_matrix;
    if (number_of_matrix == 1)
        name_matrix = " первой матрицы";
    else
        name_matrix = " второй матрицы";

    do {
        cout << "Введите размеры" + name_matrix + "\n";
        cin >> rows >> columns;
    } while (rows <= 0 || columns <= 0);
}

int** createMatrix(const int rows, const int columns) {
    int** matrix = new int* [rows];
    for (int i = 0; i < rows; i++)
        matrix[i] = new int[columns];

    return matrix;
}

int chooseFillingMethod() {
    int filling_method = 2;

    do {
        cout << "\nВыберите способ заполнения матриц\n1 - вручную\n2 - случайным образом\n";
        cin >> filling_method;
    } while (filling_method < 1 || filling_method > 2);

    return filling_method;
}

void fillingMatrix(const int rows, const int columns, int** matrix, const int filling_method) {
    random_device rd;   // источник энтропии
    mt19937 gen(rd());  // генератор случайных чисел
    uniform_int_distribution<> uid(0, 9);  // равномерное распределение [0, 10]

    switch (filling_method) {
        case 1:
            for (int i = 0; i < rows; i++)
                for (int j = 0; j < columns; j++)
                    cin >> matrix[i][j];
            break;
        case 2:
            for (int i = 0; i < rows; i++)
                for (int j = 0; j < columns; j++)
                    matrix[i][j] = uid(gen);
            break;
        default:
            for (int i = 0; i < rows; i++)
                for (int j = 0; j < columns; j++)
                    matrix[i][j] = 0;
            break;
    }
}

void printMatrix(const int rows, const int columns, int** matrix, int& number_of_matrix) {
    change_numMatrix(number_of_matrix);

    cout << "\nМатрица " << number_of_matrix << "\n";
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++)
            cout << matrix[i][j] << " ";
        cout << endl;
    }
}

void copyValues(int** matrix_1, int** matrix_2, const int rows_2, const int start_rows, const int columns_2, const int start_columns) {
    for (int i = 0; i < rows_2; i++)
        for (int j = 0; j < columns_2; j++)
            matrix_1[i][j] = matrix_2[i + start_rows][j + start_columns];
}

int** submatrixPartition(const int rows, const int start_rows, const int columns, const int start_columns, int** matrix) {
    int** submatrix = createMatrix(rows, columns);
    copyValues(submatrix, matrix, rows, start_rows, columns, start_columns);

    return submatrix;
}
