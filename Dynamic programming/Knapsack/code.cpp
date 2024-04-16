/* =============
Exercise - Knapsack problem
You are a thief planing to rob a jewelry store. In front of you, there are n 
items of jewelry, each with a weight w, a value v and a quantity q. 
However, your knapsack has a limited capacity, meaning it can only hold items 
up to a certain total weight k(w). Your goal is to maximize the total value 
of the items you can carry without exceeding this maximum.

n, w, q satisfy the constraints: n ≤ 1000, w ≤ 1000, q ≤ 1000

Input:
- Number of items: n 
- Knapsack limited capacity: w
- Item detail: weight value quantity

Example 1
4 10
4 8 2
8 22 1
3 7 3
2 9 2
Ans: 32
Selected items: 
dfs: 1 | Item_Index 3: 1
dfs: 2 | Item_Index 3: 1
dfs: 3 | Item_Index 2: 2

Example 2
5 20
4 7 6
1 2 10
6 9 2
10 11 4
5 2 3
Ans: 37
Selected items: 
dfs: 1 | Item_Index 1: 3
dfs: 2 | Item_Index 1: 4
dfs: 3 | Item_Index 1: 1
dfs: 4 | Item_Index 0: 2
dfs: 5 | Item_Index 0: 1

============= */

#include <algorithm>
#include <iostream>
#include <numeric>
#include <math.h>
#include <string.h>
#include <vector>

using namespace std;

int n, w;
int wi[1000];
int vi[1000];
int qi[1000];
int fw[10001][1001]; 

struct item_struct {
    int item_index;
    int weight;
    int value;
};
vector<item_struct> items_vector;

int f[10];
void input(){
    for(int i = 0; i < n; i++){
        cin >> wi[i];
        cin >> vi[i];
        cin >> qi[i];
    }
    for(int j = 0; j < 11; j++){
        if(j == 0) f[j] = 1;
        else f[j] = f[j-1]*2;
    }
}

void new_ni(int i, int j, int c){
    for(int h = 0; h <= j; h++ ){
        item_struct new_item;
        new_item.item_index = i;
        new_item.weight = f[h]*wi[i];
        new_item.value = f[h]*vi[i];
        items_vector.push_back(new_item);
    }
    if(c != 0){
        item_struct new_item;
        new_item.item_index = i;
        new_item.weight = c*wi[i];
        new_item.value = c*vi[i];
        items_vector.push_back(new_item);
    }
}

void create_new_ni(){
    for(int i = 0; i < n; i++){
        int j = 0;
        int max_j = 0;
        int c  = 0;
        while(j < 9){
            if( qi[i] == f[j+1] - 1){
                max_j = j;
                c = 0;
                j = 9;
            }
            else {
                if(qi[i] < f[j+2] - 1){
                    max_j = j;
                    c = (qi[i] - f[j+1] + 1);
                    j = 9;
                }
                else{
                    j++;
                } 
            }
        }
        new_ni(i, max_j, c);
    }
}

void dfs_selected_item(int row, int col, int dfs_index){ 
    // cout << "fw_end " << fw[row][] << endl;
    if(fw[row][col] > fw[row-1][col]){
        cout << "dfs: " << dfs_index <<  " | Item_Index " << items_vector[row - 1].item_index << ": "<< items_vector[row - 1].weight/wi[items_vector[row - 1].item_index] << endl;
        dfs_selected_item(row - 1, col - items_vector[row - 1].weight, dfs_index + 1);
    }
    else if(fw[row][col] == fw[row-1][col]){
        if(fw[row][col] == items_vector[row-1].weight + fw[row][col - items_vector[row-1].weight]){
            cout << "dfs: " << dfs_index <<  " | Item_Index: " << items_vector[row - 1].item_index << items_vector[row - 1].weight/wi[items_vector[row - 1].item_index];
            dfs_selected_item(row - 1, col - items_vector[row - 1].weight, dfs_index + 1);
            dfs_selected_item(row - 1, col, dfs_index);
        }else{
            dfs_selected_item(row - 1, col, dfs_index);
        }
    }
}


int main (){
    cin >> n >> w;
    input();
    create_new_ni();     
    for(int i = 0; i <= items_vector.size(); i++){
        for(int j = 0; j <= w; j++){
            fw[i][j] = 0;
        }
    }
    for(int i = 1; i <= items_vector.size(); i++){
        for(int j = 1; j < w + 1; j++){
            if(items_vector[i - 1].weight <= j){
                fw[i][j] = max(fw[i-1][j], items_vector[i - 1].value + fw[i-1][j- items_vector[i - 1].weight]);
            }else{
                fw[i][j] = fw[i-1][j];
            }
        }
    }
    cout << "Ans: " << fw[items_vector.size()][w] << endl;
    cout << "Selected items: " << endl;
    dfs_selected_item(items_vector.size(), w, 1);
    return 0;
}

// Time complexity: O(w * n * log(q)) <= 10^7