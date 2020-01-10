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
			if (spare == 1) { //스페어일 때
				sum += num;
				spare = 0;
			}
			if (num == 10) { //스트라이크일 때
				if (strike == 0) strike++; //한번 스트라이크
				else if (strike == 1) { //더블 스트라이크
					sum += 10;
					strike++;
				}
				else { //3번 연속 스트라이크
					sum += 20;
				}
			}
			else {
				input_fp >> num2;
				sum += num2;
				if (strike == 1) { //한번 스트라이크
					sum = sum + num + num2;
					strike = 0;
				}
				else if (strike == 2) { //더블 스트라이크
					sum = sum + num*2 + num2;
					strike = 0;
				}
				if (num + num2 == 10) { //스페어일 때
					spare = 1;
				}
			}
		}
		if (spare == 1 || strike == 1) { //마지막 프레임 스페어 or 스트라이크일 때
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