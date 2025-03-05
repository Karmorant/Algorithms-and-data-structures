#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <algorithm>

int getMax(int* arr, size_t size) {
    int max = arr[0];
    for (size_t i = 1; i < size; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}

void countSort(int* arr, size_t size, int exp) {
    int* output = (int*)malloc(size * sizeof(int));
    int count[10] = {0};
    for (size_t i = 0; i < size; i++) {
        count[(arr[i] / exp) % 10]++;
    }
    for (int i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }
    for (int i = size - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }
    for (size_t i = 0; i < size; i++) {
        arr[i] = output[i];
    }
    free(output);
}

void radixSort(int* arr, size_t size) {
    int max = getMax(arr, size);
    for (int exp = 1; max / exp > 0; exp *= 10) {
        countSort(arr, size, exp);
    }
}

void generateRandomArray(int* arr, size_t size) {
    for (size_t i = 0; i < size; i++) {
        arr[i] = rand() % 1000000;
    }
}

void generatePartiallySortedArray(int* arr, size_t size, float sortedPercentage) {
    for (size_t i = 0; i < size; i++) {
        arr[i] = i;
    }
    size_t shuffleCount = size * (1 - sortedPercentage);
    for (size_t i = 0; i < shuffleCount; i++) {
        size_t j = rand() % size;
        size_t k = rand() % size;
        int temp = arr[j];
        arr[j] = arr[k];
        arr[k] = temp;
    }
}

double measureTime(void (*sortFunction)(int*, size_t), int* arr, size_t size) {
    clock_t start = clock();
    sortFunction(arr, size);
    clock_t end = clock();
    return (double)(end - start) / CLOCKS_PER_SEC;
}

int main() {
    srand(time(NULL));
    FILE* file = fopen("sorting_times.txt", "w");
    if (!file) {
        perror("Failed to open file");
        return 1;
    }
    size_t sizes[] = {10, 100, 1000, 10000, 100000};
    for (size_t n : sizes) {
        int* arr = (int*)malloc(n * sizeof(int));
        generateRandomArray(arr, n);

        double radixTime = measureTime(radixSort, arr, n);
        double stdSortTime = measureTime([](int* arr, size_t size) { std::sort(arr, arr + size); }, arr, n);

        fprintf(file, "%zu %f %f\n", n, radixTime, stdSortTime);
        free(arr);
    }
    fprintf(file, "\n");

    float sortedPercentages[] = {0.2, 0.4, 0.6, 0.8, 1.0};
    size_t n = 100000;
    for (float sortedPercentage : sortedPercentages) {
        int* arr = (int*)malloc(n * sizeof(int));
        generatePartiallySortedArray(arr, n, sortedPercentage);

        double radixTime = measureTime(radixSort, arr, n);
        double stdSortTime = measureTime([](int* arr, size_t size) { std::sort(arr, arr + size); }, arr, n);

        fprintf(file, "%.1f %f %f\n", sortedPercentage, radixTime, stdSortTime);
        free(arr);
    }
    fprintf(file, "\n");

    int numDigits[] = {3, 5, 7, 9};
    for (int digits : numDigits) {
        int* arr = (int*)malloc(n * sizeof(int));
        for (size_t i = 0; i < n; i++) {
            arr[i] = rand() % (int)pow(10, digits);
        }

        double radixTime = measureTime(radixSort, arr, n);
        double stdSortTime = measureTime([](int* arr, size_t size) { std::sort(arr, arr + size); }, arr, n);

        fprintf(file, "%d %f %f\n", digits, radixTime, stdSortTime);
        free(arr);
    }

    fclose(file);
    return 0;
}