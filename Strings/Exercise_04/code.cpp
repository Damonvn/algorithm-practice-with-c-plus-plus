/* =============
Exercise - Modular Exponentiation:
Given positive integers a, b, M, where a is a very large number represented as a string of digits.
Find K = (a^b) % M. For example, if a = 3, b = 2, M = 4, then K = (3^2) % 4 = 1.


Input:
The first line contains the number of tests T.
Constraints: 1 ≤ T ≤ 100; 0 ≤ length(a) ≤ 1000; 2 ≤ b, M ≤ 10^12.

Example
Input:
4234626 100 10
Output:
6

Input:
2 6 5
Ouput:
4

============= */

#include <iostream>
#include <string>
// #include <sstream>

using namespace std;

typedef long long ll;

ll modulo(string a, ll m){
    ll res = 0;
    for(char x : a){  
        res = res*10 + x - '0';
        res %= m;
    }
    return res;
}
/*
- Applying the modular addition theorem : (a1 + a2) % m = (a1 % m + a2) % m  
- Applying decomposing an integer into its digits and multiplying by the base,
  example: 123 = ((0*10+1)*10 + 2)*10 + 3
*/

ll modular_binary_exponentiation(ll a, ll b, ll m){
    ll res = 1;
    while(b){
        if(b%2 == 1){
            res *= a;
            res %= m;
        }
        a *= a; // a^2 a^3... a^logb
        a %= m;
        b /= 2;
    }
    return res;
}

/*
- Applying binary exponentiation: 
  ll n = logb
  b = (0/1)*2^0 + (0/1)*2^1 + .... + (0/1)2^n
  a^b = a^((0/1)*2^0 + (0/1)*2^1 + .... + (0/1)2^n)
- Applying the modular addition theorem
*/ 

int main(){
    int t; cin >> t;
    while(t--){
        string a;
        ll b, m; cin >> a >> b >> m;
        ll res = modulo(a, m);
        cout << modular_binary_exponentiation(res, b, m) << endl;
    }
    return 0;
}
