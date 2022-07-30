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
    const static int N = 20010;
    static vector<int> p ;
    static vector<int> sz;

    int ans = 1;
    int find(int x){
        if(p[x] != x){
            p[x] = find(p[x]);
        }
        return p[x];
    }

    //　提取质因子是有序的，为了保证合并的祖先是唯一的，所以用最小质因子作为唯一
    void merge(int a, int b){
        if(find(a) == find(b)) return; //

        sz[find(a)] += sz[find(b)];     // 二者连通块得数目合一
        p[find(b)] = p[find(a)];        // merge  a的祖先作为了合并的最终祖先
        ans = max(ans, sz[find(a)]);    // 更新结果
    }

    int largestComponentSize(vector<int>& nums) {
        int n = nums.size();
        unordered_map<int, vector<int>> m1;
        for(int i = 0; i < n; i++){
            // 求取cur得所有质因数, 存取该质因数对应的所有数得坐标
            int cur = nums[i];
            for(int j = 2; j * j <= cur ; j++){
                if(cur % j == 0) m1[j].push_back(i);
                while(cur % j == 0) cur /= j;
            }
            if(cur > 1) m1[cur].push_back(i);
        }

        for(int  i = 0 ; i <= n; i++){
            p[i] = i; // 初始化并查集
            sz[i] = 1; // 初始化每个连通块得数量
        }

        // 联通这些点
        for(auto & it : m1){
            vector<int> tmp = it.second;
            // cout << tmp.size() << endl;
            for(int i = 1 ; i < tmp.size(); i++){
                merge(tmp[0], tmp[i]);
            }
        }

        return ans;
    }
};

std::vector<int> Solution::p(N, 0);
std::vector<int> Solution::sz(N, 0);

void trimLeftTrailingSpaces(string &input) {
    input.erase(input.begin(), find_if(input.begin(), input.end(), [](int ch) {
        return !isspace(ch);
    }));
}

void trimRightTrailingSpaces(string &input) {
    input.erase(find_if(input.rbegin(), input.rend(), [](int ch) {
        return !isspace(ch);
    }).base(), input.end());
}

vector<int> stringToIntegerVector(string input) {
    vector<int> output;
    trimLeftTrailingSpaces(input);
    trimRightTrailingSpaces(input);
    input = input.substr(1, input.length() - 2);
    stringstream ss;
    ss.str(input);
    string item;
    char delim = ',';
    while (getline(ss, item, delim)) {
        output.push_back(stoi(item));
    }
    return output;
}

int main() {
    string line;
    while (getline(cin, line)) {
        vector<int> nums = stringToIntegerVector(line);

        int ret = Solution().largestComponentSize(nums);

        string out = to_string(ret);
        cout << out << endl;
    }
    return 0;
}