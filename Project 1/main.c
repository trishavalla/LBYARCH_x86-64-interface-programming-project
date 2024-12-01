/*****************************
* x86-to-C interface programming project
* Members:
* SALIC, SHAIMMA 
* VALLADOLID, TRISHA LAINE 
******************************/

#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// External assembly function declaration
extern void imgCvtGrayDoubleToInt(double** src, int** dest, int h, int w);

void grayscaleConversion(double** src, int** dest, int h, int w) {
    for (int r = 0; r < h; r++) {
        for (int c = 0; c < w; c++) {
            dest[r][c] = (int)(src[r][c] * 255.0 + 0.5);
        }
    }
}

void allocateMemory(double*** source, int*** cResult, int*** asmResult, int h, int w) {
    *source = malloc(h * sizeof(double*));
    *cResult = malloc(h * sizeof(int*));
    *asmResult = malloc(h * sizeof(int*));
    for (int i = 0; i < h; i++) {
        (*source)[i] = malloc(w * sizeof(double));
        (*cResult)[i] = malloc(w * sizeof(int));
        (*asmResult)[i] = malloc(w * sizeof(int));
    }
}

void freeMemory(double** source, int** cResult, int** asmResult, int h) {
    for (int i = 0; i < h; i++) {
        free(source[i]);
        free(cResult[i]);
        free(asmResult[i]);
    }
    free(source);
    free(cResult);
    free(asmResult);
}

void readInput(double** source, int h, int w) {
    double input;
    int valid;
    do {
        valid = 1; // Assume inputs are valid initially
        for (int r = 0; r < h; r++) {
            for (int c = 0; c < w; c++) {
                scanf("%lf", &input);
                if (input < 0.0 || input > 1.0) {
                    printf("Invalid input. Please enter a value between 0.0 and 1.0.\n");
                    valid = 0; // Mark as invalid to re-enter all values
                }
                source[r][c] = input;
            }
        }
    } while (!valid); // Repeat if any input was invalid
}


void printResults(int** result, int h, int w, const char* label) {
    printf("\n%s:\n", label);
    for (int r = 0; r < h; r++) {
        for (int c = 0; c < w; c++) {
            printf("%d ", result[r][c]);
        }
        printf("\n");
    }
}

#include <time.h> // For clock()

int main() {
    srand((unsigned int)time(NULL));
    int h, w;

    // Input dimensions
    printf("Enter heigh, width, and double float pixel values: \n");
    scanf("%d %d", &h, &w);

    // Allocate memory
    double** source;
    int** cResult;
    int** asmResult;
    allocateMemory(&source, &cResult, &asmResult, h, w);

    // Read input values
    readInput(source, h, w);

    // Perform conversions
    grayscaleConversion(source, cResult, h, w);
    imgCvtGrayDoubleToInt(source, asmResult, h, w);

    // Print results
    printResults(asmResult, h, w, "Grayscale image representation in integer");
    printResults(cResult, h, w, "Expected results");


    // Measure execution time for asm_imgCvtGrayDoubleToInt
    printf("\nAverage execution time (30 tests):\n");

    int sizes[] = { 10, 100, 1000 }; // Define the sizes (width = height)
    for (int s = 0; s < 3; s++) {
        int size = sizes[s];
        int reps = 30; // Number of repetitions
        double total_time = 0.0;

        // Allocate temporary arrays for testing
        double** testSource = malloc(size * sizeof(double*));
        int** testResult = malloc(size * sizeof(int*));
        for (int i = 0; i < size; i++) {
            testSource[i] = malloc(size * sizeof(double));
            testResult[i] = malloc(size * sizeof(int));
        }

        // Generate random values for the input
        for (int r = 0; r < size; r++) {
            for (int c = 0; c < size; c++) {
                testSource[r][c] = ((double)rand() / RAND_MAX);
            }
        }

        // Time the ASM function
        for (int rep = 0; rep < reps; rep++) {
            clock_t start = clock();
            imgCvtGrayDoubleToInt(testSource, testResult, size, size);
            clock_t end = clock();
            total_time += (double)(end - start) / CLOCKS_PER_SEC;
        }

        // Print average execution time
        printf("Size %dx%d: Average time = %.6f seconds\n", size, size, total_time / reps);

        // Free temporary arrays
        for (int i = 0; i < size; i++) {
            free(testSource[i]);
            free(testResult[i]);
        }
        free(testSource);
        free(testResult);
    }

    // Free memory
    freeMemory(source, cResult, asmResult, h);

    return 0;
}
