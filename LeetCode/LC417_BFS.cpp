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

class Solution {
public:

    using pii = pair<int, int>;
    int m, n;
    vector<vector<int>> dir  = {
            {0,1}, {0,-1}, {1,0}, {-1,0}
    };

    void bfs(queue<pii> & q, vector<vector<bool>> & mem , vector<vector<int>>& heights){
        while(!q.empty()){
//            auto & node = q.front();
            auto node = q.front();
            q.pop();
            for(auto & it : dir){
                int _x = node.first + it[0];
                int _y = node.second + it[1];
                if(_x < 0 || _x >= m || _y < 0 || _y >= n) continue;
                if(mem[_x][_y] || heights[_x][_y] < heights[node.first][node.second] ) continue;
                mem[_x][_y] = 1;
                q.push({_x, _y});
            }
        }
    }

    vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights) {

        m = heights.size();
        n = heights[0].size();

        vector<vector<bool>> mem0(m, vector<bool>(n,0));
        vector<vector<bool>> mem1(m, vector<bool>(n,0));

        queue<pii> q1;
        queue<pii> q2;

        for(int i = 0 ; i < m ; i++){
            for(int j = 0; j < n; j++){
                if(i == 0 || j == 0){
                    mem0[i][j] = 1;
                    q1.push({i , j});
                }

                if(i == m - 1 || j == n - 1){
                    mem1[i][j] = 1;
                    q2.push({i , j});
                }
            }
        }

        bfs(q1, mem0, heights);
        bfs(q2, mem1, heights);
        vector<vector<int>> res;
        for(int i = 0 ; i < m ; i++){
            for(int j = 0; j < n; j++){
                if(mem1[i][j] && mem0[i][j]){
                    res.push_back({i,j});
                }
            }
        }

        return res;

    }
};


int main() {

    vector<vector<int>> arr = {{1,2,3,4,5,6,7,8} ,
                               {28,29,30,31,32,33,34,9},
                               {27,48,49,50,51,52,35,10},
                               {26,47,60,61,62,53,36,11},
                               {25,46,59,64,63,54,37,12},
                               {24,45,58,57,56,55,38,13},
                               {23,44,43,42,41,40,39,14},
                               {22,21,20,19,18,17,16,15}};

    vector<vector<int>> out = Solution(). pacificAtlantic(arr);

    for(auto & ite : out){
        for(auto  & it : ite){
            cout << it << " ";
        }
        cout << endl;
    }

    return 0;
}
