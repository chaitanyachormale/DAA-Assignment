#include <stdio.h>

// Function to perform Bubble Sort
void bubbleSort(int arr[], int n) {
    int temp;
    for (int i = 0; i < n - 1; i++) { // Reduced one iteration as last element becomes sorted
        for (int j = 0; j < (n - i - 1); j++) { // Optimized loop to avoid already sorted elements
            if (arr[j] > arr[j + 1]) {
                // Swap
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// Function to print the array
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]); // print all in same line
    }
    printf("\n");
}

int main() {
    // Updated input
    int arr[] = {50, 10, 40, 30, 20};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Array size is = %d\n", n);

    printf("Original array:\n");
    printArray(arr, n);

    // Sorting
    bubbleSort(arr, n);

    printf("Sorted array:\n");
    printArray(arr, n);

    return 0;
}
