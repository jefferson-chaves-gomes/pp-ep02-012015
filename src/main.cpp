/*
 ============================================================================
 Name        : main.cpp
 Author      : Jefferson Chaves Gomes
 Version     : 1.0.0
 Copyright   : Academic Program
 Description : EP 02 in C++
 ============================================================================
 */

// Libraries definitions
// -----------------------------------------------------
#include <iostream>
#include <time.h>
#include <cmath>

// Enums definitions
// -----------------------------------------------------
enum OutputType {
    NONE = 0,
    TIME = 1,
    AREA = 2,
    ALL = 3
};

// Structs definitions
// -----------------------------------------------------
struct Result {
        std::chrono::duration<double> processTime;
        double area;
};

// Functions declarations
// -----------------------------------------------------
bool readInputParams(int, char**, OutputType&, long&);
void printUsage();
OutputType stringToOutputType(std::string);
void readVertices(long, double[][2]);
Result shoelaceTheorem(long, double[][2], long);
void printResult(OutputType, Result);

//Result findPrimesSequential(int);
//Result findPrimesParallel(int, int);
//bool isPrime(int);
//void printTimeOutputType(Result);
//void printListOutputType(Result);

// main Function
// -----------------------------------------------------
int main(int argc, char **argv) {
    long numVertices = 0;
    long numThreads = 0;
    OutputType outputType = NONE;
    if (readInputParams(argc, argv, outputType, numThreads)) {
        std::cin >> numVertices;
        double arrayVertices[numVertices][2];
        readVertices(numVertices, arrayVertices);
        shoelaceTheorem(numVertices, arrayVertices, numThreads);
    }
    std::cout << "\n\nFinalizando:\n";
    return EXIT_SUCCESS;
}

// Function implementations
// -----------------------------------------------------
bool readInputParams(int argc, char **argv, OutputType &outputType, long &numThreads) {
    if (argc != 3) {
        printUsage();
        return false;
    } else {
        std::string input(argv[1]);
        numThreads = std::atol(argv[2]);
        OutputType outputTypel = stringToOutputType(input);
        if (numThreads <= 0 || numThreads > INT_MAX || outputTypel == NONE) {
            printUsage();
            return false;
        }
        outputType = outputTypel;
    }
    return true;
}

void printUsage() {
    std::cout << "Usage:\n";
    std::cout << "\t./pp-ep02-012015 [output type] [number of threads]\n\n";
    std::cout << "\toutput type         -- Define the output type [time | area | all]\n";
    std::cout << "\tnumber of threads   -- Define the number of threads to use in processing  [a valid interger greater than 0 and less or equal than " << INT_MAX << "]\n";
    std::cout << "Sample:\n";
    std::cout << "\t./pp-ep02-012015 all 4\n";
}

OutputType stringToOutputType(std::string input) {
    if (input == "time") {
        return TIME;
    } else if (input == "area") {
        return AREA;
    } else if (input == "all") {
        return ALL;
    }
    return NONE;
}

void readVertices(long numVertices, double arrayVertices[][2]) {
    for (long i = 0; i < numVertices; ++i) {
        std::cin >> arrayVertices[i][0];
        std::cin >> arrayVertices[i][1];
    }
}

Result shoelaceTheorem(long numVertices, double arrayVertices[][2], long numThreads) {
    Result result;
    long double sum1 = 0;
    long double sum2 = 0;
    double x = 0;
    double y = 0;
    for (int i = 0; i < numVertices - 1; i++) {
        x = arrayVertices[i][0];
        y = arrayVertices[i + 1][1];
        sum1 += x * y;
    }
    sum1 += arrayVertices[4][0] * arrayVertices[1][1];
    for (int i = 0; i < numVertices - 1; i++) {
        x = arrayVertices[i + 1][0];
        y = arrayVertices[i][1];
        sum2 += x * y;
    }
    sum2 += arrayVertices[1][0] * arrayVertices[4][1];

    long double area = std::abs((sum1 - sum2) / 2.0);
    std::cout << " area: " << area << "\n";
    return result;
}

void printResult(OutputType, Result) {

}
