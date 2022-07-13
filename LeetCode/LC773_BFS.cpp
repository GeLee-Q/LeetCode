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

    struct node{
        string s1;
        int x, y;
        node(string _s1, int _x, int _y)
                : s1(_s1), x(_x), y(_y){}
    };

    int n = 2, m = 3;
    /*
    s , e 初始状态 和 终止状态，x , y 0的位置;
     */
    string s , e;
    int x , y;

    int slidingPuzzle(vector<vector<int>>& board) {
        s = "";
        e = "123450";
        for(int i = 0; i < n; i++){
            for(int j = 0 ; j < m ;j++){
                s += to_string(board[i][j]);
                if(board[i][j] == 0){
                    x = i;
                    y = j;
                }
            }
        }
        // cout << s << endl;
        int ans = bfs();
        return ans;
    }

    vector<vector<int>> dir = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};
    int bfs(){
        queue<node> q1;
        unordered_map<string,int> mem;
        q1.push({s, x, y});
        mem[s] = 0;

        /*
        map 记录每一个变形的str 和 步数
        处理每一个出q1的node
        得到q1 可以获得的每一种可能
         */
        while(!q1.empty()){
            auto cur_node = q1.front(); q1.pop();
            int step = mem[cur_node.s1];
            if(cur_node.s1 == e) return step;
            for(auto & ite : dir){
                int _x = cur_node.x + ite[0], _y = cur_node.y + ite[1];
                if(_x < 0 || _x >= n || _y < 0 || _y >= m) continue;
                string new_str = update(cur_node.s1, _x, _y, cur_node.x ,cur_node.y);
                if(mem.count(new_str)) continue;
                q1.push({new_str, _x , _y});
                mem[new_str] = step + 1;
            }
        }
        return -1;
    }

    string update(string & s1, int _x ,int _y ,int x , int y){
        string new_str = s1;
         swap(new_str[_x * m + _y], new_str[x * m + y]);
//        char ch = new_str[x * m + y];
//        new_str[x * m + y] = new_str[_x * m + _y];
//        new_str[_x * m + y] = ch;
        return new_str;
    }
};


int main() {

    vector<vector<int>> arr = {{1, 2, 3} ,{4, 0 ,5}};

    int out = Solution().slidingPuzzle(arr);



    cout << out << endl;

    return 0;
}
