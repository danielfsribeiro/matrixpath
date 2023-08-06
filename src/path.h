#ifndef PATH_H
#define PATH_H
#include "matrix.h"

int find_parent(Matrix& matrix, int child);

Matrix build_score_matrix(Matrix& tree_matrix);

#endif //PATH_H