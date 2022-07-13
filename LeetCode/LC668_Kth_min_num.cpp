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
#include <iostream>
#include <queue>
#include <iosfwd>
#include <sstream>
#include <stack>


using namespace std;






class Solution {
public:
    typedef pair<int,int> PII;
    int findKthNumber(int m, int n, int k) {
        // 堆排序

        priority_queue<PII, vector<PII>, greater<PII> > q1;
        //将每一行最小的数入列
        for(int i = 1 ; i <= m ; ++i){
            pair<int, int> tmp = {i , i};
            q1.push(tmp);
        }

        for(int i = 0 ; i < k-1; ++i){
            auto a = q1.top(); q1.pop();
            if(a.first + a.second > a.second * n){
               continue;
            }
            pair<int, int> tmp = {a.first + a.second , a.second};
            q1.push(tmp);
        }

        return q1.top().first;
    }
};

int stringToInteger(string input) {
    return stoi(input);
}

int main() {
    string line;
    while (getline(cin, line)) {
        int m = stringToInteger(line);
        getline(cin, line);
        int n = stringToInteger(line);
        getline(cin, line);
        int k = stringToInteger(line);

        int ret = Solution().findKthNumber(m, n, k);

        string out = to_string(ret);
        cout << out << endl;
    }
    return 0;
}
