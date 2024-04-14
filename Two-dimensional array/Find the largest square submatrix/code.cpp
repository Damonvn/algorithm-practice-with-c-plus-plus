/* =============
Exercise - Find the largest square submatrix:
Given a matrix A[n][m] contains only the numbers 0 and 1, find the largest square
submatrix with all elements equal to 1. For example, in the matrix below, the 
largest square submatrix with all elements equal to 1 has a size of 3x3.

0 1 1 0 1
1 1 0 1 0
0 1 1 1 0
1 1 1 1 0
1 1 1 1 1
0 0 0 0 0

T, n, n satisfy the constraints: 1 ≤ T ≤ 100; 1 ≤ n, n ≤ 1000

Example 1
1
6 5
0 1 1 0 1
1 1 0 1 0
0 1 1 1 0
1 1 1 1 0
1 1 1 1 1
0 0 0 0 0
Ans: 3

Example 2
1
6 7
0 1 1 0 1 0 1
0 0 1 1 1 1 0
0 1 1 1 1 1 0
1 1 1 1 1 1 1
1 0 1 1 1 1 1
0 1 1 0 1 1 0
Ans: 4


============= */

#include <iostream>
#include <string>

using namespace std;

int main(){
    int t;
    cin >> t;
    while(t--){ 
        int n, m;
        cin >> n >> m;
        int a[n][m];
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                cin >> a[i][j];
            }
        }
        int size[n][m];
        int ans = INT_MIN;
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                if(i == 0 || j == 0){
                    size[i][j] = a[i][j];
                }else{
                    if(a[i][j] == 0){
                        size[i][j] = 0;
                    }else{
                        size[i][j] = 1 + min(size[i-1][j-1], min(size[i][j-1], size[i-1][j]));
                    }
                }
                ans = max(ans, size[i][j]);
            }
        }
        cout << "Ans: " << ans << endl;
    }   
    return 0;
}

// Time complexity: O(n^2)

