#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int to;
    double cost;
};

class SwiftCargo {
private:
    int totalNodes;
    int stages;
    vector<vector<Edge>> graph;
    vector<double> minCost;
    vector<int> nextNode;

public:
    SwiftCargo(int nodes, int stages) {
        this->totalNodes = nodes;
        this->stages = stages;
        graph.resize(nodes + 1);
        minCost.assign(nodes + 1, 1e9);
        nextNode.assign(nodes + 1, -1);
    }

    void addRoute(int u, int v, double cost) {
        graph[u].push_back({v, cost});
    }

    // Use Dynamic Programming to find optimal route in a multistage graph
    void findOptimalRoute(int source, int destination) {
        minCost[destination] = 0; // base case

        // Traverse backwards from last to first node
        for (int i = totalNodes; i >= 1; i--) {
            for (auto &edge : graph[i]) {
                if (minCost[i] > edge.cost + minCost[edge.to]) {
                    minCost[i] = edge.cost + minCost[edge.to];
                    nextNode[i] = edge.to;
                }
            }
        }

        // Display optimal path
        cout << "\nOptimal Route (Source → Destination): ";
        int current = source;
        cout << current;
        while (nextNode[current] != -1) {
            cout << " → " << nextNode[current];
            current = nextNode[current];
        }
        cout << "\nMinimum Cost: " << minCost[source] << "\n";
    }

    // Simulate real-time updates (e.g., traffic, weather, fuel cost)
    void updateRouteCost(int u, int v, double newCost) {
        for (auto &edge : graph[u]) {
            if (edge.to == v) {
                edge.cost = newCost;
                cout << "Updated route (" << u << " → " << v << ") with new cost: " << newCost << "\n";
                return;
            }
        }
        cout << "Route not found!\n";
    }

    // Process multiple delivery requests in batch
    void batchProcess(const vector<pair<int, int>> &requests) {
        for (auto &req : requests) {
            cout << "\n=== Processing Delivery Request: " << req.first << " → " << req.second << " ===";
            findOptimalRoute(req.first, req.second);
        }
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int nodes, stages, edges;
    cout << "Enter total number of nodes, stages, and routes: ";
    cin >> nodes >> stages >> edges;

    SwiftCargo cargo(nodes, stages);

    cout << "Enter routes (from to cost):\n";
    for (int i = 0; i < edges; i++) {
        int u, v;
        double cost;
        cin >> u >> v >> cost;
        cargo.addRoute(u, v, cost);
    }

    int source, destination;
    cout << "Enter source and destination node: ";
    cin >> source >> destination;

    cargo.findOptimalRoute(source, destination);

    // Real-time update simulation
    cout << "\n--- Simulating real-time updates (enter -1 to stop) ---\n";
    while (true) {
        int u;
        cout << "Enter route (u v newCost): ";
        cin >> u;
        if (u == -1) break;
        int v;
        double newCost;
        cin >> v >> newCost;
        cargo.updateRouteCost(u, v, newCost);
        cargo.findOptimalRoute(source, destination);
    }

    // Batch requests
    vector<pair<int, int>> requests = {{1, destination}, {2, destination}};
    cargo.batchProcess(requests);

    return 0;
}
