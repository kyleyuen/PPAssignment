#include <iostream>
#include <vector>

using namespace std;

const int THREAD_NUM = 8;

vector< vector<int> > change_calculate_order_method(const vector< vector<int> >& matrixA,
                                    const vector< vector<int> >& matrixB)
{
    int M = matrixA.size();
    int N = matrixA[0].size();
    int K = matrixB[0].size();

    vector< vector<int> > matrixC(M, vector<int>(K));
    int i, j, k;
    double temp;
    #pragma omp parallel for private(j, k) num_threads(THREAD_NUM)
	for (i = 0; i < M; i++) {
	    for (k = 0; k < K; ++k) {
			temp = matrixA[i][k];

			#pragma ivdep
			for (j = 0; j < N; ++j) {
				matrixC[i][j] += temp * matrixB[k][j];
			}
		}
	}
	return matrixC;
}

