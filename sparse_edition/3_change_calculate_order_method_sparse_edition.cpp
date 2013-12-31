#include <iostream>
#include <vector>

using namespace std;

void change_calculate_order_method_sparse_edition(const vector< vector<int> >& matrixA,
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
        for (k = 0; k < K; ++k) {
            if (matrixA[i][k] == 0) {
                continue;
            }
            int result = matrixA[i][k];

            #pragma ivdep
            for (j = 0; j < N; ++j) {
                matrixC[i][j] += result * matrixB[k][j];
            }
        }
    }
}

