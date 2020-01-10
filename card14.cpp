#include <fstream>
#include <algorithm>
using namespace std;

ifstream input_fp("card14.inp");
ofstream output_fp("card14.out");

int main() {

	int T, n, arr[1000], dp[1000][1000], total[1001];
	input_fp >> T;

	for (int a = 0; a < T; a++) {
		input_fp >> n;
		total[0] = 0;
		for (int i = 0; i < n; i++) { // total(더한 누적 값 배열) 생성
			input_fp >> arr[i];
			total[i + 1] = total[i] + arr[i];
		}
		for (int i = 0; i < n; i++) { // dp 배열 초기화
			for (int j = 0; j < n; j++)
				dp[i][j] = arr[i];
		}
		for (int i = 2; i < n; i++) {
			for (int j = i; j < n; j++) {
				dp[j][j - i] += (total[j] - total[j - i]) - max(dp[j - 1][j - i], dp[j - i][j - 1]);
				dp[j - i][j] += (total[j + 1] - total[j - i + 1]) - max(dp[j - i + 1][j], dp[j][j - i + 1]);
			}
		}
		output_fp << max(dp[0][n - 1], dp[n - 1][0]) << endl;
	}
	input_fp.close();
	output_fp.close();

	return 0;
}