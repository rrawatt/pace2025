#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <sstream>
#include <algorithm>
#include <chrono>

using namespace std::chrono;
using namespace std;

void parse_graph(const string &filename, vector<vector<int>> &adj_list, int &n, int &m) {
    ifstream infile(filename);
    string line;
    
    while (getline(infile, line)) {
        if (line[0] == 'p') {
            stringstream ss(line);
            string tmp;
            ss >> tmp >> tmp >> n >> m;
            adj_list.resize(n + 1);  
            break;
        }
    }

    while (getline(infile, line)) {
        if (line[0] == 'c' || line.empty()) {
            continue; 
        }

        int u, v;
        stringstream ss(line);  
        ss >> u >> v;

        adj_list[u].push_back(v);
        adj_list[v].push_back(u);
    }
}

unordered_set<int> optimized_greedy_dominating_set(const vector<vector<int>> &adj_list, int n) {
    unordered_set<int> dominating_set;
    unordered_set<int> uncovered_vertices;

    for (int v = 1; v <= n; ++v) {
        uncovered_vertices.insert(v);
    }

    vector<int> cover_count(n + 1, 0);
    while (!uncovered_vertices.empty()) {
        int best_vertex = -1;
        int best_cover = -1;

        for (int v : uncovered_vertices) {
            int count = 0;
            for (int neighbor : adj_list[v]) {
                if (uncovered_vertices.count(neighbor)) {
                    count++;
                }
            }
            cover_count[v] = count;
            
            if (count > best_cover) {
                best_cover = count;
                best_vertex = v;
            }
        }

        dominating_set.insert(best_vertex);
        uncovered_vertices.erase(best_vertex);

        for (int neighbor : adj_list[best_vertex]) {
            uncovered_vertices.erase(neighbor);
        }
    }

    return dominating_set;
}

void write_solution(const string &filename, const unordered_set<int> &dominating_set) {
    ofstream outfile(filename);
    outfile << dominating_set.size() << endl;
    for (int vertex : dominating_set) {
        outfile << vertex << endl;
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " <graph_filename> <solution_filename>" << endl;
        return 1;
    }

    string graph_filename = argv[1];
    string solution_filename = argv[2];

    int n, m;
    vector<vector<int>> adj_list;

    parse_graph(graph_filename, adj_list, n, m);

    auto start_time = high_resolution_clock::now();

    unordered_set<int> dominating_set = optimized_greedy_dominating_set(adj_list, n);

    auto end_time = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end_time - start_time);

    write_solution(solution_filename, dominating_set);

    cout << "Time taken: " << duration.count() << " microseconds." << endl;

    return 0;
}
