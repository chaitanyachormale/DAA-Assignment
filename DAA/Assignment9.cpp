// Name:Chaitanya Ashok Chormale
//PRN:123B1F014
#include <bits/stdc++.h>
using namespace std;

const int INF = INT_MAX;


struct Node {
    vector<int> path;    
    int cost;            
    int bound;           
    int level;          
};


int calculateBound(vector<vector<int>>& costMatrix, vector<int>& path, int N) {
    int bound = 0;
    vector<bool> visited(N, false);

 
    for (int city : path) visited[city] = true;

  
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


struct cmp {
    bool operator()(Node a, Node b) {
        return a.bound > b.bound;
    }
};



pair<int, vector<int>> branchAndBoundTSP(vector<vector<int>>& costMatrix, int N) {
    priority_queue<Node, vector<Node>, cmp> pq;

    Node root;
    root.path.push_back(0); 
    root.cost = 0;
    root.level = 0;
    root.bound = calculateBound(costMatrix, root.path, N);

    pq.push(root);

    int minCost = INF;
    vector<int> bestPath;

    while (!pq.empty()) {
        Node curr = pq.top();
        pq.pop();

        if (curr.bound >= minCost) continue; 

        if (curr.level == N - 1) {
           
            int last = curr.path.back();
            if (costMatrix[last][0] != INF) {
                int totalCost = curr.cost + costMatrix[last][0];
                if (totalCost < minCost) {
                    minCost = totalCost;
                    bestPath = curr.path;
                    bestPath.push_back(0); /
                }
            }
            continue;
        }

        
        for (int i = 0; i < N; i++) {
            if (find(curr.path.begin(), curr.path.end(), i) == curr.path.end() && costMatrix[curr.path.back()][i] != INF) {
                Node child;
                child.path = curr.path;
                child.path.push_back(i);
                child.level = curr.level + 1;
                child.cost = curr.cost + costMatrix[curr.path.back()][i];
                child.bound = child.cost + calculateBound(costMatrix, child.path, N);

                if (child.bound < minCost)
                    pq.push(child); 
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

