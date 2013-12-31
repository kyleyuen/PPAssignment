#include <iostream>
#include <fstream>
#include <vector>
#include <omp.h>

using namespace std;

void generate_sparse_matrix(int size, const string& file_name);
void read_matrix(vector< vector<int> >& matrix, const string& filename);
void write_matrix(vector< vector<int> >& matrix, const string& file_name);
void clean_matrix(vector< vector<int> >& matrix);

void basic_method_sparse_edition(const vector< vector<int> >& matrixA,
                                   const vector< vector<int> >& matrixB,
                                   vector< vector<int> >& matrixC);

void vectorization_method_sparse_edition(const vector< vector<int> >& matrixA,
                                            const vector< vector<int> >& matrixB,
                                            vector< vector<int> >& matrixC,
                                            int thread_num);

void change_calculate_order_method_sparse_edition(const vector< vector<int> >& matrixA,
                                                    const vector< vector<int> >& matrixB,
                                                    vector< vector<int> >& matrixC,
                                                    int thread_num);

void divide_matrix_method_sparse_edition(const vector< vector<int> >& matrixA,
                                            const vector< vector<int> >& matrixB,
                                            vector< vector<int> >& matrixC,
                                            int thread_num);

int main()
{
    int target_size = 1000;
    int thread_num = 16;

    // generate and read matrix A
    generate_sparse_matrix(target_size, "matrix_a.txt");
    vector< vector<int> > matrixA(target_size, vector<int>(target_size));
    read_matrix(matrixA, "matrix_a.txt");

    // generate and read matrix B
    generate_sparse_matrix(target_size, "matrix_b.txt");
    vector< vector<int> > matrixB(target_size, vector<int>(target_size));
    read_matrix(matrixB, "matrix_b.txt");

    double start, end;
    double baseline, runtime;
    vector< vector<int> > matrixC(target_size, vector<int>(target_size, 0));

    cout.setf(ios::fixed);
    cout.precision(2);
    // run basic matrix multiply method
    start = omp_get_wtime();
    basic_method_sparse_edition(matrixA, matrixB, matrixC);
    end = omp_get_wtime();
    cout << "step 1, basic method's runtime: ";
    baseline = end - start;
    cout << baseline << "s" << endl;
    cout << endl;
    write_matrix(matrixC, "step1_result.txt");
    clean_matrix(matrixC);


    // run vectorization matrix multiply method
    start = omp_get_wtime();
    vectorization_method_sparse_edition(matrixA, matrixB, matrixC, thread_num);
    end = omp_get_wtime();
    cout << "step 2, vectorization method's runtime: ";
    runtime = end - start;
    cout << runtime << "s" << endl;
    cout << "speedup ratio: " << baseline /runtime << endl;
    cout << endl;
    write_matrix(matrixC, "step2_result.txt");
    clean_matrix(matrixC);


    // run change calculate order matrix multiply method
    start = omp_get_wtime();
    change_calculate_order_method_sparse_edition(matrixA, matrixB, matrixC, thread_num);
    end = omp_get_wtime();
    cout << "step 3, change calculate order method's runtime: ";
    runtime = end - start;
    cout << runtime << "s" << endl;
    cout << "speedup ratio: " << baseline /runtime << endl;
    cout << endl;
    write_matrix(matrixC, "step3_result.txt");
    clean_matrix(matrixC);


    // run divide matrix method
    start = omp_get_wtime();
    divide_matrix_method_sparse_edition(matrixA, matrixB, matrixC, thread_num);
    end = omp_get_wtime();
    cout << "step 4, divide matrix method's runtime: ";
    runtime = end - start;
    cout << runtime << "s" << endl;
    cout << "speedup ratio: " << baseline /runtime << endl;
    cout << endl;
    write_matrix(matrixC, "step4_result.txt");
    clean_matrix(matrixC);

    return 0;
}

void read_matrix(vector< vector<int> >& matrix, const string& file_name)
{
    ifstream ifs(file_name.c_str());
    for (vector<int>::size_type i = 0; i < matrix.size(); ++i) {
        for (vector<int>::size_type j = 0; j < matrix[i].size(); ++j) {
            ifs >> matrix[i][j];
        }
    }
}

void write_matrix(vector< vector<int> >& matrix, const string& file_name)
{
    ofstream ofs(file_name.c_str());
    for (vector<int>::size_type i = 0; i < matrix.size(); ++i) {
        for (vector<int>::size_type j = 0; j < matrix[i].size(); ++j) {
            ofs << matrix[i][j] << " ";
        }
        ofs << endl;
    } 
}

void clean_matrix(vector< vector<int> >& matrix)
{
    for (vector<int>::size_type i = 0; i < matrix.size(); ++i) {
        for (vector<int>::size_type j = 0; j < matrix[i].size(); ++j) {
            matrix[i][j] = 0;
        }
    } 
}
