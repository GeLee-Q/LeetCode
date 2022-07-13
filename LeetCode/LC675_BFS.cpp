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




/*数位DP模板
 * */

class Solution {
public:
    int m, n;

    int next = 0;
    vector<int> tree_val;

    vector<vector<int>> mem_origin;
    vector<vector<int>> dir = {{0,1}, {0,-1}, {1,0},{-1,0}};

    int step = 0;

    void dfs(vector<vector<int>> & forest,
             vector<vector<int>>  & mem,
             int & x, int & y,  int & pre, int & cnt_step){

        // 首先判断是否越界
        if(x < 0 || x >= m || y < 0 || y >= n) return ;

        //判断是否可以遍历 1. forset为0 不可遍历，mem为0 不可遍历
        if(mem[x][y] == 0 || forest[x][y] == 0 ) return;

        //处理当前节点, 步长++, 更新mem
//        cnt_step++;
        mem[x][y] = 0;

        //判断此节点的树是否可以砍
        if(forest[x][y] == tree_val[next]) {
            next++;
            pre = forest[x][y];
            step += cnt_step;
            cnt_step = 0;
            // 判断是否砍完了
            if(pre == tree_val.back()) return;
            mem = mem_origin;
            mem[x][y] = 0;
        }


        for(auto & ite : dir){
            int _x = x + ite[0], _y = y + ite[1];
            if(_x < 0 || _x >= m || _y < 0 || _y >= n) continue;
            if(mem[_x][_y] == 0 || forest[_x][_y] == 0 ) continue;
            cnt_step++;
            dfs(forest, mem, _x, _y , pre, cnt_step);
            cnt_step--;
        }
    }

    int cutOffTree(vector<vector<int>>& forest) {
        m = forest.size();
        n = forest[0].size();

        // 对于每一个砍树后的节点，都需要一个全新的记忆矩阵。 0 表示 不能走 或者 走过 ， 1 未走过。
        mem_origin = vector<vector<int>> (m , vector<int> (n , 0));
        for(int i = 0 ; i < m ; ++i){
            for(int j = 0 ; j < n; ++j){
                if(forest[i][j] != 0){
                    if(forest[i][j] != 1) tree_val.push_back(forest[i][j]);

                    mem_origin[i][j] = 1;
                }

            }
        }
        sort(tree_val.begin(), tree_val.end());

        int cnt_step = 0;
        int pre = 0;// 第一个砍的树的值
        vector<vector<int>> mem = mem_origin;
        int x =0, y = 0;
        dfs(forest , mem, x, y, pre, cnt_step);

        return pre == tree_val.back() ? step : -1;
    }
};


int main() {

    vector<vector<int>>  nums = {{1,2,3},{0,0,0},{0,0,0}};
    vector<vector<int>>  nums_0 = {{2,3,4},{0,0,5},{8,7,6}};
    vector<vector<int>>  nums_1 = {{54581641,64080174,24346381,69107959},
                                   {86374198,61363882,68783324,79706116},
                                   {668150,92178815,89819108,94701471},
                                   {83920491,22724204,46281641,47531096},
                                   {89078499,18904913,25462145,60813308}};
    int ret = Solution().cutOffTree(nums_0);
    cout << ret << endl;

    return 0;
}

