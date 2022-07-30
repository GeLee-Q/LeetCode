#include <cstdio>
#include <algorithm>
#include <cstdint>
#include <algorithm>
#include <vector>
#include <queue>
#include <cmath>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <iostream>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <map>
#include <iostream>
#include <queue>
#include <iosfwd>
#include <sstream>
#include <stack>


using namespace std;

/*
        连通块得数量用 并查集
        维护映射关系用 哈希表 两个数被同一个质因数映射

*/


class Solution {
public:
    // 允许四个方向移动的时候 ，基本就不是dp问题了。
    // 不是拓扑图的图论问题，无法使用DP问题求解。
    // 看似DP 实则建图的问题，基本是最小生成树或者最短路问题。
    int row , col;
    const int n = 10009;
    //----
    vector<int> p;
    int find(int x){
        if(p[x] != x){
            p[x] = find(p[x]);
        }
        return p[x];
    }
    // 联通 a 点 b 点
    void _union_(int a, int b){
        p[find(b)] = p[find(a)];
    }
    // 查询这两个点是否联通
    bool query(int a, int b){
        return p[find(a)] == p[find(b)];
    }
    // -----

    int getIdx (int x, int y){
        return x * col + y;
    }

    int minimumEffortPath(vector<vector<int>>& heights) {
        p = vector<int> (n, 0);
        row = heights.size();
        col = heights[0].size();
        for(int i = 0; i < row * col ; i++){ // 初始化并查集
            p[i] = i;
        }

        // 预处理所有的边
        vector<vector<int>> edges; // 得到某一点得到向右和向下的两条边
        for(int i = 0; i < row; i++){
            for(int j = 0 ; j < col; j++){
                int idx = getIdx(i , j);
                if(i + 1 < row){
                    int a = idx , b = getIdx(i + 1, j);
                    int w = abs(heights[i][j] - heights[i+1][j]);
                    edges.push_back({a, b , w});
                }
                if(j + 1 < col){
                    int a = idx , b = getIdx(i , j + 1);
                    int w = abs(heights[i][j] - heights[i][j + 1]);
                    edges.push_back({a, b , w});
                }
            }
        }

        // 按照权值升序排列
        sort(edges.begin(), edges.end(),[&](auto & a, auto & b){
            return a[2] < b[2];
        });

        // 从「小边」开始添加，当某一条边别应用之后，恰好使用得「起点」和「结点」联通
        // 那么代表找到了「最短路径」中的「权重最大的边」
        int start = getIdx(0, 0), end = getIdx(row - 1, col -1);
        for(auto & edge : edges){
            int a = edge[0] , b = edge[1] , w = edge[2];
            _union_(a , b);
            if(query(start, end)){
                return w;
            }
        }
        return 0;
    }
};


int main() {
