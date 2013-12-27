#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std;

const int number_range = 1000;

void generate_random_matrix(int size, const string& file_name)
{
	ofstream ofs(file_name.c_str());
	if (!ofs) {
		cout << "file can't open" << endl;
		return;
	}

	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			int number = rand() % number_range + 1;
			ofs << number << " ";
		}
		ofs << endl;
	}

	ofs.close();
}
