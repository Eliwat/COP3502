int binarySearch(int numbers[], int low, int high, int value) {
    if (low > high) {
        return -1; // Base case: value not found
    }

    int mid = low + (high - low) / 2;

    if (numbers[mid] == value) {
        return mid; // Value found at index mid
    } else if (numbers[mid] < value) {
        return binarySearch(numbers, mid + 1, high, value); // Search in the right half
    } else {
        return binarySearch(numbers, low, mid - 1, value); // Search in the left half
    }
}

int search(int numbers[], int low, int high, int value) {
    if (low > high || value < numbers[low] || value > numbers[high]) {
        return -1; // Base case: value not found or out of range
    }

    if (low == high) {
        if (numbers[low] == value) {
            return low; // Base case: value found at index low
        } else {
            return -1; // Base case: value not found at index low
        }
    }

    return binarySearch(numbers, low, high, value);
}
