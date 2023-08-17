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

//Node
std::vector<Node> get_nodes(const std::vector<int>& node_info)
{
    std::vector<Node> nodes;
    if(node_info.size() % 2 != 0)
    {
        std::cout << "Error: node info list is not even numbered "\
        << "(" << node_info.size() << " items)" << std::endl;
        return nodes;
    }
    
    for(std::size_t i = 0; i<node_info.size(); i += 2)
    {
        nodes.push_back(Node(node_info[i], node_info[i + 1]));
    }
    return nodes;
}