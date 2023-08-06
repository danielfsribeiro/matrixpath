#ifndef NODE_H
#define NODE_H
#include <vector>

struct Node
{
    int id;
    int parent;
    
    Node(int id, int parent);
};

std::vector<Node> get_nodes(const char* path);

#endif //NODE_H