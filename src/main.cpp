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
bool readInputParams(int, char**, OutputType&, long&);
void printUsage();
OutputType stringToOutputType(std::string);
void readVertices(long&, char**);

//Result findPrimesSequential(int);
//Result findPrimesParallel(int, int);
//bool isPrime(int);
//void printResult(OutputType, Result);
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

        char arrayVertices[][2] = { { 0, 0 }, { 0, 8 }, { 8, 8 }, { 8, 0 }, { 0, 0 } };
        readVertices(numVertices, arrayVertices);
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

void readVertices(long &numVertices, char **arrayVertices) {

}
