#include <iostream>
#include <fstream>
using namespace std;

int main() {

	ifstream input_fp("bowling.inp");
	ofstream output_fp("bowling.out");

	int T, num, num2, strike, spare, sum;

	input_fp >> T;

	for (int a = 0; a < T; a++) {
		sum = 0, strike = 0, spare = 0;
		for (int i = 0; i < 10; i++) {
			input_fp >> num;
			sum += num;
			if (spare == 1) { //������� ��
				sum += num;
				spare = 0;
			}
			if (num == 10) { //��Ʈ����ũ�� ��
				if (strike == 0) strike++; //�ѹ� ��Ʈ����ũ
				else if (strike == 1) { //���� ��Ʈ����ũ
					sum += 10;
					strike++;
				}
				else { //3�� ���� ��Ʈ����ũ
					sum += 20;
				}
			}
			else {
				input_fp >> num2;
				sum += num2;
				if (strike == 1) { //�ѹ� ��Ʈ����ũ
					sum = sum + num + num2;
					strike = 0;
				}
				else if (strike == 2) { //���� ��Ʈ����ũ
					sum = sum + num*2 + num2;
					strike = 0;
				}
				if (num + num2 == 10) { //������� ��
					spare = 1;
				}
			}
		}
		if (spare == 1 || strike == 1) { //������ ������ ����� or ��Ʈ����ũ�� ��
			input_fp >> num;
			sum += num;
			if (strike == 1) {
				input_fp >> num;
				sum += num;
			}
		}
		else if (strike == 2) {
			input_fp >> num >> num2;
			sum = sum + num*2 + num2;
		}

		output_fp << sum << endl;
	}

	return 0;
}