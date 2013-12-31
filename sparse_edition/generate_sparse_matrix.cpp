#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std;

// set zero probability to 0.8
const double zero_probability = 0.8;
const int number_range = 1000;

void generate_sparse_matrix(int size, const string& file_name)
{
	ofstream ofs(file_name.c_str());
	if (!ofs) {
		cout << "file can't open" << endl;
		return;
	}

	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			int number;
			if ((rand() % 10 + 1) < 8) {
				number = 0;
			}
			else {
			 	number = rand() % number_range + 1;
			}
			
			ofs << number << " ";
		}
		ofs << endl;
	}

	ofs.close();
}
