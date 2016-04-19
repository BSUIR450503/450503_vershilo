#include <iostream>
#include <string>
#include <fstream>
#include <conio.h>
#define MAX 1024

using namespace std;

unsigned fibonachi (unsigned num) {
	unsigned i = 1, a = 0, b = 1, s;
 
	while (i++ < num) {
		s = a;
		a = b;
		b = s + a;
	}
	return b;
}

int main() {
	double input;
	double output;
	fstream input_file;
	input_file.open("temp", ios::in | ios::binary);
	if (!input_file) {
		cout << "No input number" << endl;
		return 1;
	}

	input_file >> input;
	input_file.close();

	output = fibonachi(input);

	remove("temp");

	fstream output_file;
	output_file.open("temp", ios::app | ios::binary);
	if (!output_file) {
		cout << "Error open file" << endl;
		return 1;
	}
	output_file << output;
	output_file.close();
	getch();
	return 0;
}