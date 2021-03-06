#include <iostream>
#include <vector>

using namespace std;

void vectorization_method_sparse_edition(const vector< vector<int> >& matrixA,
                                            const vector< vector<int> >& matrixB,
                                            vector< vector<int> >& matrixC,
                                            int thread_num)
{
    int M = matrixA.size();
    int N = matrixA[0].size();
    int K = matrixB[0].size();

    int i, j, k;
    #pragma omp parallel for private(j, k) num_threads(thread_num)
    for (i = 0; i < M; i++) {
        for (j = 0; j < N; ++j) {
            int result = 0;

            #pragma ivdep
            for (k = 0; k < K; ++k) {
                result = result + matrixA[i][k] * matrixB[k][j];
            }
            matrixC[i][j] = result;
        }
    }
}
