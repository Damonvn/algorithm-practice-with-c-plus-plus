/* =============
Exercise - Sieve of Eratosthenes:

Given a continuous sequence of integers from a to b, 
where 0 ≤ a, b ≤ 10^12 and and b-a ≤ 10^6.  Your task is 
counting the prime numbers in the range from a to b

============= */

#include <iostream>

using namespace std;

typedef long long ll;

ll max(ll a, ll b){
    if(a > b) return a;
    return b;
}

void sieve(ll left, ll right){
    // Applying Sieve of Eratosthenes
    int prime[right-left+1];
    for(int i = 0; i <= right-left; i++){
        prime[i] = 1;
    }
    for(ll i = 2; i <= sqrt(right); i++){
        for(ll j = max(i*i, (left+i-1)/i*i); j <= right; j+=i ){
            prime[j-left] = 0;
        }
    }
    int ans = 0;
    for(ll i = max(left, 2); i <= right; i++){
        if(prime[i-left]){
            ++ans;
        }
    }
    cout << ans << endl;
}


int main(){
    int t;
    cin >> t;
    while(t--){
        ll l, r;
        cin >> l >> r;
        sieve(l, r);
    }
    return 0;
}