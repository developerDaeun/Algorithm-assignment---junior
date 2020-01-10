#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;
int paper[4001][4001];
int none, part, all;

struct point {
	int paper_seq_num;
	int point;
};

vector<point> x_point;
vector<point> y_point;

bool compare_paper(point a, point b) {
	return a.point < b.point;
}

bool compare_paper2(point a, point b) {
	if (a.paper_seq_num == b.paper_seq_num)
		return a.point < b.point;
	return a.paper_seq_num < b.paper_seq_num;
}

void change_point_num() { // 좌표압축 번호로 갱신
	int tmp = 0, num = x_point[0].point;
	x_point[0].point = 0;
	for (int i = 1; i < x_point.size(); i++) {
		if (x_point[i].point != num) {
			num = x_point[i].point;
			++tmp;
			x_point[i].point = tmp;
		}
		else
			x_point[i].point = tmp;
	}
	tmp = 0;
	num = y_point[0].point, y_point[0].point = 0;
	for (int i = 1; i < y_point.size(); i++) {
		if (y_point[i].point != num) {
			num = y_point[i].point;
			++tmp;
			y_point[i].point = tmp;
		}
		else
			y_point[i].point = tmp;
	}
}

void drawing_paper() {
	for (int i = 0; i < x_point.size(); i=i+2) {
		for (int x = x_point[i].point; x < x_point[i+1].point; x++) {
			for (int y = y_point[i].point; y < y_point[i+1].point; y++) {
				paper[x][y] = x_point[i].paper_seq_num;
			}
		}
	}
}

void counting_paper() {
	int cnt, total;
	for (int i = 0; i < x_point.size(); i = i + 2) {
		cnt = 0;
		for (int x = x_point[i].point; x < x_point[i + 1].point; x++) {
			for (int y = y_point[i].point; y < y_point[i + 1].point; y++) {
				if (paper[x][y] != x_point[i].paper_seq_num) {
					cnt++;
				}
			}
		}
		total = (x_point[i + 1].point - x_point[i].point) * (y_point[i + 1].point - y_point[i].point);
		if (cnt == 0) all++;
		else if (cnt < total) part++;
		else none++;
	}
}

int main() {

	ifstream input_fp("paper.inp");
	ofstream output_fp("paper.out");

	int n, x, y, w, h;
	input_fp >> n;

	for (int i = 0; i < n; i++) {
		input_fp >> x >> y >> w >> h;
		x_point.push_back({ i, x });
		x_point.push_back({ i, x + w });
		y_point.push_back({ i, y });
		y_point.push_back({ i, y + h });
	}
	sort(x_point.begin(), x_point.end(), compare_paper);
	sort(y_point.begin(), y_point.end(), compare_paper);
	change_point_num();
	sort(x_point.begin(), x_point.end(), compare_paper2);
	sort(y_point.begin(), y_point.end(), compare_paper2);
	drawing_paper();
	counting_paper();
	output_fp << none << " " << part << " " << all;

	input_fp.close();
	output_fp.close();

	return 0;
}