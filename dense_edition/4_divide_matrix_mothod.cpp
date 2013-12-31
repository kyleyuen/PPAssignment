#include <vector>

using namespace std;

void divide_matrix_method(const vector< vector<int> >& matrixA,
                            const vector< vector<int> >& matrixB,
                            vector< vector<int> >& matrixC,
                            int thread_num)
{
    int M = matrixA.size();
    int N = matrixA[0].size();
    int K = matrixB[0].size();

    int divide_size = thread_num / 4;
    int mc = M / divide_size;
    int kc = K / divide_size;
    int nc = N / divide_size;

    int i, j, k;
    int i_end, j_end, k_end;

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

                #pragma omp parallel for private(i, j, k) num_threads(thread_num)
                for (i = ii; i < ii + i_end; ++i) {
                    for (k = kk; k < kk + k_end; ++k) {
                        int result = matrixA[i][k];

                        #pragma ivdep
                        for (j = jj; j < jj + j_end; ++j) {         
                            matrixC[i][j] += result * matrixB[k][j];
                        }
                    }
                }
            }
        }
    }
}