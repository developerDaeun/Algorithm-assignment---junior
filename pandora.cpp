#include <fstream>
#include <string>
#include <vector>
using namespace std;
string s;
int cnt, check1, check2, bbefore, before, current;

ifstream input_fp("pandora.inp");
ofstream output_fp("pandora.out");

int check() {
	bbefore = 0, before = 0, current = 0;
	for (int i = 0; i < s.size(); i++) {
		bbefore = before, before = current;
		if (s[i] == 'L') {
			if (current < 3) current++;
			else current = 0;
		}
		else {
			if (current == 0) current = 3;
			else current--;
		}
		if (i > 1) {
			if (bbefore == 1 && before == 0 && current == 3) check2 = 1;
			if (bbefore == 3 && before == 2 && current == 1) check2 = 1;
			if (bbefore == 0 && before == 3 && current == 2) check1 = 1;
			if (bbefore == 2 && before == 1 && current == 0) check1 = 1;
		}
	}
	if (check1 + check2 == 2) return 0;
	else if (check1 + check2 == 1) return 1;
	return 2;
}

int main() {

	int T;
	
	input_fp >> T;
	for (int i = 0; i < T; i++) {
		input_fp >> s;
		s = s + s[0] + s[1];
		output_fp << check() << endl;
		check1 = 0, check2 = 0;
	}

	input_fp.close();
	output_fp.close();

	return 0;
}