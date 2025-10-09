#include <iostream>
#include <vector>
using namespace std;

// Function to get the maximum of two numbers
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Function to solve 0/1 Knapsack problem
int knapsack(int W, vector<int>& wt, vector<int>& val, int n) {
    vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0));

    // Build table dp[][] in bottom-up manner
    for (int i = 0; i <= n; i++) {
        for (int w = 0; w <= W; w++) {
            if (i == 0 || w == 0)
                dp[i][w] = 0;
            else if (wt[i - 1] <= w)
                dp[i][w] = max(val[i - 1] + dp[i - 1][w - wt[i - 1]],
                               dp[i - 1][w]);
            else
                dp[i][w] = dp[i - 1][w];
        }
    }

    return dp[n][W]; // Maximum value possible
}

int main() {
    // Minor change in input
    vector<int> val = {70, 90, 120};   // item values
    vector<int> wt  = {10, 25, 35};    // item weights
    int W = 50;                        // Knapsack capacity
    int n = val.size();               // Number of items

    cout << "Maximum value in Knapsack = " << knapsack(W, wt, val, n) << endl;

    return 0;
}
