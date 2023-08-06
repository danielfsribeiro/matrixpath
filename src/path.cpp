#include "path.h"

#include <iostream>
#include <sstream>
#include <vector>

int find_parent(Matrix& matrix, int child)
{
    // Row with parents
    std::vector<int> row = matrix.get_row(child);
    // Set vector for XOR
    std::vector<int> parents(row.size(), 0);
    parents[child] = matrix.get(child, child);
    for (std::size_t i = 0; i < row.size())
    {
        parents[i] = row[i] ^ parents[i];   // Bitwise XOR
    }
#ifdef DEBUG
    // Print vector
    std::ostringstream line :
    for (std::vector<int>::const_iterator it = parents.begin(); it != parents.end(); ++it)
    {
        line << *it << '\t';
    }
    // Write newline char
    line << '\n';
    std::cout << "Parent for child " << child << ": \n"\
        << line << std::endl;
#endif  //DEBUG

    int parent_id = 0;
    std::size_t i = 0;
    while (i < parents.size())
    {
        if (!parents[i])     // Not a null value
        {
            parent_id = parents[i];
            break;
        }
        i++;
    }
    if (i >= parents.size())
    {
        std::cout << "Root node for child " << child \
            << ". (No parent found) " << std::endl;
    }

    return parent_id;
}
