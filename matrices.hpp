#pragma once
#include <iostream>

bool if_add_or_mult(char *my_string);

void memory_clean(float** memory, size_t size);

float ** get_matrix_from_file(char const *file_name_a, std::size_t *size_row, std::size_t *size_column);

void get_sum(float **array_a, float **array_b,
            std::size_t row_a, std::size_t column_a);

void get_mult(float **array_a, float **array_b,
             std::size_t row_a, std::size_t *column_a,
             std::size_t row_b, std::size_t column_b);