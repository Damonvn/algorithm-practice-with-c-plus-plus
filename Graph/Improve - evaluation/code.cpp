/* =============

Exercise - Improve and evaluation:

In the country Beta, there are N cities numbered from 1 to N. The cities are connected 
by M two-way roads, numbered from 1 to M. Between any two cities, there is at most one 
direct road connecting them. The two-way road number i (1 ≤ i ≤ M) connects the distinct 
cities Ui and Vi with a length of Wi. A route consisting of K cities from city X to city 
Y is a sequence of cities P1, P2, ..., Pk, such that P1 = X, Pk = Y, and there is a direct 
road between any two consecutive cities Pi and Pi+1 (∀𝑖=1,2,…,K-1). In the country Beta, 
every city has a route to another city. The cost of traveling along a route from X to city 
Y is the sum of the lengths of the roads on that route. Let D(X, Y) be the minimum cost 
among the costs of traveling along routes from city X to city Y. It is agreed that 
D(X, X) = 0 for every city X.

City 1 has a mold casting plant, and city 2 has an electrostatic coating plant. A company 
wants to choose a city to open a decorative steel manufacturing center using materials from 
the mold casting plant and the electrostatic coating plant. City Y is considered better than 
or equivalent to city X when and only when D(Y, 1) ≤ D(X, 1) and D(Y, 2) ≤ D(X, 2). Note that 
city X is considered better than or equivalent to itself. The company calculates the rank of 
city X as the number of cities Y that are better than or equivalent to city X. Specifically, 
the formula for calculating the rank is: 

R(X) = ∣Y∈{1,2,…,N} : D(Y,1)≤D(X,1) and D(Y,2)≤D(X,2)∣.

Furthermore, the company also commits to the local government that before establishing a steel 
manufacturing center in any city X, they will renovate a road connecting to city X. The company 
has surveyed and proposed P plans. For the j-th plan (1 ≤ j ≤ P), the road Tj connecting city 
U(Tj) and city V(Tj) will be chosen for renovation to reduce its length from the initial length 
W(Tj) to a new length W(Tj'). For each plan, after renovating the road, the company needs to 
calculate the rank of city U(Tj) and city V(Tj). The plans are independent, meaning that each 
plan applies only to the initial state of the M roads.

Requirement: For each j-th plan (1 ≤ j ≤ P), help the company determine the rankings of city 
U(Tj) and city V(Tj) after renovating road Tj.

Input:

- The first line contains three integers N, M, and P, representing the number of cities, the 
number of roads, and the number of renovation plans, respectively. 
Constraints: 2 ≤ N ≤ 10^5; 1 ≤ M, P ≤ 10^3.

- The next M lines each contain three integers Ui, Vi, Wi, representing two cities connected 
by the i-th road and the length of that road, respectively. 
Constraints: 1 ≤ Ui, Vi ≤ N; 1 ≤ Wi ≤ 10^9.

- The next P lines each contain two integers Tj and W(Tj'), representing the index of the 
road selected for renovation in the j-th plan and the length after renovation. 
Constraints: 1 ≤ Tj ≤ M; 1 ≤ W(Tj') < W(Tj).

Output:

Consisting of P lines, where the j-th line contains two integers representing the ranks 
of U(Tj) and V(Tj) respectively, corresponding to the ranks of cities U(Tj) and V(Tj) 
if the j-th plan is implemented.

Sample Input 1
5 6 2
1 5 8
5 2 10
1 3 6
3 2 12
3 4 3
4 2 11
5 2
6 9

Sample Output 1
1 2
1 1

============= */

#include <cstdio>
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const long long INF =  1e14;
vector<long long> min_paths_1;
vector<long long> min_paths_2;
vector<pair<int, long long>> adj[100001];
struct edge {
    int x, y, w;
};
vector<edge> edges;
struct adjust {
    int index, new_w;
};
vector<adjust> adjusts;
void input(int n, int m, int p){
    for(int i = 1; i <= n; i++){
        adj[i].clear();
    }
    edges.clear();
    edges.resize(m+1);
    for(int i = 1; i <= m; i++){
        int x, y, w; cin >> x >> y >> w;
        adj[x].push_back({y, w});
        adj[y].push_back({x, w});
        edges[i].x = x;
        edges[i].y = y;
        edges[i].w = w;
    }
    adjusts.clear();
    adjusts.resize(p+1);
    for(int i = 1; i <= p; i++){
        cin >> adjusts[i].index >> adjusts[i].new_w;
    }
}

void dijkstra(int s, vector<long long> &min_paths, int x, int y, int new_w){
    min_paths[s] = 0;
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> Q;
    Q.push({0, s});
    while(!Q.empty()){
        pair<long, long> top = Q.top(); Q.pop();
        int u = top.second;
        long long length = top.first;
        if(length > min_paths[u]){
            continue;
        };
        for(auto it : adj[u]){
            int v = it.first;
            int w;
            if((u == x && v == y) || (u == y && v == x)){
                w = new_w;
            }
            else{
                w = it.second;
            }
            if(min_paths[v] > min_paths[u] + w){
                min_paths[v] = min_paths[u] + w;
                Q.push({min_paths[v], v});
            }
        }
    }
}

int main(){
    // freopen("IMPEVAL.inp", "r", stdin);
    // freopen("IMPEVAL.out", "w", stdout);
    // ios_base::sync_with_stdio(false);
    // cin.tie(NULL);
    int n, m, p;
    cin >> n >> m >> p;
    input(n, m, p);
    for(int i = 1; i <= p; i++){
        // Adjust
        int id = adjusts[i].index;
        int row = edges[id].x;
        int col = edges[id].y;
        min_paths_1.clear();
        min_paths_1.resize(n + 1, INF);
        min_paths_2.clear();
        min_paths_2.resize(n + 1, INF);
        //Resolve
        dijkstra(1, min_paths_1, row, col, adjusts[i].new_w);
        dijkstra(2, min_paths_2, row, col, adjusts[i].new_w);
        int rank1 = 0;
        int rank2 = 0;
        for(int i = 1; i <= n; i++){
            if((min_paths_1[i] <= min_paths_1[row]) && (min_paths_2[i] <= min_paths_2[row])){
                ++rank1;
            }
            if((min_paths_1[i] <= min_paths_1[col]) && (min_paths_2[i] <= min_paths_2[col])){
                ++rank2;
            }
        }
        cout << rank1 << " " << rank2 << endl;
    }
    return 0;
}

// Time complexity: P*(N + M)logN