/* =============

Exercise - Purchasing agricultural products:

The Delta nation boasts a leading agricultural sector worldwide. This year, thanks to 
widespread application of information technology in agricultural production, farmers 
in the Delta nation have enjoyed a bountiful harvest. To celebrate the significant 
success of our people and to boost exports, the government has decided to allocate 
vehicles for purchasing agricultural products from all corners of the country.

Within the nation, there are N villages numbered from 1 to N. The transportation network 
consists of N - 1 two-way roads, each directly connecting two villages. These roads ensure 
nationwide connectivity. In other words, from any village, one can reach all other villages 
through one or more roads. The people in the Delta nation are capable of producing K different 
types of agricultural products, numbered from 1 to K. This year, the villagers in the i-th 
village (1 ≤ i ≤ K) produce Ai-th type of agricultural product.

The government of the Delta nation will allocate N*(N-1)/2 trucks for purchasing agricultural 
products. Specifically, for each pair of integers (u, v) where (1 ≤ u, v ≤ N), each truck 
will purchase agricultural products along a road from village u to village v, meaning it will 
purchase from village u, travel through one or more roads, and end the purchase at village v 
(trucks always choose the route with the fewest possible roads). It is known that when arriving 
at any village (including both villages u and v), the truck will purchase 1 ton of agricultural 
products produced in that village. Thanks to the abundant harvest, all villages have enough 
products for all trucks passing through. Note that trucks do not purchase along the same route; 
if one truck has already started purchasing at u and stopped at v, then no other truck will 
start purchasing at u and stop at v, or start purchasing at v and stop at u.


Transporting agricultural products always incurs costs. Depending on the characteristics, the 
transportation costs for each type of agricultural product may vary. According to the government's 
calculations, if over the entire journey, a truck purchases a total weight of agricultural products 
for types 1, 2, ..., K, corresponding to W1, W2, ...Wk tons, the transportation cost of the truck 
is calculated as C1 * W1^2 + C1 * W2^2 + ... + Ck*Wk^2, where C1, C2, ..., Ck are the transportation 
coefficients for the K types of agricultural products 1, 2, ..., k. The government will sponsor all 
transportation costs, so it is necessary to know the total cost of all N(N-1)/2 trucks.

Additionally, with the belief that the agricultural sector will continue to thrive in the coming years, 
the government wishes to budget for the transportation costs of agricultural products for the following 
years. According to the cultivation plan for the next Q years, in the jth year ((1 ≤ j ≤ Q)), village 
Tj will switch to producing agricultural product type Bj, while the remaining N - 1 villages will continue 
cultivating the same type of agricultural product as in the j - 1 year (this year considered as year 0).
For each year, the government wants to know the total transportation cost of agricultural products if 
they continue to allocate trucks for purchasing as in the above plan.

Requirement: Write a program to calculate the total transportation cost of agricultural products for 
the government for this year and for the next Q years, based on the cultivation plan changes.

Input:
- The first line contains three integers N, K, and Q, representing respectively the number of villages 
in the Delta nation, the number of types of agricultural products produced here, and the number of 
years in the cultivation plan. Constraints: 1 ≤ K ≤ 20; 2 ≤ N, Q ≤ 100; 1 ≤ Q ≤ 100.

- The second line contains N integers A1, A2, ..., An, indicating the specialized type of agricultural 
product produced in each village this year. Constraints: 1 ≤ Ai ≤ K; ∀𝑖 = 1,2, … ,N.

- The third line contains K integers C1, C2, ..., Ck, representing the transportation cost coefficients 
of the agricultural product types. Constraints: 1 ≤ Ci ≤ 10^9; ∀𝑖 = 1,2, … ,K.

- Each line among the next N - 1 lines contains two integers x and y, indicating that there is a two-way 
road connecting village x and village y.

- The j-th line among the last Q lines contains two integers Tj and Bj, indicating that in the jth year 
out of the Q following years, village Tj will switch to producing agricultural product type Bj. 
Constraints: 1 ≤ Tj ≤ N; 1 ≤ Bj ≤ K;

Output: 
- The first line contains an integer, which is the remainder of the total transportation cost of 
agricultural products for this year divided by 998244353.

- The j-th line among the remaining Q lines contains an integer, which is the remainder of the 
total transportation cost of agricultural products for the jth year divided by 998244353.

Sample Input
5 3 2
1 1 1 2 3
2 3 5
1 2
2 3
2 4
1 5
2 3
3 2

Sample Output:
120
137
139


Notes
The purchasing routes of the N(N-1)/2 trucks:
1→2
1→2→3
1→2→4
1→5
2→3
2→4
2→1→5
3→2→4
3→2→1→5
4→2→1→5

============= */

