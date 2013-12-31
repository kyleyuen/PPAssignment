#include <iostream>
#include <vector>

using namespace std;

void basic_method(const vector< vector<int> >& matrixA,
                   const vector< vector<int> >& matrixB,
                   vector< vector<int> >& matrixC)
{
    int M = matrixA.size();
    int N = matrixA[0].size();
    int K = matrixB[0].size();

    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; ++j) {
            int result = 0;
            for (int k = 0; k < K; ++k) {
                result = result + matrixA[i][k] * matrixB[k][j];
            }
            matrixC[i][j] = result;
        }
    }
}
