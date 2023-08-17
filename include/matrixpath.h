#ifndef MATRIXPATH_H
#define MATRIXPATH_H
#include <string>
#include <vector>

#ifdef __cplusplus
    extern "C" {
#endif  

//nodes should be a 2D matrix of shape m (node id) x n (parent id) [[id1, p1], [id2, p2], [id3, p3],...] 
std::vector<int> matrixpath(const std::vector<int>& nodes, 
                            bool tree_matrix = false, 
                            bool score_matrix = false, 
                            bool score_table = false, 
                            const std::string& path = std::string());
#ifdef __cplusplus
    }
#endif

#endif //MATRIXPATH_H