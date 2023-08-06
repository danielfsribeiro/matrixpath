#include <filesystem>
#include <iostream>
#include <string>
#include <vector>

#include "matrix.h"
#include "node.h"
#include "path.h"

int main(int argc, char* argv[])
{
    // If no args provided
    if(argc <= 1)
    {
        std::cout << "No arguments provided!\n";
        std::cout << "Usage:\n";
        std::cout << "matrixpath 'path/to/tree/file.csv' ['path/to/output_folder']\n";
        std::cout << "\nfile.csv must be TAB delimited\n";
        
        std::cout << "\nCurrent program args:\n";
        for(int i = 0; i < argc; i++)
        {
            std::cout << argv[i] << " ";
        }
        std::cout << std::endl;
        
        return 0;
    }
    
#ifdef DEBUG
    std::cout << "Program args:\n";
    for(int i = 0; i < argc; i++)
    {
        std::cout << argv[i] << " ";
    }
    std::cout << "\n" << std::endl;
#endif //DEBUG
    
    // Check if path is valid
    std::filesystem::path in_path = argv[1]; 
    if(!std::filesystem::exists(in_path) || !in_path.has_filename())
    {
       std::cout << "File: " << argv[1] << " does not exist or is not a file" << std::endl;
       return 1;
    }
    
    // Extract node information
    std::vector<Node> nodes = get_nodes(argv[1]);
#ifdef DEBUG
    for(std::size_t i = 0; i < nodes.size(); i++)
    {
        std::cout << "Node id: " << nodes[i].id << " Parent id: " << nodes[i].parent << "\n";
    }
    std::cout << std::endl;
#endif //DEBUG
    
    // Create Matrix from nodes
    Matrix matrix(matrix_from_nodes(nodes));
    // Calculate score matrix
    Matrix score_matrix(build_score_matrix(matrix));
    
    // Write test matrices
    // Tree matrix
    std::filesystem::path out_path = "./";     // Default out folder to WD
    std::string out_file_name = std::string(in_path.stem().c_str()) + "_matrix.csv";
    if(argc >= 3)
    {
        //Write to given output directory
        out_path = argv[2];
    }
    out_path = out_path / out_file_name;
    write_matrix(matrix, out_path.c_str());
    
    // Score matrix
    out_path = "./";     // Default out folder to WD
    out_file_name = std::string(in_path.stem().c_str()) + "_score_matrix.csv";
    if(argc >= 3)
    {
        //Write to given output directory
        out_path = argv[2];
    }
    out_path = out_path / out_file_name;
    write_matrix(score_matrix, out_path.c_str());
    
    // Scores table
    out_path = "./";     // Default out folder to WD
    out_file_name = std::string(in_path.stem().c_str()) + "_scores.csv";
    if(argc >= 3)
    {
        //Write to given output directory
        out_path = argv[2];
    }
    out_path = out_path / out_file_name;
    write_scores(score_matrix, out_path.c_str());
    
    return 0;
}