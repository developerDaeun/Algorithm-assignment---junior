#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

string cube, last_cube;
stringstream cube1, cube2, cube1_temp, cube2_temp;
int r[2], g[2], b[2], cube2_num;

bool compare_color2() {
	cube2_temp.str("");
	if (cube2_num == 16)
		cube2_temp << cube[7] << cube[9] << cube[10] << cube[8];
	else if (cube2_num == 61)
		cube2_temp << cube[7] << cube[8] << cube[10] << cube[9];
	else if (cube2_num == 25)
		cube2_temp << cube[6] << cube[8] << cube[11] << cube[9];
	else if (cube2_num == 52)
		cube2_temp << cube[6] << cube[9] << cube[11] << cube[8];
	else if (cube2_num == 34)
		cube2_temp << cube[6] << cube[10] << cube[11] << cube[7];
	else if (cube2_num == 43)
		cube2_temp << cube[6] << cube[7] << cube[11] << cube[10];
	if (cube1_temp.str().find(cube2_temp.str()) != string::npos)
		return true;
	return false;
}

bool compare_color() {
	cube1.str(""); cube1_temp.str("");
	cube1 << cube[0] << cube[5]; // 첫번째 주사위의 1, 6
	cube1_temp << cube[1] << cube[3] << cube[4] << cube[2] // 첫번째 주사위의 2453 두개
		<< cube[1] << cube[3] << cube[4] << cube[2]; 
	cube2.str("");
	cube2 << cube[6] << cube[11]; // 두번째 주사위의 1, 6
	cube2_num = 16;
	if (cube1.str() == cube2.str())
		if (compare_color2() == true)
			return true;
	cube2.str("");
	cube2 << cube[11] << cube[6]; // 두번째 주사위의 6, 1
	cube2_num = 61;
	if (cube1.str() == cube2.str())
		if (compare_color2() == true)
			return true;
	cube2.str("");
	cube2 << cube[7] << cube[10]; // 두번째 주사위의 2, 5
	cube2_num = 25;
	if (cube1.str() == cube2.str())
		if (compare_color2() == true)
			return true;
	cube2.str("");
	cube2 << cube[10] << cube[7]; // 두번째 주사위의 5, 2
	cube2_num = 52;
	if (cube1.str() == cube2.str())
		if (compare_color2() == true)
			return true;
	cube2.str("");
	cube2 << cube[8] << cube[9]; // 두번째 주사위의 3, 4
	cube2_num = 34;
	if (cube1.str() == cube2.str())
		if (compare_color2() == true)
			return true;
	cube2.str("");
	cube2 << cube[9] << cube[8]; // 두번째 주사위의 4, 3
	cube2_num = 43;
	if (cube1.str() == cube2.str())
		if (compare_color2() == true)
			return true;
	return false;
}

ifstream input_fp("cube.inp");
ofstream output_fp("cube.out");

int main() {
	while (1) {
		input_fp >> cube;
		if (cube == last_cube) break;
		// 색깔 카운팅
		for (int i = 0; i < cube.size(); i++) {
			if (i < 6) {
				if (cube[i] == 'r') r[0]++;
				else if (cube[i] == 'g') g[0]++;
				else b[0]++;
			}
			else {
				if (cube[i] == 'r') r[1]++;
				else if (cube[i] == 'g') g[1]++;
				else b[1]++;
			}
		}
		if(r[0] != r[1] || g[0] != g[1] || b[0] != b[1]) // 색깔 갯수 다를 때
			output_fp << "FALSE" << endl;
		else if (compare_color() == false)
			output_fp << "FALSE" << endl;
		else
			output_fp << "TRUE" << endl;
		r[0] = 0, r[1] = 0, g[0] = 0, g[1] = 0, b[0] = 0, b[1] = 0;
		last_cube = cube;
	}
	
	input_fp.close(), output_fp.close();

	return 0;
}