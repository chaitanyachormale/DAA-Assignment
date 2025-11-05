#include <iostream>
#include <vector>
#include <climits>
using namespace std;

int main() {
    int n;
    cout << "Enter number of vertices: ";
    cin >> n;

    vector<vector<int>> graph(n, vector<int>(n));
    cout << "Enter adjacency matrix (0 if no edge, weight otherwise):" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> graph[i][j];
        }
    }

    int source = 0;        
    int destination = n - 1; 

    vector<int> cost(n, INT_MAX); 
    vector<int> next(n, -1);     

    cost[destination] = 0; 


    for (int i = n - 2; i >= 0; i--) {
        int minCost = INT_MAX;
        int minVertex = -1;
        for (int j = i + 1; j < n; j++) {
            if (graph[i][j] > 0 && cost[j] != INT_MAX) {
                int tempCost = graph[i][j] + cost[j];
                if (tempCost < minCost) {
                    minCost = tempCost;
                    minVertex = j;
                }
            }
        }
        cost[i] = minCost;
        next[i] = minVertex;
    }

    cout << "Shortest distance from " << source << " to " << destination << " = " << cost[source] << "\n";

    cout << "Path: ";
    int v = source;
    cout << v;
    while (v != destination && next[v] != -1) {
        v = next[v];
        cout << " -> " << v;
    }
    cout << "\n";

    return 0;
}
// Enter number of vertices: 5
// Enter adjacency matrix (0 if no edge, weight otherwise):
// 0 2 1 0 0
// 0 0 0 2 0
// 0 0 0 3 1
// 0 0 0 0 1
// 0 0 0 0 0
// Shortest distance from 0 to 4 = 4
// Path: 0 -> 2 -> 4

