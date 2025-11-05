// Name:Chaitanya Ashok Chormale
//PRN:123B1F014
#include <bits/stdc++.h>
using namespace std;

struct Item {
    string name;
    int weight;
    int utility;
    bool isPerishable; 
};


int knapsackBruteForce(vector<Item> &items, int W, int n) {
    if (n == 0 || W == 0)
        return 0;
    if (items[n - 1].weight > W)
        return knapsackBruteForce(items, W, n - 1);
    return max(items[n - 1].utility + knapsackBruteForce(items, W - items[n - 1].weight, n - 1),
               knapsackBruteForce(items, W, n - 1));
}


int knapsackDP(vector<Item> &items, int W) {
    int n = items.size();
    vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0));

    for (int i = 1; i <= n; i++) {
        for (int w = 1; w <= W; w++) {
            if (items[i - 1].weight <= w)
                dp[i][w] = max(items[i - 1].utility + dp[i - 1][w - items[i - 1].weight], dp[i - 1][w]);
            else
                dp[i][w] = dp[i - 1][w];
        }
    }

    
    int res = dp[n][W];
    int w = W;
    cout << "\nOptimal Items Selected:\n";
    for (int i = n; i > 0 && res > 0; i--) {
        if (res != dp[i - 1][w]) {
            cout << "- " << items[i - 1].name << " (Weight: " << items[i - 1].weight
                 << ", Utility: " << items[i - 1].utility << ")\n";
            res -= items[i - 1].utility;
            w -= items[i - 1].weight;
        }
    }

    return dp[n][W];
}


double knapsackGreedy(vector<Item> items, int W) {
    sort(items.begin(), items.end(), [](Item &a, Item &b) {
        double r1 = (double)a.utility / a.weight;
        double r2 = (double)b.utility / b.weight;
        return r1 > r2;
    });

    double totalUtility = 0;
    int currentWeight = 0;

    cout << "\nGreedy Selection Order:\n";
    for (auto &it : items) {
        if (currentWeight + it.weight <= W) {
            currentWeight += it.weight;
            totalUtility += it.utility;
            cout << "- " << it.name << " (Weight: " << it.weight
                 << ", Utility: " << it.utility << ")\n";
        }
    }
    return totalUtility;
}


int knapsackWithPriority(vector<Item> &items, int W) {
    for (auto &it : items) {
        if (it.isPerishable)
            it.utility += 20;
    }
    return knapsackDP(items, W);
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, W;
    cout << "Enter number of items: ";
    cin >> n;
    cout << "Enter truck capacity (in kg): ";
    cin >> W;

    vector<Item> items(n);
    cout << "Enter item details:\n";
    for (int i = 0; i < n; i++) {
        cout << "Name Weight Utility IsPerishable(1/0): ";
        cin >> items[i].name >> items[i].weight >> items[i].utility >> items[i].isPerishable;
    }

    cout << "\n=== Disaster Relief Resource Allocation ===\n";

    auto start = chrono::high_resolution_clock::now();
    int maxUtility = knapsackDP(items, W);
    auto end = chrono::high_resolution_clock::now();

    cout << "\nMaximum Utility Value (DP): " << maxUtility;
    cout << "\nComputation Time: "
         << chrono::duration_cast<chrono::microseconds>(end - start).count() / 1000.0
         << " ms\n";

    cout << "\n[Comparison: Greedy Approach]";
    cout << "\nApproximate Utility (Greedy): " << knapsackGreedy(items, W);

    cout << "\n\n[Extended: Prioritizing Perishables]";
    int priorityUtility = knapsackWithPriority(items, W);
    cout << "\nMaximum Utility with Priority: " << priorityUtility << "\n";

    return 0;
}

