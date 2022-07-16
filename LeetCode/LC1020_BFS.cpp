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
    int m , n;
    vector<vector<int>> mem;
    vector<vector<int>> ans;
    vector<vector<int>> dirs = {{1,0}, {-1,0}, {0,1}, {0,-1}};
    int numEnclaves(vector<vector<int>>& grid) {
        m = grid.size();
        n = grid[0].size();
        mem = vector<vector<int>>(m, vector<int>(n, 0));
        ans = vector<vector<int>>(m, vector<int>(n, 0));

        queue<pii> q;
        for(int i = 0; i < m; i++){
            for(int j = 0; j < n; j++){
                if(i == 0 || j == 0 || i == m-1 || j == n -1){
                    ans[i][j] = 1;
                    mem[i][j] = 1;
                    q.push({i , j});
                }
            }
        }

        cout << "------" << endl;
        int res = 0;
        while(!q.empty()){
            auto node = q.front(); q.pop();
            int x = node.first, y = node.second;
            for(auto & dir : dirs){
                int _x = x + dir[0], _y = y + dir[1];
                if(_x < 0 || _x >=m || _y < 0 || _y >= n) continue;
                if(mem[_x][_y] == 1) continue;
                mem[_x][_y] = 1;
                if(grid[_x][_y] == 1){
                    ans[_x][_y] = 1;
                    q.push({_x, _y});
                }
            }
        }

        for(auto &ite : ans){
            for(auto & it : ite){
                if(it == 1) res++;
            }
        }
        return res;
    }
};


int main() {

//    vector<vector<int>> arr = {{1,2,3,4,5,6,7,8} ,
//                               {28,29,30,31,32,33,34,9},
//                               {27,48,49,50,51,52,35,10},
//                               {26,47,60,61,62,53,36,11},
//                               {25,46,59,64,63,54,37,12},
//                               {24,45,58,57,56,55,38,13},
//                               {23,44,43,42,41,40,39,14},
//                               {22,21,20,19,18,17,16,15}};
    vector<vector<int>> arr = {{0,0,0,0} ,
                               {1,0,1,0},
                               {0,1,1,0},
                               {0,0,0,0}};

    int out = Solution(). numEnclaves(arr);

    cout << out << endl;
//    for(auto & ite : out){
//        for(auto  & it : ite){
//            cout << it << " ";
//        }
//        cout << endl;
//    }

    return 0;
}
