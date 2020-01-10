#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;
vector<string> v;

int main() {

	ifstream input_fp("palindrome.inp");
	ofstream output_fp("palindrome.out");

	int T;
	string s;

	input_fp >> T;
	for (int a = 0; a < T; a++) {
		input_fp >> s;
		v.push_back(s);
	}

	return 0;
}