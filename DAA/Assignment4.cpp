// Name:Chaitanya Ashok Chormale
//PRN:123B1F014
#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int to;
    double weight; 
};

class Graph {
    int V; 
    vector<vector<Edge>> adj; 

public:
    Graph(int vertices) {
        V = vertices;
        adj.resize(V);
    }

    
    void addEdge(int u, int v, double w) {
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    
    void updateWeight(int u, int v, double newWeight) {
        for (auto &e : adj[u]) {
            if (e.to == v) {
                e.weight = newWeight;
                break;
            }
        }
        for (auto &e : adj[v]) {
            if (e.to == u) {
                e.weight = newWeight;
                break;
            }
        }
    }

   
    vector<double> dijkstra(int src, vector<int> &parent) {
        vector<double> dist(V, DBL_MAX);
        parent.assign(V, -1);

        using pii = pair<double, int>;
        priority_queue<pii, vector<pii>, greater<pii>> pq;

        dist[src] = 0.0;
        pq.push({0.0, src});

        while (!pq.empty()) {
            int u = pq.top().second;
            double d = pq.top().first;
            pq.pop();

            if (d > dist[u])
                continue;

            for (auto &edge : adj[u]) {
                int v = edge.to;
                double weight = edge.weight;

                if (dist[v] > dist[u] + weight) {
                    dist[v] = dist[u] + weight;
                    parent[v] = u;
                    pq.push({dist[v], v});
                }
            }
        }
        return dist;
    }

    
    void printPath(int dest, const vector<int> &parent) {
        if (parent[dest] == -1) {
            cout << dest;
            return;
        }
        printPath(parent[dest], parent);
        cout << " -> " << dest;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int V, E;
    cout << "Enter number of intersections (nodes): ";
    cin >> V;
    cout << "Enter number of roads (edges): ";
    cin >> E;

    Graph city(V);

    cout << "\nEnter roads (u v travel_time_in_minutes):\n";
    for (int i = 0; i < E; i++) {
        int u, v;
        double w;
        cin >> u >> v >> w;
        city.addEdge(u, v, w);
    }

    int src;
    cout << "\nEnter ambulance location (source node): ";
    cin >> src;

    int numHospitals;
    cout << "Enter number of hospitals: ";
    cin >> numHospitals;

    vector<int> hospitals(numHospitals);
    cout << "Enter hospital node numbers:\n";
    for (int i = 0; i < numHospitals; i++)
        cin >> hospitals[i];

    vector<int> parent;
    vector<double> dist = city.dijkstra(src, parent);

    cout << "\nShortest travel times from source " << src << ":\n";
    for (int i = 0; i < V; i++)
        cout << "Node " << i << ": " << (dist[i] == DBL_MAX ? -1 : dist[i]) << " min\n";

    /
    double minDist = DBL_MAX;
    int nearestHospital = -1;
    for (int h : hospitals) {
        if (dist[h] < minDist) {
            minDist = dist[h];
            nearestHospital = h;
        }
    }

    if (nearestHospital == -1)
        cout << "\nNo reachable hospital!\n";
    else {
        cout << "\nNearest hospital: Node " << nearestHospital << " (" << minDist << " min)\n";
        cout << "Optimal Path: ";
        city.printPath(nearestHospital, parent);
        cout << endl;
    }

    
    
    char choice;
    cout << "\nDo you want to simulate a traffic update? (y/n): ";
    cin >> choice;

    if (choice == 'y') {
        int u, v;
        double newW;
        cout << "Enter updated road (u v new_weight): ";
        cin >> u >> v >> newW;
        city.updateWeight(u, v, newW);
        cout << "\nTraffic updated. Recomputing shortest paths...\n";

        dist = city.dijkstra(src, parent);
        minDist = DBL_MAX;
        nearestHospital = -1;

        for (int h : hospitals) {
            if (dist[h] < minDist) {
                minDist = dist[h];
                nearestHospital = h;
            }
        }

        cout << "\nAfter update, nearest hospital: Node " << nearestHospital
             << " (" << minDist << " min)\n";
        cout << "New Optimal Path: ";
        city.printPath(nearestHospital, parent);
        cout << endl;
    }

    return 0;
}

