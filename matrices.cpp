#include <iostream>
#include <fstream>
#include <cstring>
#include "matrices.hpp"

bool if_add_or_mult(char *my_string) {
    std::size_t str_len = strlen(my_string);
    if (str_len < 5) {
        return false;
    }
    std::string right_a = "--add";
    std::string right_b = "--mult";
    return (my_string == right_a || my_string == right_b);
}

void memory_clean(float** memory, std::size_t size) {
    for (size_t i = 0; i < size; ++i){
        delete[] memory[i];
    }
    delete[] memory;
}

float ** get_matrix_from_file(char const *file_name, std::size_t *size_row, std::size_t *size_column){
    std::ifstream file (file_name);
    if (!file.is_open()){
        std::cerr << "file doesn't open";
        return nullptr;
    }
    file >> (*size_row) >> (*size_column);
    float **array = new float* [(*size_row)];
    for (std::size_t i = 0; i < (*size_row); ++i){
        array[i] = new float [(*size_column)];
    }
    for (std::size_t i = 0; i < (*size_row); ++i){
        for (std::size_t j = 0; j < (*size_column); ++j){
            file >> array[i][j];
        }
    }
    return array;
}

void get_sum(float **array_a, float **array_b,
             std::size_t row_a, std::size_t column_a) {
    for (std::size_t i = 0; i < row_a; ++i){
        for (std::size_t j = 0; j < column_a; ++j){
            array_a[i][j] += array_b[i][j];
        }
    }
    memory_clean(array_b, row_a);
}

void get_mult(float **array_a, float **array_b,
              std::size_t row_a, std::size_t *column_a,
              std::size_t row_b, std::size_t column_b){
    float **array_c = new float* [row_a];
    for (std::size_t i = 0; i < row_a; ++i){
        array_c[i] = new float [column_b];
        for (std::size_t j = 0; j < column_b; ++j){
            array_c[i][j] = 0;
            for (std::size_t k = 0; k < *column_a; ++k){
                array_c[i][j] += array_a[i][k] * array_b[k][j];
            }
        }
    }
    for (std::size_t i = 0; i < row_a; ++i){
        delete[] array_a[i];
    }
    for (std::size_t i = 0; i < row_a; ++i){
        array_a[i] = new float[column_b];
    }
    for (std::size_t i = 0; i < row_a; ++i){
        for (std::size_t j = 0; j < column_b; ++j){
            array_a[i][j] = array_c[i][j];
        }
    }
    *column_a = column_b;
    memory_clean(array_b, row_b);
    memory_clean(array_c, row_a);
}