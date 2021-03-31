#include "WorkMatrix.hpp"
#include <iostream>

// переменная хранит номер текущей матрицы
int numMatrix = 0;

int main() {
    int rows_1, columns_1 = 2;
    int rows_2, columns_2 = 2;
    int required_size = 2;
    std::cout << "Вас приветствует программа быстрого перемножение матриц методом Штрассена\n\n";

    // ввод размеров матрицы пользователем
    enterMatrixParameters(rows_1, columns_1, numMatrix);
    enterMatrixParameters(rows_2, columns_2, numMatrix);

    // создание двух новых матриц
    int** matrix_1 = createMatrix(rows_1, columns_1);
    int** matrix_2 = createMatrix(rows_2, columns_2);

    // выбор способа заполнения и заполнение матриц
    int filling_method = chooseFillingMethod();
    fillingMatrix(rows_1, columns_1, matrix_1, filling_method);
    fillingMatrix(rows_2, columns_2, matrix_2, filling_method);

    // вывод матриц
    printMatrix(rows_1, columns_1, matrix_1, numMatrix);
    printMatrix(rows_2, columns_2, matrix_2, numMatrix);

    // приведение матриц к требуемому размеру
    while (required_size < rows_1 || required_size < rows_2 || required_size < columns_1 || required_size < columns_2)
        required_size *= 2;

    int** matrix_3 = createMatrix(required_size, required_size);
    fillingMatrix(required_size, required_size, matrix_3, 0);

    int** matrix_4 = createMatrix(required_size, required_size);
    fillingMatrix(required_size, required_size, matrix_4, 0);

    copyValues(matrix_3, matrix_1, rows_1, 0, columns_1, 0);
    copyValues(matrix_4, matrix_2, rows_2, 0, columns_2, 0);

    std::cout << "\nПриведенные матрицы";
    printMatrix(required_size, required_size, matrix_3, numMatrix);
    printMatrix(required_size, required_size, matrix_4, numMatrix);

    // разбиение матриц на подматрицы и их заполнение
    const int part = required_size / 2;

    int** submatrix_1 = submatrixPartition(part, 0, part, 0, matrix_3);
    int** submatrix_2 = submatrixPartition(part, 0, part, part, matrix_3);
    int** submatrix_3 = submatrixPartition(part, part, part, 0, matrix_3);
    int** submatrix_4 = submatrixPartition(part, part, part, part, matrix_3);

    int** submatrix_5 = submatrixPartition(part, 0, part, 0, matrix_3);
    int** submatrix_6 = submatrixPartition(part, 0, part, part, matrix_3);
    int** submatrix_7 = submatrixPartition(part, part, part, 0, matrix_3);
    int** submatrix_8 = submatrixPartition(part, part, part, part, matrix_3);

    // cоздание промежуточных матриц
    int** intermediate_matrix_1 = createMatrix(part, part);
    int** intermediate_matrix_2 = createMatrix(part, part);
    int** intermediate_matrix_3 = createMatrix(part, part);
    int** intermediate_matrix_4 = createMatrix(part, part);
    int** intermediate_matrix_5 = createMatrix(part, part);
    int** intermediate_matrix_6 = createMatrix(part, part);
    int** intermediate_matrix_7 = createMatrix(part, part);

    // вычисление значений промежуточных матриц
    fillingMatrix(part, part, intermediate_matrix_1, 0);
    fillingMatrix(part, part, intermediate_matrix_2, 0);
    fillingMatrix(part, part, intermediate_matrix_3, 0);
    fillingMatrix(part, part, intermediate_matrix_4, 0);
    fillingMatrix(part, part, intermediate_matrix_5, 0);
    fillingMatrix(part, part, intermediate_matrix_6, 0);
    fillingMatrix(part, part, intermediate_matrix_7, 0);


    for (int i = 0; i < part; ++i) {
        for (int j = 0; j < part; ++j) {
            for (int z = 0; z < part; z++)
                intermediate_matrix_1[i][j] +=
                        (submatrix_1[i][z] + submatrix_4[i][z]) * (submatrix_5[z][j] + submatrix_8[z][j]);

            for (int z = 0; z < part; z++)
                intermediate_matrix_2[i][j] += (submatrix_3[i][z] + submatrix_4[i][z]) * submatrix_5[z][j];

            for (int z = 0; z < part; z++)
                intermediate_matrix_3[i][j] += submatrix_1[i][z] * (submatrix_6[z][j] - submatrix_8[z][j]);

            for (int z = 0; z < part; z++)
                intermediate_matrix_4[i][j] += submatrix_4[i][z] * (submatrix_7[z][j] - submatrix_5[z][j]);

            for (int z = 0; z < part; z++)
                intermediate_matrix_5[i][j] += (submatrix_1[i][z] + submatrix_2[i][z]) * submatrix_8[z][j];

            for (int z = 0; z < part; z++)
                intermediate_matrix_6[i][j] +=
                        (submatrix_3[i][z] - submatrix_1[i][z]) * (submatrix_5[z][j] + submatrix_6[z][j]);

            for (int z = 0; z < part; z++)
                intermediate_matrix_7[i][j] +=
                        (submatrix_2[i][z] - submatrix_4[i][z]) * (submatrix_7[z][j] + submatrix_8[z][j]);
        }
    }

    // создание вспомогательных матриц
    int** auxiliary_matrix_1 = createMatrix(part, part);
    int** auxiliary_matrix_2 = createMatrix(part, part);
    int** auxiliary_matrix_3 = createMatrix(part, part);
    int** auxiliary_matrix_4 = createMatrix(part, part);

    // подсчет значений вспомогательных матриц из промежуточных
    for (int i = 0; i < part; i++) {
        for (int j = 0; j < part; j++) {
            auxiliary_matrix_1[i][j] = intermediate_matrix_1[i][j] + intermediate_matrix_4[i][j] - intermediate_matrix_5[i][j] + intermediate_matrix_7[i][j];
            auxiliary_matrix_2[i][j] = intermediate_matrix_3[i][j] + intermediate_matrix_5[i][j];
            auxiliary_matrix_3[i][j] = intermediate_matrix_2[i][j] + intermediate_matrix_4[i][j];
            auxiliary_matrix_4[i][j] = intermediate_matrix_1[i][j] - intermediate_matrix_2[i][j] + intermediate_matrix_3[i][j] + intermediate_matrix_6[i][j];
        }
    }

    // создание результирующей матрицы
    int** result_matrix = createMatrix(required_size, required_size);

    // нанесение информации из вспомогательных матриц в результирующую
    copyValues(result_matrix, auxiliary_matrix_1, part, 0, part, 0);
    copyValues(result_matrix, auxiliary_matrix_2, part, 0, part, part);
    copyValues(result_matrix, auxiliary_matrix_3, part, part, part, 0);
    copyValues(result_matrix, auxiliary_matrix_4, part, part, part, part);

    // выравнивание границ результирующей матрицы
    int horizontal = 0, vertical = INT_MAX;
    for (int i = 0; i < required_size; i++)
        for (int j = 0; j < required_size; j++)
            if (result_matrix[i][j] != 0)
                break;
            else
                horizontal = i;

    for (int i = 0; i < required_size; i++)
        for (int j = 0; j < required_size; j++)
            if (result_matrix[j][i] != 0)
                break;
            else
                vertical = i;

    if (horizontal == INT_MAX)
        horizontal = required_size;
    if (vertical == INT_MAX)
        vertical = required_size;

    int** answer_matrix = new int* [horizontal];
    for (int i = 0; i < horizontal; i++) {
        answer_matrix[i] = new int[vertical];
        for (int j = 0; j < vertical; j++)
            answer_matrix[i][j] = result_matrix[i][j];
    }

    // вывод результирующей матрицы
    std::cout << "\nРезультирующая матрица\n\n";
    for (int i = 0; i < horizontal; i++) {
        for (int j = 0; j < vertical; j++)
            std::cout << answer_matrix[i][j] << " ";
        std::cout << std::endl;
    }

    //Очистка динамической памяти
    for (int i = 0; i < rows_1; i++)
        delete[] matrix_1[i];
    delete[] matrix_1;

    for (int i = 0; i < rows_2; i++)
        delete[] matrix_2[i];
    delete[] matrix_2;

    for (int i = 0; i < required_size; i++) {
        delete[] matrix_3[i];
        delete[] matrix_4[i];
        delete[] result_matrix[i];
    }
    delete[] matrix_3;
    delete[] matrix_4;
    delete[] result_matrix;

    for (int i = 0; i < horizontal; i++)
        delete[] answer_matrix[i];
    delete[] answer_matrix;

    for (int i = 0; i < required_size / 2; i++) {
        delete[] submatrix_1[i];
        delete[] submatrix_2[i];
        delete[] submatrix_3[i];
        delete[] submatrix_4[i];
        delete[] submatrix_5[i];
        delete[] submatrix_6[i];
        delete[] submatrix_7[i];
        delete[] submatrix_8[i];
        delete[] auxiliary_matrix_1[i];
        delete[] auxiliary_matrix_2[i];
        delete[] auxiliary_matrix_3[i];
        delete[] auxiliary_matrix_4[i];
        delete[] intermediate_matrix_1[i];
        delete[] intermediate_matrix_2[i];
        delete[] intermediate_matrix_3[i];
        delete[] intermediate_matrix_4[i];
        delete[] intermediate_matrix_5[i];
        delete[] intermediate_matrix_6[i];
        delete[] intermediate_matrix_7[i];
    }
    delete[] submatrix_1;
    delete[] submatrix_2;
    delete[] submatrix_3;
    delete[] submatrix_4;
    delete[] submatrix_5;
    delete[] submatrix_6;
    delete[] submatrix_7;
    delete[] submatrix_8;
    delete[] auxiliary_matrix_1;
    delete[] auxiliary_matrix_2;
    delete[] auxiliary_matrix_3;
    delete[] auxiliary_matrix_4;
    delete[] intermediate_matrix_1;
    delete[] intermediate_matrix_2;
    delete[] intermediate_matrix_3;
    delete[] intermediate_matrix_4;
    delete[] intermediate_matrix_5;
    delete[] intermediate_matrix_6;
    delete[] intermediate_matrix_7;

    return 0;
}
