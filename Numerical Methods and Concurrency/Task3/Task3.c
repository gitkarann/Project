#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

#define MAX_THREADS 4

typedef struct {
    int* data;
    int size;
    int start;
    int end;
    int primeCount;
} ThreadData;

// Function to check if a number is prime
int is_prime(int num) {
    int i;
    if (num <= 1) return 0;  // 0 and 1 are not prime
    for (i = 2; i <= sqrt(num); i++) {
        if (num % i == 0) return 0;  // not prime if divisible
    }
    return 1;  // prime
}

// Function to process data for each thread
void* process_data(void* arg) {
    ThreadData* threadData = (ThreadData*)arg;
    threadData->primeCount = 0;
    int i;

    for (i = threadData->start; i < threadData->end; i++) {
        if (is_prime(threadData->data[i])) {
            threadData->primeCount++;
        }
    }

    pthread_exit(NULL);
}

int main() {
    FILE *file1, *file2, *file3;
    pthread_t threads[MAX_THREADS];
    ThreadData threadData[MAX_THREADS];
    int i,j;

    // Open files
    file1 = fopen("PrimeData1.txt", "r");
    file2 = fopen("PrimeData2.txt", "r");
    file3 = fopen("PrimeData3.txt", "r");

    // Load data from files
    // Assume each file has the same number of elements for simplicity
    int dataSize;
    fscanf(file1, "%d", &dataSize);

    int* allData = (int*)malloc(sizeof(int) * dataSize * 3);

    for (i = 0; i < dataSize; i++) {
        fscanf(file1, "%d", &allData[i]);
        fscanf(file2, "%d", &allData[dataSize + i]);
        fscanf(file3, "%d", &allData[2 * dataSize + i]);
    }

    // Close files
    fclose(file1);
    fclose(file2);
    fclose(file3);

    // Split data among threads
    int sliceSize = dataSize / MAX_THREADS;
    for (i = 0; i < MAX_THREADS; i++) {
        threadData[i].data = allData;
        threadData[i].size = dataSize;
        threadData[i].start = i * sliceSize;
        threadData[i].end = (i == MAX_THREADS - 1) ? dataSize : (i + 1) * sliceSize;
        pthread_create(&threads[i], NULL, process_data, (void*)&threadData[i]);
    }

    // Wait for all threads to finish
    for (i = 0; i < MAX_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Output results to file
    FILE* output = fopen("output.txt", "w");
    for (i = 0; i < MAX_THREADS; i++) {
        fprintf(output, "Thread %d found %d prime numbers:\n", i + 1, threadData[i].primeCount);
        for (j = threadData[i].start; j < threadData[i].end; j++) {
            if (is_prime(allData[j])) {
                fprintf(output, "%d\n", allData[j]);
            }
        }
        fprintf(output, "\n");
    }
    fclose(output);

    // Free allocated memory
    free(allData);

    return 0;
}
