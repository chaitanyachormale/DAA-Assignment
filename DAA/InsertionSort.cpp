


#include <iostream>
using namespace std;


void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int current = arr[i];
        int j = i - 1;

       
        while (j >= 0 && arr[j] > current) {
            arr[j + 1] = arr[j];
            j--;
        }

        arr[j + 1] = current;
    }
}



void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}


int main() {
    
    
    int arr[] = {35, 10, 55, 20, 5};
    int n = sizeof(arr) / sizeof(arr[0]);

    cout << "Array size is = " << n << endl;

    cout << "Original array:" << endl;
    printArray(arr, n);

    insertionSort(arr, n);

    cout << "Sorted array:" << endl;
    printArray(arr, n);

    return 0;
}

