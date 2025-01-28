#include <iostream>
#include <fstream>
#include <cstdlib>
#include <set>
#include <ctime>
#include <vector>
#include <utility>

using namespace std;

vector<pair<int, int>> generate_random_graph(int n, int m) {
    set<pair<int, int>> edges;  // Using set to avoid duplicate edges

    while (edges.size() < m) {
        int u = rand() % n + 1;  // Random number between 1 and n
        int v = rand() % n + 1;  // Random number between 1 and n

        if (u != v) {
            if (u > v) swap(u, v);  // Ensure u < v for undirected graph representation
            edges.insert({u, v});
        }
    }

    vector<pair<int, int>> edge_list(edges.begin(), edges.end());
    return edge_list;
}

void write_graph_to_file(const string& filename, int n, int m, const vector<pair<int, int>>& edges) {
    ofstream out_file(filename);
    
    if (!out_file) {
        cerr << "Error opening file for writing!" << endl;
        return;
    }

    out_file << "c Randomly generated undirected graph\n";
    
    out_file << "p ds " << n << " " << m << "\n";
    
    for (const auto& edge : edges) {
        out_file << edge.first << " " << edge.second << "\n";
    }

    out_file.close();
}

int main() {
    srand(time(0));

    int n = 1000000;  //Number of vertices
    int m = 10000000; //Number of edges

    vector<pair<int, int>> edges = generate_random_graph(n, m);

    string output_file = "graph.gr";
    write_graph_to_file(output_file, n, m, edges);

    cout << "Graph has been written to " << output_file << endl;

    return 0;
}
