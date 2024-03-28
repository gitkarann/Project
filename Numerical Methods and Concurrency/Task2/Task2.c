#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Structure to hold thread-specific information
typedef struct {
    long long start; // Start index of the iteration range for this thread
    long long end; // End index of the iteration range for this thread
    double result; // Partial sum of the Leibniz series calculated by this thread
} ThreadData;

// Global variable to hold the final result of Pi
double pi = 0.0;

// Mutex to protect the shared 'pi' variable
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

// Function to calculate Pi using the Leibniz formula for a given range
void* calculatePi(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    long long i;

    for (i = data->start; i < data->end; ++i) {
        data->result += (i % 2 == 0 ? 1.0 : -1.0) / (2 * i + 1);
    }

    // Lock the mutex before updating the shared 'pi' variable
    pthread_mutex_lock(&mutex);
    pi += data->result;
    // Unlock the mutex after updating the shared 'pi' variable
    pthread_mutex_unlock(&mutex);

    pthread_exit(NULL);
}

int main() {
    long long iterations, num_threads, i;

    // Get user inputs
    printf("Enter the number of iterations: ");
    scanf("%lld", &iterations);

    printf("Enter the number of threads: ");
    scanf("%lld", &num_threads);

    // Create thread data array
    ThreadData* thread_data = (ThreadData*)malloc(num_threads * sizeof(ThreadData));

    // Calculate workload per thread
    long long workload_per_thread = iterations / num_threads;

    // Create threads
    pthread_t* threads = (pthread_t*)malloc(num_threads * sizeof(pthread_t));

    for (i = 0; i < num_threads; ++i) {
        thread_data[i].start = i * workload_per_thread;
        thread_data[i].end = (i == num_threads - 1) ? iterations : (i + 1) * workload_per_thread;
        thread_data[i].result = 0.0;

        pthread_create(&threads[i], NULL, calculatePi, (void*)&thread_data[i]);
    }

    // Join threads
    for (i = 0; i < num_threads; ++i) {
        pthread_join(threads[i], NULL);
    }

    // Multiply by 4 to get the final value of Pi
    pi *= 4;

    // Print the result
    printf("Calculated Pi with %lld iterations using %lld threads: %.15f\n", iterations, num_threads, pi);

    // Clean up
    free(thread_data);
    free(threads);

    return 0;
}
