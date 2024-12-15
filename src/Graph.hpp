#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>


struct Connection;

struct Node
{
    int id;
    int capacity;
    std::vector<Connection> connections;

    Node(int id, int capacity){
        this->id = id;
        this->capacity = capacity;
        connections = std::vector<Connection>();
    };
};

struct Connection
{
    int from;
    int to;
    int capacity;

    Connection(int from, int to, int capacity){
        this->from = from;
        this->to = to;
        this->capacity = capacity;
    };
};

class Graph
{
    private:
        std::vector<Node> nodes;

    public:
        Graph();
        ~Graph();
        void addNode(int id, int capacity);
        void addConnection(int from, int to, int capacity);
        void printGraph();
};


#endif // GRAPH_HPP