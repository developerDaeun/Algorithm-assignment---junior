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
	for (int i = n1_start; i <= n1_end; i++) {  // 전체가 1인지 0인지 D인지 체크
		for (int j = n2_start; j <= n2_end; j++) {
			if (bitmap[i][j] != temp) { // D일 때
				temp = -1; // D 이면 -1 저장
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
		///////////////////////////// 1사분면 /////////////////////////
		if ((n1_end - n1_start) % 2 == 0) // n1이 홀수개일때
			end1 = n1_start + ((n1_end - n1_start + 1) / 2);
		else                       // n1이 짝수개일때
			end1 = n1_start + ((n1_end - n1_start) / 2);
		if ((n2_end - n2_start) % 2 == 0) // n2가 홀수개일때
			end2 = n2_start + ((n2_end - n2_start + 1) / 2);
		else                      // n2가 짝수개일때
			end2 = n2_start + ((n2_end - n2_start) / 2);
		B_to_D(n1_start, end1, n2_start, end2);
		if (n2_start != n2_end) ////////// 2사분면(세로로 한줄 X)
			B_to_D(n1_start, end1, end2 + 1, n2_end);
		if (n1_start != n1_end) ///////// 3사분면(가로로 한줄 X)
			B_to_D(end1 + 1, n1_end, n2_start, end2);
		if ((n1_start != n1_end) && (n2_start != n2_end)) ////// 4사분면(가로,세로 둘다 한줄 X)
			B_to_D(end1 + 1, n1_end, end2 + 1, n2_end);

	}
	else { // 전체가 0이나 1일 때
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
		///////////////////////////// 1사분면 /////////////////////////
		if ((n1_end - n1_start) % 2 == 0) // n1이 홀수개일때
			end1 = n1_start + ((n1_end - n1_start + 1) / 2);
		else                       // n1이 짝수개일때
			end1 = n1_start + ((n1_end - n1_start) / 2);
		if ((n2_end - n2_start) % 2 == 0) // n2가 홀수개일때
			end2 = n2_start + ((n2_end - n2_start + 1) / 2);
		else                      // n2가 짝수개일때
			end2 = n2_start + ((n2_end - n2_start) / 2);
		D_to_B(n1_start, end1, n2_start, end2);
		if (n2_start != n2_end) ////////// 2사분면(세로로 한줄 X)
			D_to_B(n1_start, end1, end2 + 1, n2_end);
		if (n1_start != n1_end) ///////// 3사분면(가로로 한줄 X)
			D_to_B(end1 + 1, n1_end, n2_start, end2);
		if ((n1_start != n1_end) && (n2_start != n2_end)) ////// 4사분면(가로,세로 둘다 한줄 X)
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

		if (c == 'B') { // B 를 읽고 D 로 출력
			output_fp << "D " << n1 << " " << n2 << endl;
			for (int i = 0; i < n1; i++) { // bitmap 배열에 넣기
				for (int j = 0; j < n2; j++) {
					input_fp >> c;
					bitmap[i][j] = c - '0';
				}
			}
			B_to_D(0, n1 - 1, 0, n2 - 1); // D로 변환 후 출력
			output_fp << endl;
		}
		else { // D 를 읽고 B 로 출력
			input_fp >> s;
			if(s.size() == 50) {
				while (1) {
					input_fp >> temp;
					s += temp;
					if (temp.size() < 50) { // break 문
						if (temp.size() > 1) { // ex) B or D 를 새로 읽었을때
							if (temp[1] == ' ')
								check = 1;
						}
						break;
					}
				}
			}
			output_fp << "B " << n1 << " " << n2 << endl;
			D_to_B(0, n1 - 1, 0, n2 - 1); // B로 변환
			for (int i = 0; i < n1; i++) { // B 출력
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