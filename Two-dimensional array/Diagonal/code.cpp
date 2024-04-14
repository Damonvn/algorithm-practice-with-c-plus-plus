/* =============
Exercise - main diagonal, opposite diagonal of the matrix:

Assume the value of a square matrix is the difference between the 
sum of the numbers on the main diagonal and the sum of the 
numbers on the opposite diagonal. Given a matrix A of size 
N * N, find a square submatrix of A such that this submatrix 
has the maximum value.

Constraints: N (2 ≤ N ≤ 400), −10^9 ≤ A[i][j] ≤ 10^9

Example 1
1
2
1 2 
3 9
Ans: 5

Example 2
1
3
1 2 3
4 5 6
7 8 19
Ans: 10

Example 3
1
4
9 -2 -8 0
-6 -2 0 9
4 -5 6 1 
1 3 4 9
Ans: 26
============= */

#include <iostream>
#include <string>

using namespace std;

typedef long long ll;

ll ma[402][402], op[402][402] = {0};

int main(){
    int t;
    cin >> t;
    while(t--){
        int n; 
        cin >> n;
        int a[n+1][n+1];
        for(int i = 1; i <= n; i++){
            for(int j = 1; j <= n; j++){
                cin >> a[i][j];
            }
        }

        for(int i = 1; i <= n; i++){
            for(int j = 1; j <= n; j++){
                if(i == 1 || j == 1){
                    ma[i][j] = a[i][j];
                }
                else{
                    ma[i][j] =  a[i][j] +  ma[i-1][j-1];
                }
            }
        }

        for(int i = 1; i <= n; i++){
            for(int j = 1; j <= n; j++){
                if(i == 1 || j == n){
                    op[i][j] = a[i][j];
                }
                else{
                    op[i][j] =  a[i][j] +  op[i-1][j+1];
                }
            }
        }

        ll ans = 0;
        for(int i = 2; i <= n; i++){
            for(int j = 2; j <= n; j++){
                int tmp = min(i, j) - 1;
                int row = i - tmp, col = j - tmp;
                for(int k = 0; k < tmp; k++){
                    ll count = ma[i][j] - ma[row+k-1][col+k-1] - (op[i][col+k] - op[row+k-1][j+1]);
                    ans = max(ans, count);
                }
            }
        }
        cout<< "Ans: " << ans << endl;  
    }   
    return 0;
}

// Time complexity is n^3