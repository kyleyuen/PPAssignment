#include <iostream>
#include <vector>

using namespace std;

vector< vector<int> > basic_method(const vector< vector<int> >& matrixA,
                                   const vector< vector<int> >& matrixB)
{
    int M = matrixA.size();
    int N = matrixA[0].size();
    int K = matrixB[0].size();

    vector< vector<int> > matrixC(M, vector<int>(K));
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; ++j) {
			int result = 0;
			for (int k = 0; k < K; ++k) {
				result = result + matrixA[i][k] * matrixB[k][j];
			}
			matrixC[i][j] = result;
		}
	}
	return matrixC;
}
