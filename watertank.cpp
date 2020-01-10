#include <fstream>
#include <vector>
#include <queue>
using namespace std;

ifstream input_fp("watertank.inp");
ofstream output_fp("watertank.out");

struct information {
	int x, y, v;
};

int T, l, w, h, visit[1002][1002], temp, temp_x, temp_y, temp_v, total; // l:세로, w:가로, h:높이
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
			for (int j = 1; j < w + 1; j++) { // 벡터 생성 1
				input_fp >> temp;
				if (temp >= 0 && tank[i][j].v > temp)
					tank[i][j].v = temp;
				if (temp >= 0 && tank[i + 1][j].v > temp) // 더 작으면 부피 초기화
					tank[i + 1][j].v = temp;
			}
		}
		for (int i = 1; i < l + 1; i++) { // 벡터 생성 2
			for (int j = 0; j < w + 1; j++) {
				input_fp >> temp;
				if (temp >= 0 && tank[i][j].v > temp)
					tank[i][j].v = temp;
				if (temp >= 0 && tank[i][j + 1].v > temp) // 더 작으면 부피 초기화
					tank[i][j + 1].v = temp;
			}
		}
		for (int i = 0; i < l; i++) {  // 물탱크 위치 넣기, que 에 넣기
			for (int j = 0; j < w; j++) {
				tank[i][j].x = i, tank[i][j].y = j; 
				que.push(tank[i][j]);
			}
		}
		while (!que.empty()) { // que가 빌 때까지
			information temp_tank;
			temp_tank = que.top();
			temp_x = temp_tank.x, temp_y = temp_tank.y, temp_v = temp_tank.v;
			que.pop();
			
		}
		output_fp << total << '\n';
		total = 0, tank.clear(); // total 값과 벡터 초기화 시키기
		memset(visit, 0, sizeof(visit)); // visit 함수 초기화
	}
	input_fp.close(), output_fp.close();
	return 0;
}