/* =============
Exercise:

Given a square matrix A[][] of size n, where the elements of the matrix are 
sorted in ascending order row-wise and column-wise, we need to find the k-th 
smallest element of the matrix. For example, in a 4x4 matrix shown below, the
3rd smallest element is 20, and the 7th smallest element is 30.

T, n, k, A[i][j] satisfy the constraints: 
1 ≤ T ≤ 1000; 
1 ≤ n, k ≤ 1000; 
1 ≤ n, k ≤ 1000000; 
1 ≤ A[i][j] ≤ 10^4.

Example 1
1
3 7
1 2 3 
4 5 6
7 8 9
Ans: 7

Example 2
1
4 3
10 20 30 40
15 25 35 45
24 29 37 48
32 33 39 50
Ans: 20

Example 3
1
4 7
10 20 30 40
15 25 35 45
24 29 37 48
32 33 39 50
Ans: 30

============= */

#include <iostream>
#include <string>
#include <map>
#include <queue>
#include <utility>

using namespace std;

int a[1000][1000];

int main(){
    int t;
    cin >> t;
    while(t--){
        int n, k; 
        cin >> n >> k;
        int a[n][n];
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                cin >> a[i][j];
            }
        }
        map<int, int> rowMap;
        for(int i = 0; i < n; i++){
            if(i == 0){
                rowMap[i] = 1;
            }else{
                rowMap[i] = 0;
            }
        }
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> minPriorityQueue;
        for(int i = 1; i < n; i++){
            pair<int, int> tmp;
            tmp.first = a[i][0];
            tmp.second = i;
            minPriorityQueue.push(tmp);
        }
        int row = 0; 
        int stt = 1;
        int minValue = a[0][0];

        while(stt < k){
            if(rowMap[row] < n){
                pair<int, int> tmp;
                tmp.first = a[row][rowMap[row]];
                tmp.second = row;
                minPriorityQueue.push(tmp);
            }
            minValue = minPriorityQueue.top().first;
            row = minPriorityQueue.top().second;
            minPriorityQueue.pop();  
            if(rowMap[row] < n) ++rowMap[row];
            ++stt;
        } 
        cout << "Ans: " << minValue << endl;
    }   
    return 0;
}

// Time complexity: k*log(n) + n*log(n)
