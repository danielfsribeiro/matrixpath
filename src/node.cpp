#include "node.h"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

Node::Node(int id, int parent)
: id(id), parent(parent)
{   }

std::vector<Node> get_nodes(const char* path)
{
    std::vector<Node> nodes;
    std::ifstream tree_file;
    tree_file.open(path);
    if(tree_file.is_open())
    {
#ifdef DEBUG
        std::cout << "Create matrix from: " << path << std::endl;
#endif //DEBUG
        std::string line;
        while(std::getline(tree_file, line))
        {
            // Read line into temporary buffer
            std::istringstream buffer(line);
            // Read int into a temp Node
            int id, parent;
            buffer >> id;
            buffer >> parent;
            nodes.push_back(Node(id, parent));
        }
    }
    tree_file.close();
    
    return nodes;
}