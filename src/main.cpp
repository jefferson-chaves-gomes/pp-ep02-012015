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
#include <time.h> //
#include <cmath> // for std::abs use
#include <iomanip> // for std::setprecision use

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
        long double area;
};

// Functions declarations
// -----------------------------------------------------
bool readInputParams(int, char**, OutputType&, int&);
void printUsage();
OutputType stringToOutputType(std::string);
void readVertices(long, float[][2]);
Result shoelaceTheorem(long, const float[][2], long);
void printResult(OutputType, Result);

// main Function
// -----------------------------------------------------
int main(int argc, char **argv) {
    int numThreads = 0;
    OutputType outputType = NONE;
    if (readInputParams(argc, argv, outputType, numThreads)) {
        long numVertices = 0;
        std::cin >> numVertices;
        float arrayVertices[numVertices][2];
        readVertices(numVertices, arrayVertices);
        Result result = shoelaceTheorem(numVertices, arrayVertices, numThreads);
        printResult(outputType, result);
    }
    return EXIT_SUCCESS;
}

// Function implementations
// -----------------------------------------------------
bool readInputParams(int argc, char **argv, OutputType &outputType, int &numThreads) {
    if (argc != 3) {
        printUsage();
        return false;
    } else {
        std::string input(argv[1]);
        numThreads = std::atoi(argv[2]);
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

void readVertices(const long numVertices, float arrayVertices[][2]) {
    for (long i = 0; i < numVertices; i++) {
        tratar apenas
        os vértices
        std::cin >> arrayVertices[i][0];
        std::cin >> arrayVertices[i][1];
    }
}

Result shoelaceTheorem(long numVertices, const float arrayVertices[][2], long numThreads) {
    Result result;
    long double sum1 = 0;
    long double sum2 = 0;
    double x = 0;
    double y = 0;
    for (long i = 0; i < numVertices - 1; i++) {
        x = arrayVertices[i][0];
        y = arrayVertices[i + 1][1];
        sum1 += x * y;
//    sum1 += arrayVertices[4][0] * arrayVertices[1][1];
        x = arrayVertices[i + 1][0];
        y = arrayVertices[i][1];
//    sum2 -= arrayVertices[1][0] * arrayVertices[4][1];
        sum2 += x * y;
    }
    result.area = std::abs((sum1 - sum2) / 2.0);
    return result;
}

void printResult(OutputType outputType, Result result) {
    std::cout << std::endl;
    switch (outputType) {
        case TIME:
            std::cout << result.processTime.count() << "time \n";
            break;
        case AREA:
            std::cout << std::fixed;
            std::cout << std::setprecision(2) << result.area << "area \n";
            break;
        case ALL:
            std::cout << std::fixed;
            std::cout << std::setprecision(2) << result.area << "area \n";
            std::cout << result.processTime.count() << "time \n";
            break;
        default:
            break;
    }
}
