#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>

using namespace std;
using namespace std::chrono;

void Clasica(int N, const vector<vector<int>>& A, const vector<vector<int>>& B, vector<vector<int>>& C) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            C[i][j] = 0;
            for (int k = 0; k < N; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

void Porbloques(int N, int blockSize, const vector<vector<int>>& A, const vector<vector<int>>& B, vector<vector<int>>& C) {
    for (int i0 = 0; i0 < N; i0 += blockSize) {
        for (int j0 = 0; j0 < N; j0 += blockSize) {
            for (int k0 = 0; k0 < N; k0 += blockSize) {
                for (int i = i0; i < min(i0 + blockSize, N); i++) {
                    for (int j = j0; j < min(j0 + blockSize, N); j++) {
                        for (int k = k0; k < min(k0 + blockSize, N); k++) {
                            C[i][j] += A[i][k] * B[k][j];
                        }
                    }
                }
            }
        }
    }
}

int main() {
    int N = 256; 
    int blockSize = 64; 

    vector<vector<int>> A(N, vector<int>(N, 1));
    vector<vector<int>> B(N, vector<int>(N, 2));
    vector<vector<int>> C(N, vector<int>(N, 0));
    vector<vector<int>> C_blocked(N, vector<int>(N, 0));


    auto start = high_resolution_clock::now();
    Clasica(N, A, B, C);
    auto stop = high_resolution_clock::now();
    auto durationClassic = duration_cast<milliseconds>(stop - start);
    cout << "Tiempo de ejecucion (Clasica): " << durationClassic.count() << " ms" << endl;

    start = high_resolution_clock::now();
    Porbloques(N, blockSize, A, B, C_blocked);
    stop = high_resolution_clock::now();
    auto durationBlocked = duration_cast<milliseconds>(stop - start);
    cout << "Tiempo de ejecucion (Por bloques): " << durationBlocked.count() << " ms" << endl;

    return 0;
}
