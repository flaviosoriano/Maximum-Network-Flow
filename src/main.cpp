#include "Graph.hpp"

#include <iostream>

using namespace std;

int main (void){

    //stdin = freopen("inputs/testCase06.txt", "r", stdin);

    int numNodes, numConnections;
    cin >> numNodes;
    cin >> numConnections;

    Graph graph = Graph();
    
    for(int i = 0; i < numNodes; i++){
        int id, capacity;
        cin >> id;
        cin >> capacity;
        graph.addNode(id, capacity);
    }
    for(int i = 0; i < numConnections; i++){
        int from, to, capacity;
        cin >> from;
        cin >> to;
        cin >> capacity;
        graph.addConnection(from, to, capacity);
    }
    //Part 1
    int maxFlow = graph.getMaxFlow();
    cout << maxFlow << endl;
    //Part2
    int missingEnergy = graph.getMissingEnergy();
    cout << missingEnergy << endl;
    //Part3
    int unusedEnergy = graph.getUnusedEnergy();
    cout << unusedEnergy << endl;
    
    graph.PrintMaxUsedConnections();

    return 0;
}