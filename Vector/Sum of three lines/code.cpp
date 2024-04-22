/* =============
Exercise - sum of three power lines:

Country Alpha has a wind farm planned on a square grid of rows and columns. 
The rows are numbered from 1 to N from top to bottom, and the columns are 
numbered from 1 to N from left to right. The farm has M wind turbine stations 
numbered from 1 to M. The i-th station (1 ≤  i ≤ M) is located at the cell 
in row Ri, column Ci, and has a production capacity of Wi watts. The farm 
owner has signed a contract to supply electricity to a partner. The farm must 
install three power lines, each passing through a row or a column in the grid. 
The power lines can intersect but cannot overlap. The total supply capacity to 
the partner is the sum of the capacities of the turbine stations located within 
the three power lines. The farm needs to find a way to install the three power 
lines to maximize the total supply capacity.

Additionally, the company has Q adjustment plans. The j-th adjustment plan involves 
increasing the capacity of station Tj by an amount of Qj watts while keeping the 
capacities of all other stations unchanged. Note that the adjustment plans are 
independent, meaning each plan applies only to the initial state of the farm.

Requirement: Provide the maximum total capacity achievable when installing three 
power lines with the initial state of the farm and considering the Q adjustment plans.

Input:
The first line contains a positive integer T, which represents the number of test cases.

Each group of lines in the following set of lines describes one test case with the following structure:

- The first line contains three integers N, M, Q respectively, representing the size of the grid, 
  the number of electric stations, and the number of adjustment plans.
  Constraints: 3 ≤ N, M ≤ 500; 1 ≤  Q ≤ 500

- The i-th line among the following M lines contains three integers Ri, Ci, Wi respectively, representing 
  the row position, column position, and power of the i-th electric station. The data ensures that no two 
  stations are placed in the same cell.
  Constraints: 1 ≤ Ri, Ci ≤ N; 1 ≤ Wi ≤ 10^9; 

- The j-th line among the following Q lines contains two integers Tj and Dj, indicating an adjustment 
  plan to increase the power by Dj watts for the Tj-th electric station.
  Constraints: Constraints: 1 ≤ Tj ≤ M; 1 ≤ Dj ≤ 10^9.

Example

Input:
2
5 7 2
1 1 1
3 1 2
2 2 3
4 2 4
2 4 2
1 5 5
3 5 2
5 3
2 7
3 3 1
1 1 1
1 2 2
1 3 3
3 1

Output:
17
19
24
6
7

============= */

#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

struct transf {
    int r, c, w;
};
struct adjust {
    int index, value;
};
struct maxLines {
    long long maxSum;
    long long max3Rows;
    long long row1;
    long long row2;
    long long row3;
    long long max3Cols;
    long long col1;
    long long col2;
    long long col3;
};
vector<transf> a;
vector<long long> sumRow;
vector<long long> sumCol;
vector<adjust> adj;
vector<vector<long long>> costs;

maxLines find_max_3lines(int n){
    maxLines res;
    long long maxSum3Rows;
    long long row1;
    long long row2;
    long long row3;
    long long maxSum3Cols;
    long long col1;
    long long col2;
    long long col3;

    // Rows
    if(sumRow[2] > sumRow[1]){
        if(sumRow[2] > sumRow[0]){
            row1 = 2;
            if(sumRow[1] > sumRow[0]){
                row2 = 1;
                row3 = 0;
            }else{
                row2 = 0;
                row3 = 1;
            }
        }else{
            row1 = 0;
            row2 = 2;
            row3 = 1;
        }
    }else{
        if(sumRow[1] > sumRow[0]){
            row1 = 1;
            if(sumRow[2] > sumRow[0]){
                row2 = 2;
                row3 = 0;
            }else{
                row2 = 0;
                row3 = 2;
            }
        } else {
            row1 = 0;
            row2 = 1;
            row3 = 2;
        }
    }
    
    for(int i = 3; i < n; i++){
        if(sumRow[i] <= sumRow[row3]){
            continue;
        }
        else if(sumRow[i] >= sumRow[row1] ){
            row3 = row2;
            row2 = row1;
            row1 = i;
        }
        else if(sumRow[i] >= sumRow[row2] && sumRow[i] < sumRow[row1]){
            row3 = row2;
            row2 = i;
        }
        else if(sumRow[i] > sumRow[row3] && sumRow[i] < sumRow[row2]){
            row3 = i;
        }
    } 
    maxSum3Rows = sumRow[row1] + sumRow[row2] + sumRow[row3];

    // Cols
    if(sumCol[2] > sumCol[1]){
        if(sumCol[2] > sumCol[0]){
            col1 = 2;
            if(sumCol[1] > sumCol[0]){
                col2 = 1;
                col3 = 0;
            }else{
                col2 = 0;
                col3 = 1;
            }
        }else{
            col1 = 0;
            col2 = 2;
            col3 = 1;
        }
    }else{
        if(sumCol[1] > sumCol[0]){
            col1 = 1;
            if(sumCol[2] > sumCol[0]){
                col2 = 2;
                col3 = 0;
            }else{
                col2 = 0;
                col3 = 2;
            }
        } else {
            col1 = 0;
            col2 = 1;
            col3 = 2;
        }
    }

    for(int i = 3; i < n; i++){
        if(sumCol[i] <= sumCol[col3]){
            continue;
        }
        else if(sumCol[i] >= sumCol[col1] ){
            col3 = col2;
            col2 = col1;
            col1 = i;
        }
        else if(sumCol[i] >= sumCol[col2] && sumCol[i] < sumCol[col1]){
            col3 = col2;
            col2 = i;
        }
        else if(sumCol[i] > sumCol[col3] && sumCol[i] < sumCol[col2]){
            col3 = i;
        }
    } 
    maxSum3Cols = sumCol[col1] + sumCol[col2] + + sumCol[col3];

    // res
    res.maxSum = max(maxSum3Rows, maxSum3Cols);
    res.max3Rows = maxSum3Rows;
    res.max3Cols = maxSum3Cols;
    res.row1 = row1;
    res.row2 = row2;
    res.row3 = row3;
    res.col1 = col1;
    res.col2 = col2;
    res.col3 = col3;
    return res;
}

