#include <iostream>
#include <vector>
using namespace std;

// Merge two sorted halves of the array
void merge(vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Temporary arrays
    vector<int> leftTemp(n1);
    vector<int> rightTemp(n2);

    // Copy data to temp arrays
    for (int i = 0; i < n1; i++)
        leftTemp[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        rightTemp[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;

    // Merge the temp arrays back into arr[left..right]
    while (i < n1 && j < n2) {
        if (leftTemp[i] <= rightTemp[j]) {
            arr[k] = leftTemp[i];
            i++;
        } else {
            arr[k] = rightTemp[j];
            j++;
        }
        k++;
    }

    // Copy remaining elements of leftTemp[], if any
    while (i < n1) {
        arr[k] = leftTemp[i];
        i++;
        k++;
    }

    // Copy remaining elements of rightTemp[], if any
    while (j < n2) {
        arr[k] = rightTemp[j];
        j++;
        k++;
    }
}

// Recursive merge sort function
void mergeSort(vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        // Sort first and second halves
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        // Merge the sorted halves
        merge(arr, left, mid, right);
    }
}

int main() {
    vector<int> arr = {21, 45, 12, 34, 67, 43, 89};

    cout << "Original array:\n";
    for (int num : arr) cout << num << " ";
    cout << "\n";

    mergeSort(arr, 0, arr.size() - 1);

    cout << "Sorted array:\n";
    for (int num : arr) cout << num << " ";
    cout << "\n";

    return 0;
}
