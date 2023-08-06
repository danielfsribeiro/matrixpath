#include "matrix.h"

#include <cstring>
#include <fstream>
#include <filesystem>
#include <iostream>
#include <new>
#include <utility>


int* Matrix::_get_pos(unsigned r, unsigned c)
{
    return _array + (_nrow * r + c % _ncol);
}

void Matrix::set(int value, unsigned r, unsigned c)
{
    if(r < _nrow && c < _ncol)
    {
        *(_get_pos(r, c)) = value;
    }
}

int Matrix::get(unsigned r, unsigned c)
{
    if(r < _nrow && c < _ncol)
    {
        return *(_get_pos(r, c));
    }
    std::cout << "Warning: requesting non-existant coordinate: "\
    << "(" << r << ", " << c << "). " \
    "Will return value 0.\n"<< std::endl;
    return 0;
}

std::vector<int> Matrix::get_row(unsigned r)
{
    std::vector<int> row;
    if(r < _nrow)
    {
        row.resize(_nrow);
        int* begin = _array + _nrow * r;
        std::memcpy(row.data(), begin, sizeof(int) * _nrow);
        
        return row;
    }
    std::cout << "Warning: requesting non-existant row coordinate: "\
    << r << ". " \
    "Will return empty row.\n"<< std::endl;
    
    return row;
}

std::vector<int> Matrix::get_col(unsigned c)
{
    std::vector<int> col{};
    if(c < _ncol)
    {
        col.reserve(_ncol);
        for(unsigned i = 0; i < _nrow; i++)
        {
            col.push_back(*(_get_pos(i, c)));
        }
        
        return col;
    }
    std::cout << "Warning: requesting non-existant col coordinate: "\
    << c << ". " \
    "Will return empty col.\n"<< std::endl;
    
    return col;
}

Matrix::Matrix(unsigned row, unsigned col)
: _array(nullptr), _nrow(row), _ncol(col)
{
    _array = new int[_nrow * _ncol]{};  // zero-ed array
}

Matrix::~Matrix()
{
    delete[] _array;
}

Matrix::Matrix(const Matrix& src)
: _array(nullptr), _nrow(src._nrow), _ncol(src._ncol)
{
    if(src._array)
    {
        _array = new int[_nrow * _ncol]{};  // zero-ed array
        std::memcpy(_array, src._array, sizeof(int) * _nrow * _ncol);
    }
}

Matrix& Matrix::operator=(const Matrix& src)
{
    if(src._array)
    {
        _nrow = src._nrow;
        _ncol = src._ncol;
        _array = new int[_nrow * _ncol]{};
        std::memcpy(_array, src._array, sizeof(int) * _nrow * _ncol);    
    }
    else
    {
        _array = nullptr; 
        _nrow = 0;
        _ncol = 0;
    }
    
    return *this;
}

Matrix::Matrix(Matrix&& src) noexcept
: _array(std::move(src._array)), _nrow(std::move(src._nrow)), _ncol(std::move(src._ncol))
{
    src._array = nullptr;
    src._nrow = 0;
    src._ncol = 0;
}

Matrix& Matrix::operator=(Matrix&& src) noexcept
{
    if(this != &src)
    {
        _array = std::move(src._array);
        _nrow = std::move(src._nrow); 
        _ncol = std::move(src._ncol);
        
        src._array = nullptr;
        src._nrow = 0;
        src._ncol = 0;
    }
    
    return *this;
}


// Free functions
// Write TAB delimited matrix file
Matrix matrix_from_nodes(std::vector<Node>& nodes)
{
    // Find biggest id in Nodes vector
    int max = 0;
    for(std::size_t i = 0; i < nodes.size(); i++)
    {
        if(nodes[i].id > max)
        {
            max = nodes[i].id;
        }
        if(nodes[i].parent > max)
        {
            max = nodes[i].parent;
        }
    }
    max = max + 1;  // 0-based index
    // Fill Matrix with ids
    Matrix matrix(max, max);
    for(std::size_t i = 0; i < nodes.size(); i++)
    {
        // Diagonal
        matrix.set(1, nodes[i].id, nodes[i].id);  
        //Parent info: row = child id, column = parent.id
        matrix.set(1, nodes[i].id, nodes[i].parent);    
    }
    
    return matrix;
}

void write_matrix(Matrix& matrix, const char* path)
{
    // Open file
    std::filesystem::path out_path(path);
    std::ofstream ofile;
    ofile.open(out_path);
    if(ofile.is_open())
    {
        unsigned line = 0;
        // Write lines
        while(line < matrix.nrow())
        {
            std::vector<int> row = matrix.get_row(line);
            std::vector<int>::const_iterator it = row.begin();
            // Write line contents
            for(; it != row.end(); ++it)
            {
                ofile << *it << '\t';
            }
            // Write newline char
            ofile << '\n';
            
            //delete pp;
            line++;
        }
    }
    ofile.close();
}