long long find_max_2_1(int n){
    long long valueMax;
    long long valueMax1 = -1;
    long long valueMax2 = -1;

    // 2 Rows 1 Col
    for(int j = 0; j < n; j++){
        long long max1 = -1;
        long long max2 = -1;
        for(int i = 0; i < n; i++){
            if(sumRow[i] - costs[i][j] <= max2){
                continue;
            }
            else if(sumRow[i] - costs[i][j] >= max1){
                max2 = max1;
                max1 = sumRow[i] - costs[i][j];
            }
            else if(sumRow[i] - costs[i][j] > max2 && sumRow[i] - costs[i][j] < max1){
                max2 = sumRow[i] - costs[i][j];
            }
        }
        valueMax1 = max(valueMax1, (max1 + max2 + sumCol[j]));
    }
    // 1 Row 2 Cols

    for(int i = 0; i < n; i++){
        long long max1 = -1;
        long long max2 = -1;
        for(int j = 0; j < n; j++){
            if(sumCol[j] - costs[i][j] <= max2){
                continue;
            }
            else if(sumCol[j] - costs[i][j] >= max1){
                max2 = max1;
                max1 = sumCol[j] - costs[i][j];
            }
            else if(sumCol[j] - costs[i][j] > max2 && sumCol[j] - costs[i][j] < max1){
                max2 = sumCol[j] - costs[i][j];
            }
        }
        valueMax2 = max(valueMax2, max1 + max2 + sumRow[i]);
    }   
    valueMax = max(valueMax1, valueMax2);
    return valueMax;
}

int main(){
    int t;
    cin >> t;
    vector<long long> ans;
    while(t--){
        int n, m, q;
        cin >> n >> m >> q;
        a.clear();
        sumRow.clear();
        sumCol.clear();
        adj.clear();
        costs.clear();
        a.resize(m);
        sumRow.resize(n);
        sumCol.resize(n);
        adj.resize(q);
        costs.resize(n);
        for(int i = 0; i < n; i++){
            costs[i].resize(n);
        }
        // Input 1
        for(int i = 0; i < m; i++){
            cin >> a[i].r >> a[i].c >> a[i].w;
            --a[i].r;
            --a[i].c;
            costs[a[i].r][a[i].c] = a[i].w;
            sumRow[a[i].r] += a[i].w;
            sumCol[a[i].c] += a[i].w;
        }
        maxLines max_3_lines = find_max_3lines(n);
        long long max_origin = max(find_max_2_1(n), max_3_lines.maxSum);
        ans.push_back(max_origin);
        // Input 2
        for(int i = 0; i < q; i++){
            cin >> adj[i].index >> adj[i].value;
            --adj[i].index;
        }
        for(int i = 0; i < q; i++){
            int r = a[adj[i].index].r;
            int c = a[adj[i].index].c;
            long long newMax3Rows;
            // Max 3 parallel lines
            if(r == max_3_lines.row1 || r == max_3_lines.row2 || r == max_3_lines.row3){
                newMax3Rows = max_3_lines.max3Rows + adj[i].value;
            }else{
                newMax3Rows = max_3_lines.max3Rows + max(sumRow[r] + adj[i].value, sumRow[max_3_lines.row3]) - sumRow[max_3_lines.row3];
            }
            long long newMax3Cols;
            if(c == max_3_lines.col1 || c == max_3_lines.col2 || c == max_3_lines.col3){
                newMax3Cols = max_3_lines.max3Cols + adj[i].value;
            }else{
                newMax3Cols = max_3_lines.max3Cols + max(sumCol[c] + adj[i].value, sumCol[max_3_lines.col3]) - sumCol[max_3_lines.col3];
            }
            // Max 2 rows 1 col / 2 cols 1 row
            costs[r][c] += adj[i].value;
            sumRow[r] += adj[i].value;
            sumCol[c] += adj[i].value;
            long long maxAdjusts = max(find_max_2_1(n), max(newMax3Rows, newMax3Cols));
            ans.push_back(maxAdjusts);
            costs[r][c] -= adj[i].value;
            sumRow[r] -= adj[i].value;
            sumCol[c] -= adj[i].value;
        }
    }
    for(vector<long long>::size_type i = 0; i < ans.size(); i++){
        cout << ans[i] << endl;
    }
    return 0;  
}

// Time complexity: O(q*n^2)