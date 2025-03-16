#include "dijkstras.h"
using namespace std;

struct Node {
    int vertex;
    int weight;
    
    Node(int v, int w) : vertex(v), weight(w) {}
    
    bool operator>(const Node& other) const {
        return weight > other.weight;
    }
};

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous) {
    int n = G.size();
    
    vector<int> distance(n, INF);
    previous.assign(n, -1);
    vector<bool> visited(n, false);
    
    priority_queue<Node, vector<Node>, greater<Node>> pq;
    pq.push(Node(source, 0));
    distance[source] = 0;
    
    while (!pq.empty()) {
        Node current = pq.top();
        pq.pop();
        
        int u = current.vertex;
        
        if (visited[u]) {
            continue;
        }
        
        visited[u] = true;
        
        for (const auto& e : G[u]) {
            int v = e.dst;
            int weight = e.weight;
            
            if (!visited[v] && distance[u] + weight < distance[v]) {
                distance[v] = distance[u] + weight;
                previous[v] = u;
                pq.push(Node(v, distance[v]));
            }
        }
    }
    
    return distance;
}

vector<int> extract_shortest_path(const vector<int>&, const vector<int>& previous, int destination) {
    vector<int> path;
    for (int v = destination; v != -1; v = previous[v]) {
        path.push_back(v);
    }
    
    reverse(path.begin(), path.end());
    
    return path;
}

void print_path(const vector<int>& v, int total) {
    for (size_t i = 0; i < v.size(); ++i) {
        cout << v[i] << " ";
    }
    cout << "\nTotal cost is " << total << "\n";
}