#include <cstdio>
#include <algorithm>
#include <cstdint>
#include <stdio.h>
#include <math.h>
#include <algorithm>
#include <vector>
#include <queue>
#include <cmath>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <iostream>
#include <string.h>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <iostream>
#include <queue>
#include <iosfwd>
#include <sstream>

using namespace std;

class Solution {
public:
    int longestSubsequence(vector<int>& arr, int diff) {
        unordered_map<int,int> pos;

        const int n = arr.size();
        vector<int> dp(n + 1, 1);

        int res = 1;
        for(int i = 1; i <= n; ++i){
            int tmp = arr[i-1] - diff;
            if(pos.count(tmp)){
                dp[i] = dp[pos[tmp]+1] + 1;
            }
            pos[arr[i-1]]= i-1;
            res = max(res, dp[i]);
        }
        return res;
    }
};


int main() {
    vector<int> arr = {1,3,5,7};
    int diff = 1;

    int res = Solution().longestSubsequence(arr, diff);
    cout << res << endl;
}