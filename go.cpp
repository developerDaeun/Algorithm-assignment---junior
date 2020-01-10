#include <fstream>
#include <vector>
using namespace std;

int k, B_cnt, W_cnt, v[19][19], check_color_main;
char temp, arr[19][19], check[19][19];

ifstream input_fp("go.inp");
ofstream output_fp("go.out");

char find_start_color(int x, int y) { // 시작 색깔 찾기
	if (x - 1 >= 0) { // top
		if (check[x - 1][y] == 'B' || check[x - 1][y] == 'W')
			return check[x - 1][y];
		else if (check[x - 1][y] == 'N') {
			v[x - 1][y] = 1;
			return 'N';
		}
	}
	if (y - 1 >= 0) { // left
		if (check[x][y - 1] == 'B' || check[x][y - 1] == 'W')
			return check[x][y - 1];
		else if (check[x][y - 1] == 'N') {
			v[x][y - 1] = 1;
			return 'N';
		}
	}
	if (y + 1 < k) { // right
		if (check[x][y + 1] == 'B' || check[x][y + 1] == 'W')
			return check[x][y + 1];
		else if (check[x][y + 1] == 'N') {
			v[x][y + 1] = 1;
			return 'N';
		}
	}
	if (x + 1 < k) { // bottom
		if (check[x + 1][y] == 'B' || check[x + 1][y] == 'W')
			return check[x + 1][y];
		else if (check[x + 1][y] == 'N') {
			v[x + 1][y] = 1;
			return 'N';
		}
	}
	v[x][y] = 1;
	if (v[x - 1][y] == 0 && x - 1 >= 0) // top
		return find_start_color(x - 1, y);
	if (v[x][y - 1] == 0 && y - 1 >= 0) // left
		return find_start_color(x, y - 1);
	if (v[x][y + 1] == 0 && y + 1 < k)  // right
		return find_start_color(x, y + 1);
	if (v[x + 1][y] == 0 && x + 1 < k)  // bottom
		return find_start_color(x + 1, y);
	return 'N';
}

char go(int x, int y) { // 집 표시
	char c = 'v';
	v[x][y] = 1;
	if (v[x - 1][y] == 0 && x - 1 >= 0) { // top
		if (check[x - 1][y] != '.' && check[x - 1][y] != temp) // temp 와 다른 집이면
			check_color_main = 1;
		else if(check[x - 1][y] == '.')
			c = go(x - 1, y);
	}
	if (v[x][y - 1] == 0 && check_color_main == 0 && y - 1 >= 0) { // left
		if (check[x][y - 1] != '.' && check[x][y - 1] != temp)
			check_color_main = 1;
		else if (check[x][y - 1] == '.')
			c = go(x, y - 1);
	}
	if (v[x][y + 1] == 0 && check_color_main == 0 && y + 1 < k) { // right
		if (check[x][y + 1] != '.' && check[x][y + 1] != temp)
			check_color_main = 1;
		else if (check[x][y + 1] == '.')
			c = go(x, y + 1);
	}
	if (v[x + 1][y] == 0 && check_color_main == 0 && x + 1 < k) { // bottom
		if (check[x + 1][y] != '.' && check[x + 1][y] != temp)
			check_color_main = 1;
		else if (check[x + 1][y] == '.')
			c = go(x + 1, y);
	}
	if (check_color_main == 1) return 'N';
	return temp;
}

int main() {

	input_fp >> k;

	for (int i = 0; i < k; i++) { // 바둑판 생성
		for (int j = 0; j < k; j++) {
			input_fp >> arr[i][j];
				if (arr[i][j] == 'B') check[i][j] = 'B'; // B랑 W는 v 배열에 넣기
				else if (arr[i][j] == 'W') check[i][j] = 'W';
				else check[i][j] = '.';
		}
	}

	for (int i = 0; i < k; i++) {
		for (int j = 0; j < k; j++) {
			if (arr[i][j] == '.') {
				if (check[i][j] != 'B' && check[i][j] != 'W' && check[i][j] != 'N') {
					temp = find_start_color(i, j); // 시작 색깔 찾기
					if (temp != 'N') {
						for (int i = 0; i < k; i++) { // v 초기화
							for (int j = 0; j < k; j++) {
								if (v[i][j] == 1) v[i][j] = 0;
							}
						}
						temp = go(i, j); // 집 색깔 찾기
					}
					for (int i = 0; i < k; i++) { // 집 넣기
						for (int j = 0; j < k; j++) {
							if (check[i][j] == '.' && v[i][j] == 1)
								check[i][j] = temp;
						}
					}
					if (temp == 'N') {
						for (int i = 0; i < k; i++) { // v 초기화
							for (int j = 0; j < k; j++) {
								if (v[i][j] == 1) v[i][j] = 0;
							}
						}
					}
				}
			}
			check_color_main = 0;
		}
	}
	for (int i = 0; i < k; i++) {
		for (int j = 0; j < k; j++) {
			if (arr[i][j] == '.') {
				if (check[i][j] == 'B') B_cnt++;
				else if (check[i][j] == 'W') W_cnt++;
			}
		}
	}

	output_fp << B_cnt << " " << W_cnt;

	input_fp.close();
	output_fp.close();

	return 0;
}