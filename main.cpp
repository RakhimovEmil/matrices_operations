#include <iostream>
#include <cstring>
#include "matrices.hpp"

int main(int argc, char ** argv) {
    float **array_to_move_a = nullptr, **array_to_move_b = nullptr;
    std::size_t curr_a_row_size = 0, curr_a_column_size = 0, curr_b_row_size = 0, curr_b_column_size = 0;
    if (argc % 2 == 1){
        std::cerr << "missing matris";
        return 1;
    }
    for (int i = 1; i < argc; ++i){
        if (i % 2 != 0) {
            if (i == 1) {
                array_to_move_a = get_matrix_from_file(argv[i], &curr_a_row_size, &curr_a_column_size);
                if (array_to_move_a == nullptr) {
                    return 1;
                }
            } else {
                array_to_move_b = get_matrix_from_file(argv[i], &curr_b_row_size, &curr_b_column_size);
                if (array_to_move_b == nullptr) {
                    memory_clean(array_to_move_a, curr_a_row_size);
                    return 1;
                }
                std::string right_add = "--add";
                if (argv[i - 1] == right_add) {
                    if (curr_a_row_size != curr_b_row_size || curr_a_column_size != curr_b_column_size) {
                        memory_clean(array_to_move_a, curr_a_row_size);
                        memory_clean(array_to_move_b, curr_b_row_size);
                        std::cerr << "matrices must be the same size";
                        return 2;
                    }
                    get_sum(array_to_move_a, array_to_move_b,
                            curr_a_row_size, curr_a_column_size);
                } else {
                    if (curr_a_column_size != curr_b_row_size) {
                        memory_clean(array_to_move_a, curr_a_row_size);
                        memory_clean(array_to_move_b, curr_b_row_size);
                        std::cerr << "these matrices cannot be multiplied";
                        return 1;
                    }
                    get_mult(array_to_move_a, array_to_move_b,
                             curr_a_row_size, &curr_a_column_size,
                             curr_b_row_size, curr_b_column_size);
                }
            }
        } else {
            if (!if_add_or_mult(argv[i])){
                memory_clean(array_to_move_a, curr_a_row_size);
                std::cerr << "you need to write the sign in the correct format (--add/mult)!";
                return 2.0;
            }
        }
    }
    std::cout << curr_a_row_size << " " << curr_a_column_size << std::endl;
    for (std::size_t i = 0; i < curr_a_row_size; ++i){
        for (std::size_t j = 0; j < curr_a_column_size; ++j){
            std::cout << array_to_move_a[i][j] << " ";
        }
        std::cout << std::endl;
    }
    memory_clean(array_to_move_a, curr_a_row_size);
    return 0;
}