/* =============
Exercise - counting the number of substrings divisible by 3, 6 , 7, 9:

Given a string S consisting of digits only. Your task is to count the 
substrings of S that are divisible by N, where N = 3 || 6 || 7 || 9 || 30 
|| 60 || 70 || 90 || 300 || 600 || 700 || 900.

Input:
The first line contains the number of test cases, T.
The next line contain the test cases. Each test case consists of 
two parts: the string S and the number N
Constraints: 1 ≤ T, Length(S) ≤ 100.

Example 

5

787878 7
5

7778 7
6

667 6
3

123 3
3

97899 9
4

============= */

#include <iostream>
#include <string>

using namespace std;

typedef long long ll;

int num(char c){
    return c - '0';
}

void count_substrings(){
    string s; cin >> s;
    int n; cin >> n;
    int length = s.length();
  
    int ten_exp_modulo[length];
    ten_exp_modulo[0] = 1;
    for(int i = 1; i < length; i++){
        ten_exp_modulo[i] = (ten_exp_modulo[i-1]*10)%n;
    }
    int dp[length + 1][n];
    for(int i = 0; i < length + 1; i++){
        for(int j = 0; j < n; j++){
            dp[i][j] = 0;
        }
    }
    int sum_num_modulo[length];
    int ans = 0;
    int sum = 0;
    for(int i = 1; i <= length; i++){
        sum = (sum*10 + num(s[i-1]))%n;
        if(sum == 0){
            ++ans;
        };
        sum_num_modulo[i] = (sum * ten_exp_modulo[length-i])%n;
        ans += dp[i-1][sum_num_modulo[i]];  
        for(int j = 0; j < n; j++){
            dp[i][j] += dp[i-1][j];
        }
        ++dp[i][sum_num_modulo[i]];
    }
    cout << ans << endl;
}

int main(){
    int t; cin >> t;
    while(t--){
        count_substrings();
    }  
    return 0;
}