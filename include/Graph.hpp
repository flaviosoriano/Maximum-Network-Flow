#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
using namespace std;

struct Connection;

struct Node
{
    int id;
    int capacity;
    int flow;

    std::vector<Connection> connections;

    Node(int id, int capacity){
        this->id = id;
        this->capacity = capacity;
        this->flow = 0;
        connections = std::vector<Connection>();
    };
};

struct Connection
{
    int from;
    int to;
    int capacity;
    int flow;

    Connection(int from, int to, int capacity){
        this->from = from;
        this->to = to;
        this->capacity = capacity;
        this->flow = 0;
    };
};

class Graph
{
    private:

        std::vector<Node> nodes;
        int maxCapacity;
        int numNodes;

        int SuperSourceId;
        int SuperSinkId;

        int maxFlow;
        int missingEnergy;

        vector<vector<int>> residualGraph;

    public:

        Graph();
        ~Graph();
        void addNode(int id, int capacity);
        void addConnection(int from, int to, int capacity);
        void printGraph();

        // Part 1
        void addSuperSink_SuperSource();
        bool BFS(int source, int sink, vector<vector<int>>& residual, vector<int>& parent);
        void FordFulkerson();
        int getMaxFlow();

        // Part 2
        int getMissingEnergy();

        // Part 3
        int getUnusedEnergy();

        void PrintMaxUsedConnections();

};


#endif // GRAPH_HPP