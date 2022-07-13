//
// Created by 86503 on 2022/3/21.
//

#include <string>
#include <algorithm>
#include <unordered_map>
#include <iostream>
#include <vector>

using namespace std;

//字符串的子串为连续的：

signed main(){
    int n = 5;
    vector<vector<int>> copy_tmp;
    vector<vector<int>> tmp(n,vector<int>(n,-1));

    copy_tmp = vector<vector<int>> (n,vector<int>(n,2));;


    for(int i = 0 ; i < n; i++){
        for(int j = 0; j < n; j++) {
            tmp[i][j] = 0;
            cout << tmp[i][j] << " " ;
        }
        cout << endl;
    }

    cout << endl;

    for(int i = 0 ; i < n; i++){
        for(int j = 0; j < n; j++) {
            cout << copy_tmp[i][j] << " " ;
        }
        cout << endl;
    }

    cout << &(tmp) << endl;
    cout << &(copy_tmp) << endl;
}