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


    vector<int> asteroidCollision(vector<int>& asteroids) {
        vector<int> ans;
        stack<int> s1;
        for(auto it : asteroids){
            bool ok = true;
            while(ok && !s1.empty() && s1.top() > 0 && it <0){
                int cur = s1.top() + it;
                if(cur <= 0) s1.pop();
                if(cur >= 0) ok = false;
            }
            if(ok) s1.push(it);
        }

        while(!s1.empty()){
            ans.push_back(s1.top());
            s1.pop();
        }
        reverse(ans.begin(), ans.end());
        return ans;
    }
};


int main() {

    vector<int> arr = {10,2,-5};

    vector<int> res = Solution().asteroidCollision(arr);

    for(auto it : res){
        cout << it << endl;
    }

//    cout << out << endl;

    return 0;
}
