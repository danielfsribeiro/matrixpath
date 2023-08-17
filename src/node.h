#ifndef NODE_H
#define NODE_H
#include <string>
#include <vector>

struct Node
{
    int id;
    int parent;
    
    Node(int id, int parent);
};

std::vector<Node> get_nodes(const char* path);

std::vector<Node> get_nodes(const std::vector<int>& node_info);

#endif //NODE_H