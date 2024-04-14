/* =============
Exercise - :
Given a matrix A[N][M] consisting only of the numbers 0 and 1, find the 
largest rectangular area with all elements equal to 1. For example, in 
the matrix below, the largest rectangular area with all elements equal 
to 1 has a size of 8.

0 1 1 0
1 1 1 1
1 1 1 1
1 1 0 0

T, n, m satisfy the constraints: 1 ≤ T ≤ 100; 1 ≤ N, M ≤ 1000

Example 1
1
3 3
1 0 1
1 1 1
1 1 0
Ans: 4

Example 2
1
4 4
0 1 1 0
1 1 1 1
1 1 1 1
1 1 0 0
Ans: 8

Example 3
1
5 5
1 1 0 1 0
1 0 1 1 0
1 1 1 0 1
0 1 1 0 1
0 1 1 0 1
Ans: 6

============= */

#include <iostream>
#include <string>
#include <stack>

using namespace std;


int max_area(int x[], int m){
    int res = 0;
    int i = 0;
    stack<int> st;
    while(i < m){
        if(st.empty() || x[i] >= x[st.top()]) st.push(i++);
        else{
            int top = st.top(); st.pop();
            if(st.empty()){
                res = max(res, i * x[top]);
            }else{
                res = max(res, x[top] * (i - st.top() - 1));
            }
        }
    }
    while(!st.empty()){
        int top = st.top(); st.pop();
        if(st.empty()){
            res = max(res, i * x[top]);
        }else{
            res = max(res, x[top] * (i - st.top() - 1));
        }
    }
    return res;
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
        int tmp[n][m];
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                if(i == 0) tmp[i][j] = a[i][j];
                else{
                    if(a[i][j] > 0){
                        tmp[i][j] = tmp[i-1][j] + 1;
                    }else{
                        tmp[i][j] = 0;
                    }
                }
            }
        }
        int ans = 0;
        for(int i = 0; i < n; i++){
            ans = max(ans, max_area(tmp[i], m));
        }
        cout << "Ans: " << ans << endl;
    } 
    return 0;
}

// Time complexity: O(n*m);

