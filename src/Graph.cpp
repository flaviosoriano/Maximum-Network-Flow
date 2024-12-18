#include "Graph.hpp"

#include <vector>
#include <queue>
#include <set>

#include <climits>
#include <cstring>
#include <iostream>

using namespace std;

Graph::Graph(){
    this->nodes = std::vector<Node>();

    // SuperSouce, needed for FordFulkerson
    this->nodes.push_back(Node(0, 0));
    this->SuperSourceId = 0;

    this->numNodes = 1;
    this->maxCapacity = 0;

    // Not set yet
    this->SuperSinkId = -1;
}

Graph::~Graph(){

}

void Graph::addNode(int id, int capacity){
    this->nodes.push_back(Node(id, capacity));
    this->maxCapacity += capacity;
    this->numNodes++;
}

void Graph::addConnection(int from, int to, int capacity){
    this->nodes[from].connections.push_back(Connection(from, to, capacity));
}

void Graph::printGraph(){
    for(int i = 0; i < (int)this->nodes.size(); i++){
        std::cout << "Node " << this->nodes[i].id << " with capacity " << this->nodes[i].capacity << std::endl;
        for(int j = 0; j < (int)this->nodes[i].connections.size(); j++){
            std::cout 
                << "Connection from " << this->nodes[i].connections[j].from 
                << " to " << this->nodes[i].connections[j].to 
                << " with capacity " << this->nodes[i].connections[j].capacity 
                << " and flow " << this->nodes[i].connections[j].flow
                << std::endl;
        }
    }
}

void Graph::addSuperSink_SuperSource(){

    //Create SuperSink
    this->nodes.push_back(Node((int)this->nodes.size(), INT_MAX));
    this->SuperSinkId = (int)this->nodes.size() - 1;

    //Connect SuperSource to all generators and connect all consumers to SuperSink
    for(int i = 1; i < (numNodes); i++){
        //If node is a generator connect it to SuperSource with infinite connection capacity
        if(this->nodes[i].capacity == 0){
            this->nodes[0].connections.push_back(Connection(SuperSourceId, i, INT_MAX));
        } 
        //If node is a consumer connect it to SuperSink with connection capacity = consumer capacity
        else {
            this->nodes[i].connections.push_back(Connection(i, SuperSinkId, nodes[i].capacity));
        }
    }    
}


/* Returns true if there is a path from source 's' to sink
  't' in residual graph. Also fills parent[] to store the
  path */
bool Graph::BFS(int source, int sink, vector<vector<int>>& residual, vector<int>& parent)
{
    // Create a visited array and mark all vertices as not
    // visited
    vector<bool> visited(numNodes, false);
 
    // Create a queue, enqueue source vertex and mark source
    // vertex as visited
    queue<int> q;
    q.push(source);
    visited[source] = true;
    parent[source] = -1;
 
    // Standard BFS Loop
    while (!q.empty()) {
        int u = q.front();
        q.pop();
 
        for (int v = 0; v <= numNodes; v++) {
            if (visited[v] == false && residual[u][v] > 0) {
                // If we find a connection to the sink node,
                // then there is no point in BFS anymore We
                // just have to set its parent and can return
                // true
                if (v == sink) {
                    parent[v] = u;
                    return true;
                }
                q.push(v);
                parent[v] = u;
                visited[v] = true;
            }
        }
    }
 
    // We didn't reach sink in BFS starting from source, so
    // return false
    return false;
}

void Graph::FordFulkerson(){

    //Create SuperSink and SuperSource to make the graph suitable for FordFulkerson
    addSuperSink_SuperSource();

    int source = SuperSourceId;
    int sink = SuperSinkId;

    //create residual graph
    vector<vector<int>> residual(nodes.size(), vector<int>(nodes.size(), 0));
    for (auto& node : nodes) {
        for (auto& conn : node.connections) {
            residual[conn.from][conn.to] = conn.capacity;
        }
    }

    int maxFlow = 0;
    vector<int> parent(numNodes, -1); // Para armazenar o caminho aumentante
    

    while (true) {
        // Realiza DFS para encontrar um caminho aumentante
        if (!BFS(source, sink, residual, parent))
            break;

        // Determina a capacidade mínima ao longo do caminho aumentante
        int pathFlow = INT_MAX;
        for (int v = sink; v != source; v = parent[v]) {
            int u = parent[v];
            if (residual[u][v] < pathFlow) {
                pathFlow = residual[u][v];
            }
        }

        // Atualiza a matriz residual
        for (int v = sink; v != source; v = parent[v]) {
            int u = parent[v];
            residual[u][v] -= pathFlow; // Reduz a capacidade residual
            residual[v][u] += pathFlow; // Aumenta a capacidade reversa

            // Atualiza o fluxo na conexão original, exceto para SuperSource e SuperSink
            if(v != sink && u != source){
                for(auto& conn : nodes[u].connections){
                    if(conn.to == v){
                        conn.flow += pathFlow;
                    }
                }
            }
        }   

        maxFlow += pathFlow; // Incrementa o fluxo total
    }

    this->maxFlow = maxFlow;

    //Make residual graph available for other methods
    this->residualGraph = residual;
}

 int Graph::getMaxFlow(){
    FordFulkerson();
    return this->maxFlow;
 }

int Graph::getMissingEnergy(){
    return (this->maxCapacity - this->maxFlow);
}

int Graph::getUnusedEnergy(){ 
    int usedEnergy = this->maxFlow;
    int totalEnergy = 0;
    for(auto node : this->nodes){
        if(node.capacity != 0 || node.id == 0) continue;

        for(auto conn : node.connections){
            totalEnergy += conn.capacity;
        }
    }

    return totalEnergy - usedEnergy;
}


void Graph::PrintMaxUsedConnections(){

    int counter = 0;
    vector<Connection> maxUsedConnections;

    for(auto node : this->nodes){
        for(auto conn : node.connections){
            if(conn.flow == conn.capacity){
                counter++;
                maxUsedConnections.push_back(conn);
            }
        }
    }

        for (size_t i = 0; i < maxUsedConnections.size(); ++i) {
        size_t maxIndex = i;
        for (size_t j = i + 1; j < maxUsedConnections.size(); ++j) {
            if (maxUsedConnections[j].capacity > maxUsedConnections[maxIndex].capacity) {
                maxIndex = j;
            }
        }
        // Troca os elementos
        if (maxIndex != i) {
            std::swap(maxUsedConnections[i], maxUsedConnections[maxIndex]);
        }
    }

    cout << counter << endl;
    for(auto conn : maxUsedConnections){
        cout << conn.from << " " << conn.to << " " << conn.capacity << endl;
    }
}
