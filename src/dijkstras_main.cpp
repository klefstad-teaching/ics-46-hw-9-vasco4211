#include "dijkstras.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " file " << endl;
    }
    
    Graph G;
    file_to_graph(argv[1], G);
    
    int source = 0;
    
    vector<int> previous;
    vector<int> distances = dijkstra_shortest_path(G, source, previous);
    
    for (int i = 0; i < G.numVertices; i++) {
        vector<int> v = extract_shortest_path(distances, previous, i);
        print_path(v, distances[i] == INF ? -1 : distances[i]);
    }
    
    return 0;
}