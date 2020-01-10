#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

struct next_line {
   int num, y, next, islast;
};
bool compare(int a, int b) {
   return a > b;
}
struct next_line line[50][10000];
int min_num[50], result[50];
vector<int> seq[50];

int main() {

   ifstream input_fp("ladder.inp");
   ofstream output_fp("ladder.out");

   int n, x1, y1, x2, y2, max, min, last_num, last_y, temp;

   input_fp >> n;

   while (1) {
      input_fp >> x1 >> y1 >> x2 >> y2;
      if (x1 == 0 && y1 == 0 && x2 == 0 && y2 == 0) // 0 0 0 0 break
         break;
      seq[x1].push_back(y1), seq[x2].push_back(y2);
      line[x1][y1].num = x2, line[x1][y1].y = y2, line[x1][y1].islast = 0;
      line[x2][y2].num = x1, line[x2][y2].y = y1, line[x2][y2].islast = 0;
   }

   for (int i = 0; i < n; i++) { // seq 정렬
      sort(seq[i].begin(), seq[i].end(), compare);
   }
   for (int i = 0; i < n; i++) { // 사다리마다 min 값은 -1로 지정
      min = *min_element(seq[i].begin(), seq[i].end());
      line[i][min].islast = -1;
   }
   for (int i = 0; i < n; i++) { // 같은 사다리에서 다음 갈 숫자 넣기
      for (int j = 0; j < seq[i].size()-1; j++) {
         line[i][seq[i][j]].next = seq[i][j + 1];
      }
   }
   int check = 0;
   for (int i = 0; i < n; i++) {
      last_num = i, last_y = seq[i][0]; // 첫 max 값은 seq[i]의 첫번째 값
      while (1) {
         temp = last_num;
         last_num = line[last_num][last_y].num;
         last_y = line[temp][last_y].y;
         if (line[last_num][last_y].islast == -1) {
            result[last_num] = i;
            break;
         }
         last_y = line[last_num][last_y].next;
      }
   }

   for (int i = 0; i < n; i++)
      output_fp << result[i] << " ";

   input_fp.close();
   output_fp.close();

   return 0;
}