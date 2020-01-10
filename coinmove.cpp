#include <fstream>
using namespace std;

int T, P, K, S, arr[8][1000001];

ifstream input_fp("coinmove.inp");
ofstream output_fp("coinmove.out");

void make_dp() {
	int check = 0;
	for (int j = 1; j < S + 1; j++) {
		for (int i = 1; i < K + 1; i++) {
			if (i == j) arr[i][j] = 1; // i�� j ������ 1
			else if (i > j) arr[i][j] = -1; // j���� ū i�� ��� -1
			else if (j > i && (j - i) % P == 0) { // j - i �� P�� ����϶��� ������ -1
				if (j - i == 0) arr[i][j] = 1; // j-i�� 0�϶��� ��� 1
				else arr[i][j] = -1;
			}
			else {
				check = 0;
				for (int k = 1; k < K + 1; k++) {
					if (k != i && arr[k][j - i] == 1) { // �ϳ��� 1�� ������ -1
						check = 1;
						break;
					}
				}
				if (check == 1) arr[i][j] = -1;
				else arr[i][j] = 1;
			}
		}
	}
}

void check_dp() {
	int min = -1;
	for (int i = 1; i < K + 1; i++) {
		if (arr[i][S] == 1) {
			min = i;
			break;
		}
	}
	if (min == -1) output_fp << "-1" << endl;
	else output_fp << S - min << endl;
}

int main() {
	for (int i = 1; i < 8; i++) // S==0�϶� ��� �ʱ�ȭ -1
		arr[i][0] = -1;

	input_fp >> T;
	for (int i = 0; i < T; i++) {
		input_fp >> P >> K >> S;
		make_dp();
		check_dp();
	}
	input_fp.close();
	output_fp.close();

	return 0;
}