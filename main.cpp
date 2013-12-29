#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include <omp.h>

using namespace std;

void generate_random_matrix(int size, const string& file_name);
void read_matrix(vector< vector<int> >& matrix, const string& filename);
void write_matrix(vector< vector<int> >& matrix, const string& file_name);

vector< vector<int> > basic_method(const vector< vector<int> >& matrixA,
                                   const vector< vector<int> >& matrixB);

vector< vector<int> > vectorization_method(const vector< vector<int> >& matrixA,
                                            const vector< vector<int> >& matrixB);

vector< vector<int> > change_calculate_order_method(const vector< vector<int> >& matrixA,
                                                    const vector< vector<int> >& matrixB);

vector< vector<int> > divide_matrix_method(const vector< vector<int> >& matrixA,
                                            const vector< vector<int> >& matrixB);

int main()
{
    int target_size = 1000;

    // generate and read matrix A
    generate_random_matrix(target_size, "matrix_a.txt");
    vector< vector<int> > matrixA(target_size, vector<int>(target_size));
    read_matrix(matrixA, "matrix_a.txt");

    // generate and read matrix B
    generate_random_matrix(target_size, "matrix_b.txt");
    vector< vector<int> > matrixB(target_size, vector<int>(target_size));
    read_matrix(matrixB, "matrix_b.txt");

    double start, end;

    cout.setf(ios::fixed);
    cout.precision(2);
    // run basic matrix multiply method
    start = omp_get_wtime();
    vector< vector<int> > matrixC = basic_method(matrixA, matrixB);
    end = omp_get_wtime();
    cout << "step 1, basic method's runtime: ";
    cout << end - start << "s" << endl;
    cout << endl;
    write_matrix(matrixC, "step1_result.txt");


    // run vectorization matrix multiply method
    start = omp_get_wtime();
    matrixC = vectorization_method(matrixA, matrixB);
    end = omp_get_wtime();
    cout << "step 2, vectorization method's runtime: ";
    cout << end - start << "s" << endl;
    cout << endl;
    write_matrix(matrixC, "step2_result.txt");


    // run change calculate order matrix multiply method
    start = omp_get_wtime();
    matrixC = change_calculate_order_method(matrixA, matrixB);
    end = omp_get_wtime();
    cout << "step 3, change calculate order method's runtime: ";
    cout << end - start << "s" << endl;
    cout << endl;
    write_matrix(matrixC, "step3_result.txt");

    // run divide matrix method
    start = omp_get_wtime();
    matrixC = change_calculate_order_method(matrixA, matrixB);
    end = omp_get_wtime();
    cout << "step 4, divide matrix method's runtime: ";
    cout << end - start << "s" << endl;
    cout << endl;
    write_matrix(matrixC, "step4_result.txt");

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