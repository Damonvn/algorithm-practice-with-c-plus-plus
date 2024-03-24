/* =============
Exercise 01:
Calculate the combination of n choose k modulo 1000000007, where 0 <= n, k <= 1000;

Calculate the combination of n choose k modulo 1000000007, where 0 <= n, k <= 1000000;

============= */

#include <iostream>
using namespace std;

typedef long long ll;
const int MOD = 1000000007;

//==== Solve exercise 01 ====//

int32_t C[1000][1000]; //C[i][j] : combination of i choose j
void init(){
    for(int i = 0; i <= 1000; i++){
        for(int j = 0; j <= i; j++){
            if(j == 0 || j == i){
                C[i][j] = 1;
            }
            else{
                C[i][j] = C[i-1][j] + C[i-1][j-1];
                C[i][j] %= MOD;
            }
        }
    }
}

void solve1(){
    init();
    int t; cin >> t;
    while(t--){
        cout << "Enter n, k: ";
        int n, k; cin >> n >> k; // 0 <= n, k <= 1000 && k <= n;
        if(n < 0 || k < 0 || n > 1000 || k > 1000 || k > n){
            cout << "n, k n, k need to satisfy the constraint: 0 <= n, k <= 1000, n < k" << endl;
        }
        else{
            cout << C[n][k] << endl;
        }
    }

}


//==== Solve exercise 02 ====//

ll powMod(ll a, ll b, ll m){
    ll res = 1;
    a %= m;
    while(b){
        if(b %2 == 1){
            res *= a;
            res %= m;
        }
        a *= a;
        a %= m;
        b = b/2;
    }
    return res;
}

void solve2(){
    ll f[1000001];
    f[0] = 1;
    for(int i = 1; i <= 1000000; i++){
        f[i] = i * f[i-1];
        f[i] = f[i]%MOD;
    }
    cout << endl;

    int t; cin >> t;
    while(t--){
        ll n, k; cin >> n >> k;
        if(n < 0 || k < 0 || n > 1000000 || k > 1000000 || k > n){
            cout << "n, k n, k need to satisfy the constraint: 0 <= n, k <= 1000000, n < k" << endl;
        }
        else{
            ll de = (f[n-k]*f[k])%MOD;  cout << "de: " << de << endl;
            ll re = powMod(de, MOD - 2, MOD);  cout << "re: " << re << endl;
            cout << (f[n]*re)%MOD << endl;
        }
    }
}

int main(){
    // solve1();
    solve2();  
    return 0;
}