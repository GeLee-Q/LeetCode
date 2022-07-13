#include <string>
#include <unordered_map>
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;


class Solution{
public:
    vector<string> findRepeatedDnaSequences(string s){

    }
};


signed main(){
    string s1;
    cin >> s1;
    vector<string> res = Solution().findRepeatedDnaSequences(s1);
    for(auto it : res){
        cout << it << " ";
    }
}