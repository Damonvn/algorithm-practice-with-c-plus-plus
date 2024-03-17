/* =============
Exercise - Numbers divisible by 8 and not divisible by 3:

Given a string of characters S consisting of digits from 
0 to 9. Your task is to count the number of substrings of 
S that are divisible by 8 and not divisible by 3.

Input:
The first line contains the number of test cases, T.
T, S satisfy the constraints: 1 ≤ T ≤ 100; 0 ≤ Length(S) ≤ 10^3.

Example:
2
888
5
6564525600
15

============= */

#include <iostream>
#include <string>


using namespace std;

void count_substrings(){
    string s; cin >> s;
    int length = s.length();
    /*
    Applying: The sum of the digits of an integer is divisible 
    by 3, then the number itself is also divisible by 3
    */
    int sum_modulo[length + 1];
    int dp[length + 1][3]; //Applying dynamic programming    
    memset(sum_modulo, 0, sizeof(sum_modulo)); 
    for(int i = 0; i < length + 1; i++){
        dp[i][0] = 0;
        dp[i][1] = 0;
        dp[i][2] = 0;
    }
    int sum = 0;
    dp[0][0] = 1;
    for(int i = 1; i <= length; i++){
        sum += s[i - 1] - '0';
        sum %= 3;
        sum_modulo[i] = sum;
        dp[i][sum] += 1;
        dp[i][0] += dp[i-1][0];
        dp[i][1] += dp[i-1][1];
        dp[i][2] += dp[i-1][2];
    }
    int ans = 0;
    for(int i = 1; i <= length; i++){
        int number = s[i-1] - '0';
        if(number == 8) ++ans;
        if(i >= 2){
            int tmp = (s[i-2] - '0')*10 + s[i-1] - '0';
            if(tmp % 8 == 0 && tmp % 3 != 0){
                ans++;
            }
        }
        if(i >= 3){
            int tmp = (s[i-3] - '0')*100 + (s[i-2] - '0')*10 + s[i-1] - '0';
            if(tmp % 8 == 0){
                ans += i - 2;
                ans -= dp[i - 3][sum_modulo[i]];
            }
        }
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