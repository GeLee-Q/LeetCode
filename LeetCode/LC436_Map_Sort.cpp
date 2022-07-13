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
    vector<int> findRightInterval(vector<vector<int>>& nums) {
        // 用map来记录每一个的位置,由于每一个起始位置都不一样，所以不用担心重复
        const int n = nums.size();
        unordered_map<int, int> m1;
        int _fend = 0;
        for(int i = 0; i < n ; ++i){
            _fend = max(_fend, nums[i][1]);
            m1[nums[i][0]] = i;
        }

        // 对intervals 进行排序
        sort(nums.begin(), nums.end(),
             [](auto & a, auto & b){
                 return a[0] < b[0];
             });

        vector<int> res(n,-1);
        for(int i = 0 ; i < n; ++i){
            int _end = nums[i][1];
            if(_end == _fend){
                continue;
            }
            for(int j = i + 1; j < n; ++j){
                if(_end <= nums[j][0]){
                    int pos = m1[nums[j][0]]; // 找到最近右侧区间的位置
                    int _pos = m1[nums[i][0]]; // 当前区间的位置
                    res[_pos] = pos;
                    break;
                }
            }
        }

        return res;
    }

    vector<int> findRightInterval_0(vector<vector<int>>& nums) {
        const int n = nums.size();
        if(n == 1) return {-1};
        map<int,int> m1;
        for(int i = 0; i < n; i++){
            m1[nums[i][0]] = i;
        }

        vector<int> res(n,-1);
        for(int i = 0; i < n ; i++){
            auto pos = m1.lower_bound(nums[i][1]);
            if(pos == m1.end()){
                continue;
            }else{
                res[i] = (*pos).second;
            }

        }
        return res;

    }
};


int main() {

    vector<vector<int>>  nums = {{1,4},{2,3},{3,4}};
    vector<int> ret = Solution().findRightInterval_0(nums);
    for(auto it : ret){
        cout << it <<endl;
    }
    return 0;
}
