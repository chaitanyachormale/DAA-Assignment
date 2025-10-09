#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <algorithm>
#include <climits>

using namespace std;

struct Edge {
    int to;
    int weight;
    Edge(int to, int weight) : to(to), weight(weight) {}
};

class Graph {
    int V;
    vector<vector<Edge>> adj;

public:
    Graph(int V) : V(V), adj(V) {}

    void addEdge(int u, int v, int weight) {
        adj[u].emplace_back(v, weight);
        adj[v].emplace_back(u, weight); // Assuming bidirectional roads
    }

    void updateEdgeWeight(int u, int v, int newWeight) {
        // Update edge from u to v
        for (auto& edge : adj[u]) {
            if (edge.to == v) {
                edge.weight = newWeight;
                break;
            }
        }
        // Update edge from v to u (bidirectional)
        for (auto& edge : adj[v]) {
            if (edge.to == u) {
                edge.weight = newWeight;
                break;
            }
        }
    }

    void dijkstra(int src, const set<int>& hospitals) {
        vector<int> dist(V, INT_MAX);
        vector<int> parent(V, -1);
        dist[src] = 0;

        // Min-heap priority queue: pair(distance, node)
        priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> pq;
        pq.push({0, src});

        while (!pq.empty()) {
            auto [d, u] = pq.top();
            pq.pop();

            if (d > dist[u]) continue;

            for (const Edge& edge : adj[u]) {
                int v = edge.to;
                int w = edge.weight;
                if (dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                    parent[v] = u;
                    pq.push({dist[v], v});
                }
            }
        }

        // Find nearest hospital
        int minDist = INT_MAX;
        int nearestHospital = -1;
        for (int h : hospitals) {
            if (dist[h] < minDist) {
                minDist = dist[h];
                nearestHospital = h;
            }
        }

        if (nearestHospital == -1) {
            cout << "No hospital reachable!" << endl;
            return;
        }

        cout << "Nearest hospital: Node " << nearestHospital << endl;
        cout << "Shortest travel time: " << minDist << " minutes" << endl;

        // Print path from source to nearest hospital
        vector<int> path;
        for (int at = nearestHospital; at != -1; at = parent[at]) {
            path.push_back(at);
        }
        reverse(path.begin(), path.end());

        cout << "Optimal path: ";
        for (size_t i = 0; i < path.size(); i++) {
            cout << path[i];
            if (i != path.size() - 1) cout << " -> ";
        }
        cout << endl;
    }
};

int main() {
    int V, E;
    cout << "Enter number of intersections (nodes): ";
    cin >> V;

    Graph g(V);

    cout << "Enter number of roads: ";
    cin >> E;

    cout << "Enter road details (u v travelTime):" << endl;
    for (int i = 0; i < E; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        g.addEdge(u, v, w);
    }

    int src;
    cout << "Enter ambulance source node: ";
    cin >> src;

    int hCount;
    cout << "Enter number of hospitals: ";
    cin >> hCount;

    set<int> hospitals;
    cout << "Enter hospital node indices:" << endl;
    for (int i = 0; i < hCount; i++) {
        int h;
        cin >> h;
        hospitals.insert(h);
    }

    // Run Dijkstra for initial shortest path
    g.dijkstra(src, hospitals);

    // Dynamic update of edge weight (traffic changes)
    cout << "\nUpdate traffic on road (u v newTravelTime):" << endl;
    cout << "Enter u v newWeight: ";
    int u, v, newW;
    cin >> u >> v >> newW;

    g.updateEdgeWeight(u, v, newW);

    cout << "Recalculating shortest path after traffic update..." << endl;
    g.dijkstra(src, hospitals);

    return 0;
}
//Enter number of intersections (nodes): 6
// Enter number of roads: 7
// Enter road details (u v travelTime):
// 0 1 4
// 0 2 2
// 1 2 5
// 1 3 10
// 2 4 3
// 4 3 4
// 3 5 11
// Enter ambulance source node: 0
// Enter number of hospitals: 2
// Enter hospital node indices:
// 3
// 5

// Update traffic on road (u v newTravelTime):
// Enter u v newWeight: 2 4 6
//o/p:
// Nearest hospital: Node 3
// Shortest travel time: 9 minutes
// Optimal path: 0 -> 2 -> 4 -> 3

// Recalculating shortest path after traffic update...
// Nearest hospital: Node 3
// Shortest travel time: 12 minutes
// Optimal path: 0 -> 1 -> 3
