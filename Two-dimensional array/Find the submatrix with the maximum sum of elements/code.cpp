/* =============
Exercise - Find the submatrix with the maximum sum of elements

Given a matrix A[n][m], your task is to find the submatrix of A[][] with 
the maximum sum of elements. For example, with the matrix below, you 
should find the submatrix with the maximum sum of elements, which is 29.

t: number of test cases
t, m, n, A[i][j] satisfy the constraints: 
1 ≤ t ≤ 100; 
1 ≤ n, m ≤ 200;
-10^5 ≤ A[i][j] ≤ 10^5


example 1
1
3 2
-1 5
7 -6
-3 4
max area: 7
row1, row2: 1, 1
col1, col2: 0, 0

example 2
1
4 5
1 2 -1 -4 -20
-8 -3 4 2 1
 3 8 10 1 3
-4 -1 1 7 -6
max area: 29
row1, row2: 1, 3
col1, col2: 1, 3
============= */

#include <iostream>
#include <string>



using namespace std;

pair<int, pair<int, int>> kadane (int a[], int n){
    pair<int, pair<int, int>> ans;
    int left = 0;
    int left_max = 0;
    int right_max = 0;
    int sum_end_here = 0;
    int res = 0;
    for(int i = 0; i < n; i++){
        sum_end_here += a[i];
        if(res < sum_end_here){
            res = sum_end_here;
            left_max = left;
            right_max = i;
        }
        if(sum_end_here < 0 || sum_end_here == 0){
            sum_end_here = 0;
            if(i < n - 1) ++left;
        }
    }
    ans.first = res;
    ans.second.first = left_max;
    ans.second.second = right_max;
    return ans;
}

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
        int max_area = INT_MIN;
        int r1, r2, c1, c2;
        int tmp[n];
        for(int l = 0; l < m; l++){
            for(int i = 0; i < n; i++){
                tmp[i] = 0;
            }
            for(int r = l; r < m; r++){
                for(int i = 0; i < n; i++){
                    tmp[i] += a[i][r];
                }
                pair<int, pair<int, int>> res = kadane(tmp, n);
                if(res.first > max_area){
                    max_area = res.first;
                    r1 = res.second.first;
                    r2 = res.second.second;
                    c1 = l;
                    c2 = r;
                }
            }
        }
        cout << "max area: " << max_area << endl;
        cout << "row1, row2: " << r1 << " " << r2 << endl;
        cout << "col1, col2: " << c1 << " " << c2 << endl;
    }   
    return 0;
}

//Time complexity if n >= m: O(n*m^2)
//Time complexity if n < m: O(m*n^2)
