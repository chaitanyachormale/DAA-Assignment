#include <bits/stdc++.h>
using namespace std;

const int INF = INT_MAX;

// Structure to represent the TSP state
struct Node {
    vector<int> path;    // Cities visited in the path
    int cost;            // Cost of the path so far
    int bound;           // Lower bound of the total cost
    int level;           // Level in the search tree
};

// Function to calculate a simple lower bound (reduced cost)
int calculateBound(vector<vector<int>>& costMatrix, vector<int>& path, int N) {
    int bound = 0;
    vector<bool> visited(N, false);

    // Mark cities already visited
    for (int city : path) visited[city] = true;

    // Add minimum outgoing edge for unvisited cities
    for (int i = 0; i < N; i++) {
        if (!visited[i]) {
            int minEdge = INF;
            for (int j = 0; j < N; j++) {
                if (i != j && !visited[j])
                    minEdge = min(minEdge, costMatrix[i][j]);
            }
            bound += (minEdge == INF ? 0 : minEdge);
        }
    }
    return bound;
}

// Comparator for priority queue to get least cost first
struct cmp {
    bool operator()(Node a, Node b) {
        return a.bound > b.bound;
    }
};

// Branch and Bound TSP solver
pair<int, vector<int>> branchAndBoundTSP(vector<vector<int>>& costMatrix, int N) {
    priority_queue<Node, vector<Node>, cmp> pq;

    Node root;
    root.path.push_back(0); // start at city 0
    root.cost = 0;
    root.level = 0;
    root.bound = calculateBound(costMatrix, root.path, N);

    pq.push(root);

    int minCost = INF;
    vector<int> bestPath;

    while (!pq.empty()) {
        Node curr = pq.top();
        pq.pop();

        if (curr.bound >= minCost) continue; // prune

        if (curr.level == N - 1) {
            // Complete the tour
            int last = curr.path.back();
            if (costMatrix[last][0] != INF) { // can return to start
                int totalCost = curr.cost + costMatrix[last][0];
                if (totalCost < minCost) {
                    minCost = totalCost;
                    bestPath = curr.path;
                    bestPath.push_back(0); // return to start
                }
            }
            continue;
        }

        // Expand node
        for (int i = 0; i < N; i++) {
            if (find(curr.path.begin(), curr.path.end(), i) == curr.path.end() && costMatrix[curr.path.back()][i] != INF) {
                Node child;
                child.path = curr.path;
                child.path.push_back(i);
                child.level = curr.level + 1;
                child.cost = curr.cost + costMatrix[curr.path.back()][i];
                child.bound = child.cost + calculateBound(costMatrix, child.path, N);

                if (child.bound < minCost)
                    pq.push(child); // only push promising nodes
            }
        }
    }

    return {minCost, bestPath};
}

int main() {
    int N;
    cout << "Enter number of cities: ";
    cin >> N;

    vector<vector<int>> costMatrix(N, vector<int>(N));

    cout << "Enter cost matrix (distance/fuel/time combined cost):\n";
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            cin >> costMatrix[i][j];

    auto result = branchAndBoundTSP(costMatrix, N);

    cout << "Minimum cost: " << result.first << "\n";
    cout << "Optimal route: ";
    for (int city : result.second)
        cout << city << " ";
    cout << endl;

    return 0;
}
