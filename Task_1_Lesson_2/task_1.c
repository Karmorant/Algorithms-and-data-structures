#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

void bubbleSort(int* arr, size_t size) {
    for (size_t i = 0; i < size - 1; i++) {
        for (size_t j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void improvedBubbleSort(int* arr, size_t size) {
    bool swapped;
    for (size_t i = 0; i < size - 1; i++) {
        swapped = false;
        for (size_t j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}

void Swap(int* a, int* b){
	*a ^= *b;
	*b ^= *a;
	*a ^= *b;
}

void shakerSort(int* data, size_t count){
	while (1){
	    char flag;
		int start[2] = { 1, count - 1 };
		int end[2] = { count, 0 };
		int inc[2] = { 1, -1 };

		for (int it = 0; it < 2; ++it){
			flag = 1;
			for (int i = start[it]; i != end[it]; i += inc[it]){
				if (data[i - 1] > data[i]){
					Swap(data + i - 1, data + i);
					flag = 0;
				}
			}

			if (flag)
                return;
		}
	}
}

void combSort(int* data, size_t count) {
	double gap = count;
	bool swaps = true;

	while (gap > 1 || swaps){
		gap /= 1.247330950103979;

		if (gap < 1)
			gap = 1;

		int i = 0;
		swaps = false;

		while (i + gap < count){
			int igap = i + (int)gap;
			if (data[i] > data[igap]){
				int temp = data[i];
				data[i] = data[igap];
				data[igap] = temp;
				swaps = true;
			}
			++i;
		}
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
    size_t numSizes = sizeof(sizes) / sizeof(sizes[0]);

    float sortedPercentages[] = {0.2, 0.4, 0.6, 0.8, 1.0};
    size_t numPercentages = sizeof(sortedPercentages) / sizeof(sortedPercentages[0]);

    for (size_t i = 0; i < numSizes; i++) {
        size_t n = sizes[i];
        int* arr = (int*)malloc(n * sizeof(int));

        generateRandomArray(arr, n);
        double bubbleTime = measureTime(bubbleSort, arr, n);
        generateRandomArray(arr, n);
        double improvedBubbleTime = measureTime(improvedBubbleSort, arr, n);
        generateRandomArray(arr, n);
        double shakerTime = measureTime(shakerSort, arr, n);
        generateRandomArray(arr, n);
        double combTime = measureTime(combSort, arr, n);

        fprintf(file, "%zu %f %f %f %f\n", n, bubbleTime, improvedBubbleTime, shakerTime, combTime);

        free(arr);
    }

    fprintf(file, "\n");

    size_t n = 100000;
    for (size_t i = 0; i < numPercentages; i++) {
        float sortedPercentage = sortedPercentages[i];
        int* arr = (int*)malloc(n * sizeof(int));

        generatePartiallySortedArray(arr, n, sortedPercentage);
        double bubbleTime = measureTime(bubbleSort, arr, n);
        generatePartiallySortedArray(arr, n, sortedPercentage);
        double improvedBubbleTime = measureTime(improvedBubbleSort, arr, n);
        generatePartiallySortedArray(arr, n, sortedPercentage);
        double shakerTime = measureTime(shakerSort, arr, n);
        generatePartiallySortedArray(arr, n, sortedPercentage);
        double combTime = measureTime(combSort, arr, n);

        fprintf(file, "%.1f %f %f %f %f\n", sortedPercentage, bubbleTime, improvedBubbleTime, shakerTime, combTime);

        free(arr);
    }

    fclose(file);
    return 0;
}