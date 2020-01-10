#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <sstream>
using namespace std;

struct Root {
	char c;
	int num;
};
struct cmp {
	bool operator()(Root a, Root b) {
		return a.num < b.num;
	}
};
priority_queue<Root, vector<Root>, cmp> que;
string tree;
int cnt, check;

ifstream input_fp("tree.inp");
ofstream output_fp("tree.out");

void print_preorder() { //������ȸ
	cnt = 0;
	for (int i = 0; i < tree.size(); i++) {
		if (tree[i] == ' ' || tree[i] == ')')
			continue;
		else if (tree[i] == '(') {
			output_fp << "r" << cnt << endl;
			cnt++;
		}
		else {
			output_fp << tree[i];
			i++;
			for (;; i++) {
				if (tree[i] != ' ') {
					output_fp << tree[i];
				}
				else break;
			}
			output_fp << endl;
		}
	}
}

void print_inorder() { //������ȸ
	Root temp;
	stringstream s;
	string a, b, c;
	check = 0, cnt = 0;
	for (int i = 0; i < tree.size(); i++) {
		if (tree[i] == ' ')
			continue;
		else if (tree[i] == '(') { // ��Ʈ ������ ��
			if (check == 1) check = 0;
			////////// ť�� ��Ʈ push
			temp.c = 'r';
			temp.num = cnt;
			que.push(temp);
			cnt++;
		}
		else if (tree[i] == ')') { // ť���� ��Ʈ pop
			if (check == 0) {
				if (!que.empty()) {
					s.str("");
					s << que.top().c << que.top().num;
					a = s.str();
					output_fp << a << endl;
					que.pop();
				}
				check = 1;
			}
			else check = 0;
		}
		else { 
			 //���� �ܸ���� ���
			output_fp << tree[i];
			i++;
			for (;; i++) {
				if (tree[i] != ' ') {
					output_fp << tree[i];
				}
				else break;
			}
			output_fp << endl;
			if (!que.empty()) { // ��Ʈ ���
				s.str("");
				s << que.top().c << que.top().num;
				a = s.str();
				output_fp << a << endl;
				que.pop();
			}
		}
	}
}

int main() {

	int K;

	input_fp >> K;
	getline(input_fp, tree);

	for (int a = 0; a < K; a++) {
		getline(input_fp, tree);
		output_fp << tree << endl << "Preorder" << endl;
		print_preorder();
		output_fp << "Inorder" << endl;
		print_inorder();
	}

	return 0;
}