#include <stdio.h> // Required for printf
#include <stdlib.h> // Required for malloc and free
#include <pthread.h> // Required for multithreading
#include "lodepng.h" // Required for PNG decoding and encoding

#define CHANNELS 4 // Number of color channels (RGBA)
#define MATRIX_SIZE 3 // Size of the blur matrix

// Structure for thread-specific data
struct ThreadData { // Structure for passing data to threads
    unsigned char* image; // Pointer to the image data
    unsigned char* blurredImage; // Pointer to the blurred image data
    unsigned width; // Width of the image
    unsigned height; // Height of the image
    unsigned start_row; // Starting row for the thread
    unsigned end_row; // Ending row for the thread
};

// Function to decode PNG image
void decodePNG(const char* filename, unsigned char** image, unsigned* width, unsigned* height) { // Decodes a PNG file
    unsigned error = lodepng_decode32_file(image, width, height, filename); // Decodes the PNG file specified by filename
    if (error) { // If there's an error, print it
        fprintf(stderr, "Error %u: %s\n", error, lodepng_error_text(error)); // Print the error
        exit(EXIT_FAILURE); // Exit the program
    } 
}

// Function to apply Gaussian blur in a thread
void* applyGaussianBlurThread(void* arg) { // Applies Gaussian blur to an image in a thread
    struct ThreadData* data = (struct ThreadData*)arg; // Cast the argument to ThreadData struct

    for (unsigned y = data->start_row; y < data->end_row; ++y) { // Iterate over rows
        for (unsigned x = 0; x < data->width; ++x) { // Iterate over columns
            double totalR = 0.0, totalG = 0.0, totalB = 0.0; // Initialize total RGB values
            unsigned count = 0; // Initialize the count of pixels

            for (int i = -1; i <= 1; ++i) { // Iterate over the 3x3 blur matrix
                for (int j = -1; j <= 1; ++j) { // Iterate over the 3x3 blur matrix
                    int newX = x + i; // Calculate the new x coordinate
                    int newY = y + j; // Calculate the new y coordinate

                    if (newX >= 0 && newX < data->width && newY >= 0 && newY < data->height) { // Check if the coordinates are valid
                        totalR += data->image[(newY * data->width + newX) * CHANNELS]; // Add the RGB values to the total
                        totalG += data->image[(newY * data->width + newX) * CHANNELS + 1]; // Add the RGB values to the total
                        totalB += data->image[(newY * data->width + newX) * CHANNELS + 2]; // Add the RGB values to the total
                        count++; // Increment the count
                    }
                }
            }

            // Calculate the average RGB values and update the blurred image
            data->blurredImage[(y * data->width + x) * CHANNELS] = (unsigned char)(totalR / count); // Set the red value
            data->blurredImage[(y * data->width + x) * CHANNELS + 1] = (unsigned char)(totalG / count); // Set the green value
            data->blurredImage[(y * data->width + x) * CHANNELS + 2] = (unsigned char)(totalB / count); // Set the blue value
            data->blurredImage[(y * data->width + x) * CHANNELS + 3] = data->image[(y * data->width + x) * CHANNELS + 3]; // Set the alpha value
        }
    }

    pthread_exit(NULL); // Exit the thread
}

// Function to apply Gaussian blur to the entire image
void applyGaussianBlur(unsigned char* image, unsigned width, unsigned height) { // Applies Gaussian blur to an image
    unsigned char* blurredImage = malloc(width * height * CHANNELS); // Allocate memory for the blurred image

    // Initialize pthread variables
    pthread_t threads[4]; // Array of threads
    struct ThreadData threadData[4]; // Array of thread data

    // Divide the image rows among the threads
    unsigned chunk_size = height / 4; // Divide the rows into 4 chunks
    for (int i = 0; i < 4; ++i) { // Iterate over threads
        threadData[i].image = image; // Set the image
        threadData[i].blurredImage = blurredImage; // Set the blurred image
        threadData[i].width = width; // Set the width
        threadData[i].height = height; // Set the height
        threadData[i].start_row = i * chunk_size; // Set the starting row
        threadData[i].end_row = (i + 1) * chunk_size; // Set the ending row
        if (i == 3)  // Last thread handles the remaining rows 
            threadData[i].end_row = height; // Set the ending row for the last thread

        pthread_create(&threads[i], NULL, applyGaussianBlurThread, (void*)&threadData[i]); // Create the thread
    }

    // Wait for all threads to finish
    for (int i = 0; i < 4; ++i) { // Iterate over threads
        pthread_join(threads[i], NULL); // Join the thread
    }

    // Copy the blurred image back to the original image
    for (int i = 0; i < width * height * CHANNELS; ++i) { // Iterate over the image
        image[i] = blurredImage[i]; // Copy the blurred image to the original image
    } 

    free(blurredImage); // Free the memory allocated for the blurred image
}

// Function to encode a PNG image
void encodePNG(const char* filename, const unsigned char* image, unsigned width, unsigned height) { // Encodes a PNG file
    unsigned error = lodepng_encode32_file(filename, image, width, height); // Encodes the PNG file specified by filename
    if (error) { // If there's an error, print it
        fprintf(stderr, "Error %u: %s\n", error, lodepng_error_text(error)); // Print the error
        exit(EXIT_FAILURE); // Exit the program
    }
} 

int main() {
    const char* inputFilename = "in_img.png"; // Input filename
    const char* outputFilename = "out_img.png"; // Output filename
    unsigned char* image; // Pointer to the image data
    unsigned width, height; // Width and height of the image

    decodePNG(inputFilename, &image, &width, &height); // Decode the PNG image

    int blurIterations; // Number of blur iterations
    printf("Enter the number of blur iterations: "); // Prompt the user for the number of blur iterations
    scanf("%d", &blurIterations); // Read the number of blur iterations

    for (int i = 0; i < blurIterations; ++i) { // Iterate over blur iterations
        applyGaussianBlur(image, width, height); // Apply Gaussian blur to the image
    }
    
    encodePNG(outputFilename, image, width, height); // Encode the PNG image
    
    free(image); // Free the memory allocated for the image

    return 0; // Return 0 to indicate successful execution
}
