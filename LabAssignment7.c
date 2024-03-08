#include <stdio.h>

// Function to perform bubble sort and count swaps
void bubbleSort(int arr[], int size, int swap_counts[]) {
    int tempArr[size];
    for(int k = 0; k < size; k++) {
        tempArr[k] = arr[k];
    }

    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (tempArr[j] > tempArr[j + 1]) {
                int temp = tempArr[j];
                tempArr[j] = tempArr[j + 1];
                tempArr[j + 1] = temp;
                swap_counts[j]++;
                swap_counts[j + 1]++;
            }
        }
    }
}

// Function to perform selection sort and count swaps
void selectionSort(int arr[], int size, int swap_counts[]) {
    int tempArr[size];
    for(int k = 0; k < size; k++) {
        tempArr[k] = arr[k];
    }

    for (int i = 0; i < size - 1; i++) {
        int min_index = i;
        for (int j = i + 1; j < size; j++) {
            if (tempArr[j] < tempArr[min_index]) {
                min_index = j;
            }
        }
        if (min_index != i) {
            int temp = tempArr[i];
            tempArr[i] = tempArr[min_index];
            tempArr[min_index] = temp;
            swap_counts[i]++;
            swap_counts[min_index]++;
        }
    }
}

int main() {
    int array1[9] = {97, 16, 45, 63, 13, 22, 7, 58, 72};
    int array2[9] = {90, 80, 70, 60, 50, 40, 30, 20, 10};
    const int size = sizeof(array1) / sizeof(array1[0]);

    // Arrays to store swap counts for each element in array1
    int swap_counts_bubble1[size] = {0};
    int swap_counts_selection1[size] = {0};

    // Perform bubble sort on array1
    bubbleSort(array1, size, swap_counts_bubble1);
    printf("Array 1 | Bubble Sort | Number of swaps for each number: \n");
    for (int i = 0; i < size; i++) {
        printf("%d: swapped %d times.\n", array1[i], swap_counts_bubble1[i]);
    }

    // Calculate total number of swaps for array1 bubble sort
    int total_swaps_bubble1 = 0;
    for (int i = 0; i < size; i++) {
        total_swaps_bubble1 += swap_counts_bubble1[i];
    }
    printf("Total number of swaps for Array 1 bubble sort: %d\n\n", total_swaps_bubble1 / 2);

    // Perform selection sort on array1
    selectionSort(array1, size, swap_counts_selection1);
    printf("Array 1 | Selection Sort | Number of swaps for each number: \n");
    for (int i = 0; i < size; i++) {
        printf("%d: swapped %d times.\n", array1[i], swap_counts_selection1[i]);
    }

    // Calculate total number of swaps for array1 selection sort
    int total_swaps_selection1 = 0;
    for (int i = 0; i < size; i++) {
        total_swaps_selection1 += swap_counts_selection1[i];
    }
    printf("\nTotal number of swaps for Array 1 selection sort: %d\n", total_swaps_selection1 / 2);

    printf("\n");

    // Arrays to store swap counts for each element in array2
    int swap_counts_bubble2[size] = {0};
    int swap_counts_selection2[size] = {0};

    // Perform bubble sort on array2
    bubbleSort(array2, size, swap_counts_bubble2);
    printf("Array 2 | Bubble Sort | Number of swaps for each number: \n");
    for (int i = 0; i < size; i++) {
        printf("%d: swapped %d times.\n", array2[i], swap_counts_bubble2[i]);
    }

    // Calculate total number of swaps for array2 bubble sort
    int total_swaps_bubble2 = 0;
    for (int i = 0; i < size; i++) {
        total_swaps_bubble2 += swap_counts_bubble2[i];
    }
    printf("Total number of swaps for Array 2 bubble sort: %d\n", total_swaps_bubble2 / 2);

    // Perform selection sort on array2
    selectionSort(array2, size, swap_counts_selection2);
    printf("\nArray 2 | Selection Sort | Number of swaps for each number: \n");
    for (int i = 0; i < size; i++) {
        printf("%d: swapped %d times.\n", array2[i], swap_counts_selection2[i]);
    }

    // Calculate total number of swaps for array2 selection sort
    int total_swaps_selection2 = 0;
    for (int i = 0; i < size; i++) {
        total_swaps_selection2 += swap_counts_selection2[i];
    }
    printf("Total number of swaps for Array 2 selection sort: %d\n", total_swaps_selection2 / 2);

    return 0;
}
