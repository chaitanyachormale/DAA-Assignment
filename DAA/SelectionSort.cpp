#include <iostream>
#include <vector>
using namespace std;

void SelectionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[minIndex] > arr[j]) {
                minIndex = j;
            }
        }
        // Swap arr[i] and arr[minIndex]
        int temp = arr[i];
        arr[i] = arr[minIndex];
        arr[minIndex] = temp;
    }
}

void printArray(const vector<int>& arr) {
    for (int num : arr) {
        cout << num << "\n";
    }
}

int main() {
    // Changed input array for demonstration
    vector<int> arr = {29, 10, 14, 37, 13};

    cout << "Array size is = " << arr.size() << "\n";
    cout << "Original array:\n";
    printArray(arr);

    SelectionSort(arr);

    cout << "Sorted array:\n";
    printArray(arr);

    return 0;
}
