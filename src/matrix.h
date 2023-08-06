#ifndef MATRIX_H
#define MATRIX_H
#include <vector>
#include "node.h"

// Matix class for int
class Matrix
{
    int* _array;
    unsigned _nrow;
    unsigned _ncol;
    
    int* _get_pos(unsigned r, unsigned c);
public:
    inline unsigned nrow(){ return _nrow; };
    inline unsigned ncol(){ return _ncol; };
    void set(int value, unsigned r, unsigned c);
    int get(unsigned r, unsigned c);
    std::vector<int> get_row(unsigned r);
    std::vector<int> get_col(unsigned c);

    Matrix(unsigned row, unsigned col);
    ~Matrix();   
    //Copy
    Matrix(const Matrix& src);
    Matrix& operator=(const Matrix& src);
    //Move
    Matrix(Matrix&& src) noexcept;
    Matrix& operator=(Matrix&& src) noexcept;
};

Matrix matrix_from_nodes(std::vector<Node>& nodes);

void write_matrix(Matrix& matrix, const char* path);

#endif //MATRIX_H