#include <fstream>
#include <string>
#include <string>
using namespace std;

int n1, n2, bitmap[200][200], s_idx, cnt;
string s;

ifstream input_fp("bitmap.inp");
ofstream output_fp("bitmap.out");

void B_to_D(int n1_start, int n1_end, int n2_start, int n2_end) { 
	int temp = bitmap[n1_start][n2_start];
	int end1, end2, check = 0;
	for (int i = n1_start; i <= n1_end; i++) {  // ��ü�� 1���� 0���� D���� üũ
		for (int j = n2_start; j <= n2_end; j++) {
			if (bitmap[i][j] != temp) { // D�� ��
				temp = -1; // D �̸� -1 ����
				check = 1;
				break;
			}
		}
		if (check == 1) break;
	}
	if (temp == -1) {
		if (cnt == 50) {
			output_fp << endl;
			cnt = 0;
		}
		output_fp << 'D';
		cnt++;
		///////////////////////////// 1��и� /////////////////////////
		if ((n1_end - n1_start) % 2 == 0) // n1�� Ȧ�����϶�
			end1 = n1_start + ((n1_end - n1_start + 1) / 2);
		else                       // n1�� ¦�����϶�
			end1 = n1_start + ((n1_end - n1_start) / 2);
		if ((n2_end - n2_start) % 2 == 0) // n2�� Ȧ�����϶�
			end2 = n2_start + ((n2_end - n2_start + 1) / 2);
		else                      // n2�� ¦�����϶�
			end2 = n2_start + ((n2_end - n2_start) / 2);
		B_to_D(n1_start, end1, n2_start, end2);
		if (n2_start != n2_end) ////////// 2��и�(���η� ���� X)
			B_to_D(n1_start, end1, end2 + 1, n2_end);
		if (n1_start != n1_end) ///////// 3��и�(���η� ���� X)
			B_to_D(end1 + 1, n1_end, n2_start, end2);
		if ((n1_start != n1_end) && (n2_start != n2_end)) ////// 4��и�(����,���� �Ѵ� ���� X)
			B_to_D(end1 + 1, n1_end, end2 + 1, n2_end);

	}
	else { // ��ü�� 0�̳� 1�� ��
		if (cnt == 50) {
			output_fp << endl;
			cnt = 0;
		}
		output_fp << temp;
		cnt++;
	}
}

void D_to_B(int n1_start, int n1_end, int n2_start, int n2_end) {
	int end1, end2;
	if (s[s_idx] == 'D') {
		s_idx++;
		///////////////////////////// 1��и� /////////////////////////
		if ((n1_end - n1_start) % 2 == 0) // n1�� Ȧ�����϶�
			end1 = n1_start + ((n1_end - n1_start + 1) / 2);
		else                       // n1�� ¦�����϶�
			end1 = n1_start + ((n1_end - n1_start) / 2);
		if ((n2_end - n2_start) % 2 == 0) // n2�� Ȧ�����϶�
			end2 = n2_start + ((n2_end - n2_start + 1) / 2);
		else                      // n2�� ¦�����϶�
			end2 = n2_start + ((n2_end - n2_start) / 2);
		D_to_B(n1_start, end1, n2_start, end2);
		if (n2_start != n2_end) ////////// 2��и�(���η� ���� X)
			D_to_B(n1_start, end1, end2 + 1, n2_end);
		if (n1_start != n1_end) ///////// 3��и�(���η� ���� X)
			D_to_B(end1 + 1, n1_end, n2_start, end2);
		if ((n1_start != n1_end) && (n2_start != n2_end)) ////// 4��и�(����,���� �Ѵ� ���� X)
			D_to_B(end1 + 1, n1_end, end2 + 1, n2_end);
	}
	else {
		for (int i = n1_start; i <= n1_end; i++) {
			for (int j = n2_start; j <= n2_end; j++) {
				bitmap[i][j] = s[s_idx];
			}
		}
		s_idx++;
	}
}

int main() {

	int num, check = 0;
	char c;
	string temp;

	while (1) {
		if (check == 0)
			input_fp >> c >> n1 >> n2;
		else {
			c = s[0], n1 = s[2] - '0', n2 = s[4] - '0';
			check = 0;
		}
		if (c == '#') break;

		if (c == 'B') { // B �� �а� D �� ���
			output_fp << "D " << n1 << " " << n2 << endl;
			for (int i = 0; i < n1; i++) { // bitmap �迭�� �ֱ�
				for (int j = 0; j < n2; j++) {
					input_fp >> c;
					bitmap[i][j] = c - '0';
				}
			}
			B_to_D(0, n1 - 1, 0, n2 - 1); // D�� ��ȯ �� ���
			output_fp << endl;
		}
		else { // D �� �а� B �� ���
			input_fp >> s;
			if(s.size() == 50) {
				while (1) {
					input_fp >> temp;
					s += temp;
					if (temp.size() < 50) { // break ��
						if (temp.size() > 1) { // ex) B or D �� ���� �о�����
							if (temp[1] == ' ')
								check = 1;
						}
						break;
					}
				}
			}
			output_fp << "B " << n1 << " " << n2 << endl;
			D_to_B(0, n1 - 1, 0, n2 - 1); // B�� ��ȯ
			for (int i = 0; i < n1; i++) { // B ���
				for (int j = 0; j < n2; j++) {
					if (cnt == 50) {
						output_fp << endl;
						cnt = 0;
					}
					output_fp << bitmap[i][j] - '0';
					cnt++;
				}
			}
			output_fp << endl;
		}
		s_idx = 0, cnt = 0;
	}

	input_fp.close();
	output_fp.close();

	return 0;
}