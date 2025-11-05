// Name:Chaitanya Ashok Chormale
//PRN:123B1F014

#include <stdio.h>


void bubbleSort(int arr[], int n) {
    int temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < (n - i - 1); j++) { 
            if (arr[j] > arr[j + 1]) {
               
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}


void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]); 
    }
    printf("\n");
}

int main() {
   
    int arr[] = {50, 10, 40, 30, 20};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Array size is = %d\n", n);

    printf("Original array:\n");
    printArray(arr, n);


    bubbleSort(arr, n);

    printf("Sorted array:\n");
    printArray(arr, n);

    return 0;
}

