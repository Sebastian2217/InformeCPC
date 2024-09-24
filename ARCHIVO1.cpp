#include <iostream>
#include <chrono>

const int MAX = 1000;
double A[MAX][MAX], x[MAX], y[MAX];

void initialize() {
    for (int i = 0; i < MAX; ++i) {
        x[i] = i * 0.5;
        y[i] = 0.0;
        for (int j = 0; j < MAX; ++j) {
            A[i][j] = i + j * 0.1;
        }
    }
}

void firstPairOfLoops() {
    for (int i = 0; i < MAX; ++i) {
        for (int j = 0; j < MAX; ++j) {
            y[i] += A[i][j] * x[j];
        }
    }
}

void secondPairOfLoops() {
    for (int j = 0; j < MAX; ++j) {
        for (int i = 0; i < MAX; ++i) {
            y[j] += A[i][j] * x[i];
        }
    }
}

int main() {
    initialize();

    auto start1 = std::chrono::high_resolution_clock::now();
    firstPairOfLoops();
    auto end1 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed1 = end1 - start1;
    std::cout << "Tiempo del primer par de bucles: " << elapsed1.count() << " segundos.\n";

    for (int i = 0; i < MAX; ++i) {
        y[i] = 0.0;
    }

    auto start2 = std::chrono::high_resolution_clock::now();
    secondPairOfLoops();
    auto end2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed2 = end2 - start2;
    std::cout << "Tiempo del segundo par de bucles: " << elapsed2.count() << " segundos.\n";

    return 0;
}
