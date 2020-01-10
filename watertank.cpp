#include <fstream>
#include <vector>
#include <queue>
using namespace std;

ifstream input_fp("watertank.inp");
ofstream output_fp("watertank.out");

struct information {
	int x, y, v;
};

int T, l, w, h, visit[1002][1002], temp, temp_x, temp_y, temp_v, total; // l:����, w:����, h:����
vector<vector<information> > tank;
struct cmp {
	bool operator()(information a, information b) {
		return a.v > b.v;
	}
};
priority_queue<information, vector<information>, cmp> que;

int main() {

	input_fp >> T;
	while (T--) {
		input_fp >> l >> w >> h;
		tank.assign(l + 1, vector<information>(w + 1));
		for (int i = 0; i < l + 1; i++) {
			for (int j = 1; j < w + 1; j++) { // ���� ���� 1
				input_fp >> temp;
				if (temp >= 0 && tank[i][j].v > temp)
					tank[i][j].v = temp;
				if (temp >= 0 && tank[i + 1][j].v > temp) // �� ������ ���� �ʱ�ȭ
					tank[i + 1][j].v = temp;
			}
		}
		for (int i = 1; i < l + 1; i++) { // ���� ���� 2
			for (int j = 0; j < w + 1; j++) {
				input_fp >> temp;
				if (temp >= 0 && tank[i][j].v > temp)
					tank[i][j].v = temp;
				if (temp >= 0 && tank[i][j + 1].v > temp) // �� ������ ���� �ʱ�ȭ
					tank[i][j + 1].v = temp;
			}
		}
		for (int i = 0; i < l; i++) {  // ����ũ ��ġ �ֱ�, que �� �ֱ�
			for (int j = 0; j < w; j++) {
				tank[i][j].x = i, tank[i][j].y = j; 
				que.push(tank[i][j]);
			}
		}
		while (!que.empty()) { // que�� �� ������
			information temp_tank;
			temp_tank = que.top();
			temp_x = temp_tank.x, temp_y = temp_tank.y, temp_v = temp_tank.v;
			que.pop();
			
		}
		output_fp << total << '\n';
		total = 0, tank.clear(); // total ���� ���� �ʱ�ȭ ��Ű��
		memset(visit, 0, sizeof(visit)); // visit �Լ� �ʱ�ȭ
	}
	input_fp.close(), output_fp.close();
	return 0;
}