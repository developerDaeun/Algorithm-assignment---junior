#include <vector>
#include <fstream>
#include <algorithm>
using namespace std;

int arr[201][201][201];

void cube_count(int i, int j, int k) {
	int min = 2000000000;
	for (int a = i / 2; a > 0; --a) {
		if (min > arr[a][j][k] + arr[i - a][j][k])
			min = arr[a][j][k] + arr[i - a][j][k];
	}
	for (int a = j / 2; a > 0; --a) {
		if (min > arr[i][a][k] + arr[i][j - a][k])
			min = arr[i][a][k] + arr[i][j - a][k];
	}
	for (int a = k / 2; a > 0; --a) {
		if (min > arr[i][j][a] + arr[i][j][k - a])
			min = arr[i][j][a] + arr[i][j][k - a];
	}
	arr[i][j][k] = min, arr[i][k][j] = min, arr[j][i][k] = min, arr[j][k][i] = min,
		arr[k][i][j] = min, arr[k][j][i] = min;
}

ifstream input_fp("cube16.inp");
ofstream output_fp("cube16.out");
int main() {
	int T, W, L, H;
	input_fp >> T;

	for (int i = 1; i < 201; i++) {
		for (int j = 1; j < 201; j++) {
			for (int k = 1; k < 201; k++) {
				if (i == j && j == k)
					arr[i][j][k] = 1;
				else if (arr[i][j][k] > 0) continue;
				else cube_count(i, j, k);
			}
		}
	}

	for (int i = 0; i < T; i++) {
		input_fp >> W >> L >> H;
		output_fp << arr[W][L][H] << endl;
	}

	input_fp.close();
	output_fp.close();

	return 0;
}