#include <fstream>
using namespace std;

int dp[101][101][101];

ifstream input_fp("coin.inp");
ofstream output_fp("coin.out");

int check(int first, int second, int third) { // 앞 세개중 하나라도 -1있으면 1 반환
	for (int i = first; i > 0 && i > first-3; i--) { // 3가지 경우 모두확인
		if (dp[i - 1][second][third] == -1)
			return 1;
	}
	for (int i = second; i > 0 && i > second-3; i--) {
		if (dp[first][i - 1][third] == -1)
			return 1;
	}
	for (int i = third; i > 0 && i > third-3; i--) {
		if (dp[first][second][i - 1] == -1)
			return 1;
	}
	return -1;
}
int main() {

	int n, A, B, C;

	input_fp >> n;
	for (int i = 0; i <= 100; i++) { // dp 배열 생성
		for (int j = 0; j <= 100; j++) {
			for (int k = 0; k <= 100; k++) {
				if (i == 0 && j == 0 && k == 0) continue;
				else dp[i][j][k] = check(i, j, k);
			}
		}
	}
	for (int a = 0; a < n; a++) {
		input_fp >> A >> B >> C;
		output_fp << "(" << A << " " << B << " " << C << ") : " << dp[A][B][C] << endl;
	}
	input_fp.close();
	output_fp.close();

	return 0;
}