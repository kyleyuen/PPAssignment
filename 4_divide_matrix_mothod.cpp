#include <vector>

using namespace std;

const int THREAD_NUM = 8;

vector< vector<int> > divide_matrix_method(const vector< vector<int> >& matrixA,
                                    		const vector< vector<int> >& matrixB)
{
	int M = matrixA.size();
    int N = matrixA[0].size();
    int K = matrixB[0].size();

    int mc = M / 4;
    int kc = K / 4;
    int nc = N / 4;
    int i, j, k;
	int i_end, j_end, k_end;

    vector< vector<int> > matrixC(M, vector<int>(K));

    i_end = mc;
    for (int ii = 0; ii < M; ii += mc) {
    	if (mc > M - ii) {
    		i_end = M - ii;
    	}

    	k_end = kc;
    	for (int kk = 0; kk < K; kk += kc) {
    		if (kc > K - kk) {
    			k_end = K - kk;
    		}

    		j_end = nc;
    		for (int jj = 0; jj < N; jj += nc) {
    			if (nc > N - jj) {
    				j_end = N - jj;
    			}

    			#pragma omp parallel for private(i, j, k) num_threads(THREAD_NUM)
    			for (i = ii; i < ii + i_end; ++i) {
    				for (j = jj; j < jj + j_end; ++j) {
    					int result = 0;

    					#pragma ivdep
    					for (k = kk; k < kk + k_end; ++k) {
    						result += matrixA[i][k] * matrixB[k][j];
    					}
    					matrixC[i][j] += result;
    				}
    			}
    		}
    	}
    }
}