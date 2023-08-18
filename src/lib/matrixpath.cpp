#include "../config.h"
#include "../../include/matrixpath.h"

#include <filesystem>
#include <iostream>
#include <string>
#include <vector>

#include "../matrix.h"
#include "../node.h"
#include "../path.h"
  

std::vector<int> matrixpath(const std::vector<int>& nodes,
                            bool out_tree_matrix, 
                            bool out_score_matrix, 
                            bool out_score_table, 
                            const std::string& out_path)
{
    // Check paths
    if((out_tree_matrix || out_score_matrix || out_score_table) && !out_path.empty())
    {
        std::cout << "Warning: destination path not provided. \
        Will use current path as destination " << "(" << std::filesystem::current_path() << ")." << std::endl;
    }
    
    // Check if path is valid
    std::filesystem::path dest_path(out_path); 
    if(!out_path.empty() && !std::filesystem::exists(dest_path))
    {
       std::cout << "Warning: destination path does not exist "<< "(" << out_path << ")\n"\
       << "Will use current path as destination " << "(" << std::filesystem::current_path() << ")." << std::endl;
       dest_path = std::filesystem::current_path();
    }
    
    // Extract node information
    std::vector<Node> node_list = get_nodes(nodes);
#ifdef DEBUG
    for(std::size_t i = 0; i < node_list.size(); i++)
    {
        std::cout << "Node id: " << node_list[i].id << " Parent id: " << node_list[i].parent << "\n";
    }
    std::cout << std::endl;
#endif //DEBUG
    
    // Create Matrix from nodes
    Matrix matrix(matrix_from_nodes(node_list));
    // Calculate score matrix
    Matrix score_matrix(build_score_matrix(matrix));
    
    // Write test matrices
    // Tree matrix
    std::filesystem::path out_file_name = dest_path;
    if(out_tree_matrix)
    {
        std::filesystem::path out_file_name = dest_path / "tree_matrix.tsv";
        write_matrix(matrix, out_file_name.c_str());
    }
    if(out_score_matrix)
    {
        out_file_name = dest_path / "score_matrix.tsv";
        write_matrix(score_matrix, out_file_name.c_str());
    }
    if(out_score_table)
    {
        out_file_name = dest_path / "score_table.tsv";
        write_scores(score_matrix, out_file_name.c_str());
    }
    
    // Scores vector
    std::vector<int> diagonal = score_matrix.get_diagonal(); 
    std::vector<int> scores = std::vector<int>();
    scores.reserve(diagonal.size() * 2);
    int id = 0;
    while(id < diagonal.size())
    {
        scores.push_back(id);
        scores.push_back(diagonal[id]);
        
        ++id;
    }
    
#ifdef DEBUG
    std::cout << "Result on C++ side: ";
    for(std::size_t i = 0; i < scores.size(); i++)
    {
        std::cout << scores[i] << " ";
    }
    std::cout << std::endl;
#endif  //DEBUG
    
    return scores;
}
    
