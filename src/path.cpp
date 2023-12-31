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
    // Get the value of the child
    // If the get() value is 0 , id is not being used 
    parents[child] = matrix.get(child, child);
    for (std::size_t i = 0; i < row.size(); i++)
    {
        parents[i] = row[i] ^ parents[i];   // Bitwise XOR
    }
#ifdef DEBUG
    // Print vector
    std::ostringstream line;
    for (std::vector<int>::const_iterator it = parents.begin(); it != parents.end(); ++it)
    {
        line << *it << ' ';
    }
    // Write newline char
    line << '\n';
    std::cout << "Parent for child " << child << ": \n"\
        << line.str() << std::endl;
#endif  //DEBUG

    int parent_id = 0;
    std::size_t i = 0;
    while (i < parents.size())
    {
        if (parents[i] != 0)     // Not a null value
        {
            parent_id = i;
            break;
        }
        i++;
    }
    if (i >= parents.size())
    {
        parent_id = -1;     // -1 id to say it was not found
#ifdef DEBUG
        std::cout << "Root node for child " << child \
            << ". (No parent found) " << std::endl;
#endif //DEBUG
    }

    return parent_id;
}

Matrix build_score_matrix(Matrix& matrix)
{
    Matrix score_matrix(matrix);
    // Walk from every Node until root node
    for (int i = 0; i < score_matrix.nrow(); i++)
    {
        int child = i;
        int parent = find_parent(score_matrix, i);
        //if(parent == -1)   // Not a root (to account for unenxixting id on the tree)
        //{
        //    continue;
        //}
        while (child != parent && parent != -1)  // Not a root node
        {
            // Set score +1
            int score = score_matrix.get(parent, parent) + 1;
            score_matrix.set(score, parent, parent);

            // Update
            child = parent;     // Move up 1 node. Child becomes old parent
            parent = find_parent(score_matrix, child);      // Find next parent
        }
    }

    return score_matrix;
}
