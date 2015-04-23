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
#include <iostream>     // for std::cin, std::cout, etc.
#include <vector>       // for vector
#include <sys/time.h>   // for gettimeofday
#include <cmath>        // for std::abs, std::ceil
#include <iomanip>      // for std::setprecision
#include <pthread.h>    // for pthreads
#include <stdlib.h>     // for std:atoi
#include <climits>      // for INT_MAX

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
        long processTime;
        long double area;
};

// Classes definitions
// -----------------------------------------------------
class Vertice {
    private:
        double x;
        double y;
    public:
        Vertice(double arg0, double arg1) :
                x(arg0), y(arg1) {
            // Nothing to do.
        }

        double getX() const {
            return x;
        }
        double getY() const {
            return y;
        }
};

class RlThreadRangeVertices {
    private:
        long pThreadId;
        long beginIndex;
        long endIndex;
        Result result;
    public:
        RlThreadRangeVertices(long arg0, long arg1, long arg2, Result arg3) :
                pThreadId(arg0), beginIndex(arg1), endIndex(arg2), result(arg3) {
            // Nothing to do.
        }

        long getThreadId() const {
            return pThreadId;
        }
        long getBeginIndex() const {
            return beginIndex;
        }
        long getEndIndex() const {
            return endIndex;
        }
        const Result& getResult() const {
            return result;
        }
        void setArea(const long double area) {
            this->result.area = area;
        }
};

// Functions declarations
// -----------------------------------------------------
bool readInputParams(int, char**, OutputType&, int&);
void printUsage();
OutputType stringToOutputType(std::string);
void readVertices(long, std::vector<Vertice>&);
void buildRelations(long, int, std::vector<RlThreadRangeVertices>&);
Result startParallelProcess(const std::vector<RlThreadRangeVertices>&);
void *shoelaceTheorem(void*);
void printResult(OutputType, Result);

// Globals declarations
// -----------------------------------------------------
std::vector<Vertice> vecVertices;

// main Function
// -----------------------------------------------------
int main(int argc, char **argv) {
    int numThreads = 0;
    OutputType outputType = NONE;
    if (!readInputParams(argc, argv, outputType, numThreads)) {
        return EXIT_SUCCESS;
    }
    long numVertices = 0;
    std::cin >> numVertices;
    readVertices(numVertices, vecVertices);
    std::vector<RlThreadRangeVertices> vecRelations;
    buildRelations(numVertices, numThreads, vecRelations);
    Result result = startParallelProcess(vecRelations);
    printResult(outputType, result);
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
        numThreads = atoi(argv[2]);
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

void readVertices(const long numVertices, std::vector<Vertice> &vecVertices) {
    double x = 0.0;
    double y = 0.0;
    for (long i = 0; i < numVertices; i++) {
        std::cin >> x;
        std::cin >> y;
        vecVertices.push_back(Vertice(x, y));
    }
}

void buildRelations(long numVertices, int numThreads, std::vector<RlThreadRangeVertices>& vecRelations) {
    long chunkSize = std::ceil((double) (numVertices) / numThreads);
    long beginIndex = 0;
    long endIndex = chunkSize - 1;
    for (long i = 0; i < numThreads; i++) {
        Result result;
        vecRelations.push_back(RlThreadRangeVertices(i, beginIndex, endIndex, result));
        if (endIndex + 1 == numVertices) {
            break;
        }
        beginIndex = endIndex + 1;
        endIndex = beginIndex + chunkSize - 1;
        if (numVertices <= endIndex) {
            endIndex = numVertices - 1;
        }
    }
}

Result startParallelProcess(const std::vector<RlThreadRangeVertices>& vecRelations) {
    Result result;
    timeval startTime;
    timeval endTime;
    gettimeofday(&startTime, NULL);
    pthread_t* arrayThreads = new pthread_t[vecRelations.size()];
    for (unsigned int i = 0; i < vecRelations.size(); i++) {
        pthread_create(&arrayThreads[i], NULL, shoelaceTheorem, (void *) &vecRelations[i]);
    }
    long double sum = 0.0;
    for (unsigned int i = 0; i < vecRelations.size(); i++) {
        pthread_join(arrayThreads[i], NULL);
        sum += vecRelations[i].getResult().area;
    }
    result.area = std::abs((sum) / 2.0);
    gettimeofday(&endTime, NULL);
    long time = ((endTime.tv_sec * 1000000 + endTime.tv_usec) - (startTime.tv_sec * 1000000 + startTime.tv_usec));
    result.processTime = time;
    return result;
}

void *shoelaceTheorem(void *arg0) {
    // Cast the received parameter.
    RlThreadRangeVertices *pThreadArgs = (RlThreadRangeVertices *) arg0;
    long double sum1 = 0.0;
    long double sum2 = 0.0;
    for (long i = pThreadArgs->getBeginIndex(); i <= pThreadArgs->getEndIndex(); i++) {
        sum1 += vecVertices[i].getX() * vecVertices[i + 1].getY();
        sum2 += vecVertices[i + 1].getX() * vecVertices[i].getY();
    }
    pThreadArgs->setArea(sum1 - sum2);
    pthread_exit(arg0);
}

void printResult(OutputType outputType, Result result) {
    std::cout << std::endl;
    switch (outputType) {
        case TIME:
            std::cout << result.processTime << "\n";
            break;
        case AREA:
            std::cout << std::fixed;
            std::cout << std::setprecision(2) << result.area << "\n";
            break;
        case ALL:
            std::cout << std::fixed;
            std::cout << std::setprecision(2) << result.area << "\n";
            std::cout << result.processTime << "\n";
            break;
        default:
            break;
    }
}
