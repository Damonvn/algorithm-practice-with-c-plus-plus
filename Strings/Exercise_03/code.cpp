/* =============
Exercise - Sum String:
Given a string S consisting of digits, S is called a Sum String if there exists 
a natural number k > 2 such that we can partition the string S into k different 
substrings (S1, S2, ...Sk) such that each substring satisfies the condition 
Si = Si-1 + Si-2 (i = 3, 4, ..., k). For example, the string S = "123415538" 
is a Sum String because there exists a number k = 3 such that when we partition 
the string S into 3 substrings ("123", "415", "538"), it satisfies the condition 
123 + 415 = 538. Similarly, the string S = "12345" is not a Sum String.

Your task is to determine whether the given string S is a Sum String or not.

Input:
The first line contains the number of tests, T.
The following lines contain the tests. Each test is a string of digits, S.
Constraints: 1 ≤ T ≤ 100, 3 ≤ length(S) ≤ 105.

Output:
Output the result of each test on a new line.

Example
6
12
No
123
Yes
12345
No
12358
Yes
123456579
Yes
1122335588143

============== */

#include <iostream>

using namespace std;

string sum(string a, string b){
    if(a.length() < b.length()) swap(a, b);
    int n = a.length(), m = b.length();
    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());
    b += string(n - m, '0');
    string res = "";
    int carry = 0;
    for(int i = 0; i < n; i++){
        int tmp = (a[i] - '0') + (b[i] - '0') + carry;
        res += (char)(tmp % 10 + '0');
        carry = tmp/10;
    }
    if(carry) res += (char)(carry + '0');
    reverse(res.begin(), res.end());
    return res;
}

bool check(string s, int left, int l1, int l2){
    string s1 = s.substr(left, l1);
    string s2 = s.substr(left + l1, l2);
    string s3 = sum(s1, s2);
    if(s3.length() > (s.length() - l1 - l2 - left)) return false;
    string damon = s.substr(left + l1 + l2, s3.length());
    if(s3 == s.substr(left + l1 + l2, s3.length())){
        if(s.length() == left + l1 + l2 + s3.length()) return true;
        return check(s, left + l1, l2, s3.length());
    }
    return false;
}

void solve(){
    string s;
    cin >> s;
    for(int i = 1; i <= s.length()/2; i++){
        for(int j = 1; j <= 2*s.length()/3 + 5 - i; j++){
            if(j > s.length()/2){
                break;
            }
            if(check(s, 0, i, j)){
                cout << "Yes" << endl;
                return;
            }
        }
    }
    cout << "No" << endl;
}
int main(){
    int t;
    cin >> t;
    while(t--){
        solve();
    }
    return 0;
}

/* ========
The algorithm's complexity is significantly reduced by limiting 
the value of i (i ≤ s.length()/2) and limiting the value of j
(j ≤ s.length()/2 && j ≤ 2*s.length()/3 + 5 - i).

======== */