#ifndef MATRIX_H
#define MATRIX_H
#include <vector>
#include "node.h"

// Matix class for int
class Matrix
{
    int* _array;
    int _nrow;
    int _ncol;
    
    int* _get_pos(int r, int c);
    int* _get_pos(int r, int c) const;
public:
    inline int nrow() const { return _nrow; };
    inline int ncol() const { return _ncol; };
    void set(int value, int r, int c);
    int get(int r, int c) const;
    std::vector<int> get_row(int r) const;
    std::vector<int> get_col(int c) const;
    std::vector<int> get_diagonal() const;

    Matrix(int row, int col);
    ~Matrix();   
    //Copy
    Matrix(const Matrix& src);
    Matrix& operator=(const Matrix& src);
    //Move
    Matrix(Matrix&& src) noexcept;
    Matrix& operator=(Matrix&& src) noexcept;
};

Matrix matrix_from_nodes(const std::vector<Node>& nodes);

void write_matrix(const Matrix& matrix, const char* path);

void write_scores(const Matrix& matrix, const char* path);

#endif //MATRIX_H