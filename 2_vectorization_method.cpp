#include <iostream>
#include <vector>

using namespace std;

vector< vector<int> > vectorization_method(const vector< vector<int> >& matrixA,
                                    		const vector< vector<int> >& matrixB,
                                    		int thread_num)
{
    int M = matrixA.size();
    int N = matrixA[0].size();
    int K = matrixB[0].size();

    vector< vector<int> > matrixC(M, vector<int>(K));
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
	return matrixC;
}