#include <cstdio>
#include <iostream>
#include <vector>
#include <stack>

using namespace std;

struct road {
    int u, v;
};
struct dfsPoint {
    int index;
    int preIndex;
};
struct plan {
    int index, type;
};
vector<vector<int>> trucks;
long long truck_index = 0;
vector<vector<long long>> village_routes;
vector<plan> plans;
stack<dfsPoint> st;
stack<int> route;
vector<vector<int>> adj;
vector<vector<int>> villages_pre;
vector<int> types;
vector<int> costs;
long long ans;

void dfs(int first_vil, int k, dfsPoint x){
    st.push(x);
    villages_pre[first_vil][x.index] = x.preIndex;
    int size = adj[x.index].size();
    for(int i = 0; i < size; i++){
        if(adj[x.index][i] != x.preIndex){
            dfsPoint nextDfs;
            nextDfs.index = adj[x.index][i];
            nextDfs.preIndex = x.index;
            dfs(first_vil, k, nextDfs);
        };
    }
    if(!st.empty()){
        dfsPoint top = st.top(); st.pop();
        if(top.index > first_vil){       
            while(top.index != first_vil){
                route.push(top.index);
                ++trucks[truck_index][types[top.index]];
                top.index = top.preIndex;
                top.preIndex = villages_pre[first_vil][top.index];
                if(top.index == first_vil){
                    route.push(top.index);
                    ++trucks[truck_index][types[top.index]];
                }
            }
            for(int i = 0; i < k; i++){
                ans += costs[i] * trucks[truck_index][i] * trucks[truck_index][i];
                ans %= 998244353;
            }
            while(!route.empty()){
                int top_vil = route.top(); route.pop();
                village_routes[top_vil].push_back(truck_index);
            }
            ++truck_index;   
        }    
    }
}

int main(){
    int n, k, q; cin >> n >> k >> q;
    // All routes pass one village
    village_routes.resize(n);

    // The agricultural products that a truck purchases
    long long number_of_trucks = n*(n-1)/2;
    trucks.clear();
    trucks.resize(number_of_trucks);
    for(int i = 0; i < number_of_trucks; i++){
        trucks[i].resize(k, 0);
    }
    // type of crops of villages ;
    types.resize(n);
    for(int i = 0; i < n; i++){
        cin >> types[i];
        --types[i];
    } 
    // shipping cost coefficient of crops.
    costs.clear();
    costs.resize(k);
    for(int i = 0; i < k; i++){
        cin >> costs[i];
    }
    // tracking the route
    villages_pre.clear();
    villages_pre.resize(n-1);
    for(int i = 0; i <= n-2; i++){
        villages_pre[i].resize(n);
    }
    // input
    vector<road> roads(n-1);
    adj.resize(n);
    for(int i = 0; i < n - 1; i++){
        cin >> roads[i].u >> roads[i].v;
        --roads[i].u;
        --roads[i].v;
        adj[roads[i].u].push_back(roads[i].v);
        adj[roads[i].v].push_back(roads[i].u);
    }
    plans.resize(q);
    for(int i = 0; i < q; i++){
        cin >> plans[i].index >> plans[i].type;
        --plans[i].index;
        --plans[i].type;
    }
    // Solve
    for(int i = 0; i <= n-2; i++){
        dfsPoint start;
        start.index = i;
        start.preIndex = -1;
        dfs(i, k, start);
    }
    // origin ans
    cout << ans << endl;
    for(int i = 0; i < q; i++){
        int vil_index =plans[i].index;
        int old_type = types[plans[i].index];
        int new_type = plans[i].type;
        long long size = village_routes[vil_index].size();
        for(long long tr = 0; tr < size; tr++){
            long long truck_tr = village_routes[vil_index][tr];        
            ans -= costs[old_type] * (1 + 2 * (trucks[truck_tr][old_type] - 1));
            ans += costs[new_type] * (1 + 2 * trucks[truck_tr][new_type]);
            ans %= 998244353;
            --trucks[tr][old_type];
            ++trucks[tr][new_type];
            types[vil_index] = new_type;
        }
        // ans after changing the type of crops of the village
        cout << ans << endl;
    }
    return 0;
}

// Time complexity max: n^3 + q*n^2