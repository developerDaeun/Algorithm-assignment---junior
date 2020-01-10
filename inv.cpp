#include <fstream>
using namespace std;

long long seq[20][100000], temp[20][100000];
long long num, cnt, before;

void merge(long long low, long long mid, long long high) {
	before = -1;
	long long index1 = low, index2 = mid + 1, tmp = low;
	while (index1 <= mid && index2 <= high) {
		if (seq[num][index1] > seq[num][index2]) { // 오른쪽이 더 작으면
			temp[num][tmp] = seq[num][index2];
			if (before != seq[num][index2]) // 같은 숫자 만나면 카운트 안되게
				cnt += (mid + 1 - index1);
			before = seq[num][index2];
			tmp++, index2++;
		}
		else { // 왼쪽이 더 작으면
			temp[num][tmp] = seq[num][index1];
			tmp++, index1++;
			before = -1;
		}
	}
	while (index1 <= mid) { // 왼쪽 리스트 남은거 넣기
		temp[num][tmp] = seq[num][index1];
		tmp++, index1++;
	}
	while (index2 <= high) { // 오른쪽 리스트 남은거 넣기
		temp[num][tmp] = seq[num][index2];
		tmp++, index2++;
	}
	for (int i = low; i < high + 1; i++) { // 정렬된 index만 원래 seq index와 교환하기
		if(seq[num][i] != temp[num][i])
			seq[num][i] = temp[num][i];
	}
}

void merge_sort(long long low, long long high) {
	long long mid;
	if (low < high) {
		mid = (low + high) / 2;
		merge_sort(low, mid);
		merge_sort(mid + 1, high);
		merge(low, mid, high);
	}
}

int main() {

	int T, N;

	ifstream input_fp("inv.inp");
	ofstream output_fp("inv.out");

	input_fp >> T;

	for (int i = 0; i < T; i++) {
		input_fp >> N;
		for (int j = 0; j < N; j++) {
			input_fp >> seq[i][j];
		}
		num = i; // 몇번째 케이스인지
		merge_sort(0, N-1);
		output_fp << cnt << endl;
		cnt = 0;
	}

	input_fp.close();
	output_fp.close();

	return 0;
}