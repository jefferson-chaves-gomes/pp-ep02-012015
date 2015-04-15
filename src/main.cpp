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
//struct Result {
//        std::chrono::duration<double> processTime;
//        std::set<int> lstPrimes;
//};

// Functions declarations
// -----------------------------------------------------
bool readInputParams(int, char*, OutputType*, int*);
void printUsage();
OutputType stringToOutputType(std::string);
//Result findPrimesSequential(int);
//Result findPrimesParallel(int, int);
//bool isPrime(int);
//void printResult(OutputType, Result);
//void printTimeOutputType(Result);
//void printListOutputType(Result);

// main Function
// -----------------------------------------------------
int main(int argc, char *argv[]) {
    int *numVertices = 0;
    int *numThreads = 0;
    OutputType *outputType(nullptr);
    if (readInputParams(argc, *argv, outputType, numThreads)) {
        std::cout << "Entrada correta:\numVertices d" << numVertices;
    }
    std::cout << "Finalizando:\n";
    return EXIT_SUCCESS;
}

// Function implementations
// -----------------------------------------------------
bool readInputParams(int argc, char *argv[], OutputType *outputType, int *numThreads) {
    if (argc != 2) {
        printUsage();
        return false;
    } else {
        std::string input(argv[1]);
        int numThread = std::atoi(argv[2]);
        numThreads = &numThread;
        OutputType outputTypel = stringToOutputType(input);
        if (outputTypel == NONE) {
            printUsage();
            return false;
        }
        outputType = &outputTypel;
    }
    return true;
}

void printUsage() {
    std::cout << "Usage:\n";
    std::cout << "\t./pp-ep02-012015 [time | area | all] [num_threads]\n";
    std::cout << "\t./pp-ep02-012015 all 4\n";
}

OutputType stringToOutputType(std::string input) {
    OutputType outputType = NONE;
    if (input == "time") {
        outputType = TIME;
    } else if (input == "area") {
        outputType = AREA;
    } else if (input == "all") {
        outputType = ALL;
    }
    return outputType;
}
