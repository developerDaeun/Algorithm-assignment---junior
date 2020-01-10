#include <fstream>
#include <algorithm>
using namespace std;

ifstream input_fp("card.inp");
ofstream output_fp("card.out");

int main() {

   int T, n, temp_max, current_max, arr[1000], change[1000];

   input_fp >> T;

   for (int a = 0; a < T; a++) {
      input_fp >> n;
      for (int i = 0; i < n; i++) {
         input_fp >> arr[i];
         change[i] = arr[i];
      }
      current_max = max(change[0], change[1]) + change[3];
      
      if(n > 4) {
         change[3] = current_max;
         for (int i = 4; i < n; i++) {
            temp_max = max(change[i - 2], max(change[i - 3], change[i - 4]));
            if (i == n - 1) { // �������� ������ �ִ밪�� �ְ� break
               current_max = temp_max + change[i];
               continue;
            }
            if ((current_max < temp_max+change[i]) && i!=n-2){
               if(i==n-3 && temp_max!=change[n-5]){ // i�� n-3 �϶�
                  current_max = temp_max + change[i]; // ���� �ִ밪
                  change[i] = current_max; // �ٲ� �κ� ü����
               }
               else if(i!=n-3){
                  current_max = temp_max + change[i]; // ���� �ִ밪
                  change[i] = current_max; // �ٲ� �κ� ü����
               }
            }
         }
      }
      output_fp << current_max << endl;
   }
   input_fp.close();
   output_fp.close();

   return 0;
}