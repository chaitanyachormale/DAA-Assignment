// Name:Chaitanya Ashok Chormale
//PRN:123B1F014
#include <bits/stdc++.h>
using namespace std;


struct Order {
    int orderID;
    long long timestamp; 
};


void merge(vector<Order> &orders, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<Order> leftArr(n1);
    vector<Order> rightArr(n2);

    for (int i = 0; i < n1; i++)
        leftArr[i] = orders[left + i];
    for (int j = 0; j < n2; j++)
        rightArr[j] = orders[mid + 1 + j];

    int i = 0, j = 0, k = left;

  
    while (i < n1 && j < n2) {
        if (leftArr[i].timestamp <= rightArr[j].timestamp)
            orders[k++] = leftArr[i++];
        else
            orders[k++] = rightArr[j++];
    }

   
    while (i < n1)
        orders[k++] = leftArr[i++];
    while (j < n2)
        orders[k++] = rightArr[j++];
}

void mergeSort(vector<Order> &orders, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(orders, left, mid);
        mergeSort(orders, mid + 1, right);
        merge(orders, left, mid, right);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cout << "Enter number of customer orders: ";
    cin >> n;

    vector<Order> orders(n);

    cout << "Enter orderID and timestamp for each order:\n";
    for (int i = 0; i < n; i++) {
        cin >> orders[i].orderID >> orders[i].timestamp;
    }

    auto start = chrono::high_resolution_clock::now();
    mergeSort(orders, 0, n - 1);
    auto end = chrono::high_resolution_clock::now();

    chrono::duration<double> duration = end - start;

    cout << "\nOrders sorted by timestamp:\n";
    for (auto &o : orders)
        cout << "OrderID: " << o.orderID << " | Timestamp: " << o.timestamp << "\n";

    cout << "\nTime taken for sorting: " << duration.count() << " seconds\n";
    return 0;
}


