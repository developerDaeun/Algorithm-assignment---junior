#include <fstream>
#include <algorithm>
using namespace std;

int T, house_num, bin_num, num, arr[500], dp1[500][500], dp2[501][500];

ifstream input_fp("bin.inp");
ofstream output_fp("bin.out");

int adding_min_dis(int bin, int house) { // bin은 bin개수, house는 집 인덱스
	int min_dis = 2000000000;
	// 현재house개수 만큼 구하기
	for (int i = house; i > 0; --i) {
		if (bin - 1 > i + 1) break;
		if (min_dis > dp2[bin - 1][i - 1] + dp1[i][house])
			min_dis = dp2[bin - 1][i - 1] + dp1[i][house];
	}
	return min_dis;
}

int main() {

	input_fp >> T;
	for (int a = 0; a < T; a++) {
		input_fp >> house_num >> bin_num;
		for (int i = 0; i < house_num; i++) {
			input_fp >> num;
			arr[i] = num;
		}
		sort(arr, arr + house_num);
		for (int i = 0; i < house_num; i++) { // dp1 배열 구하기
			for (int j = i + 1; j < house_num; j++) {
				// dp1의 i번째줄 j-1의 결과에서 (j번째집부터 쓰레기통까지 거리 == j/2 ~ j)를 더하기
				dp1[i][j] = dp1[i][j - 1] + (arr[j] - arr[(j + i) / 2]);
			}
		}
		for (int i = 1; i < house_num; i++) // dp2의 첫째줄은 dp1의 첫째줄과 같음
			dp2[1][i] = dp1[0][i];
		for (int i = 2; i < bin_num + 1; i++) { // dp2 배열 구하기, i는 bin개수, j는 집 인덱스
			for (int j = i; j < house_num; j++)
				dp2[i][j] = adding_min_dis(i, j);
		}
		output_fp << dp2[bin_num][house_num - 1] << endl;
	}

	input_fp.close();
	output_fp.close();

	return 0;
}