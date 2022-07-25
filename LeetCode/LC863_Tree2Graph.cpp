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


struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

const int MAX_SIZE = 510;
class Solution {
public:
/*
这道题的思路：1.建图 2.bfs
核心：建图
 */
    vector<int> ans;
    vector<int> distanceK(TreeNode* root, TreeNode* target, int k) {
        vector<vector<int>> graph(MAX_SIZE);//邻接矩阵构造图
        vector<int> visited(MAX_SIZE, 0);  // 因为是无向图，所以需要记忆数组
        buildGraph(root, graph);            //从二叉树构建无向图
        ans.clear();
        // dfs(graph, target->val, k , visited);

        //bfs

        queue<int> q1;
        q1.push(target->val);
        visited[target->val] = 1;
        while(!q1.empty() && k >= 0){
            int sz = q1.size();
            for(int i = 0; i < sz; i++){
                int cur = q1.front(); q1.pop();
                if(k == 0){
                    // cout << cur << endl;
                    ans.push_back(cur);
                    continue;
                }
                for(auto it : graph[cur]){
                    if(visited[it] == 0){
                        visited[it] = 1;
                        q1.push(it);
                    }
                }
            }
            k--;
        }
        return ans;
    }

    void dfs( vector<vector<int>> & graph, int begin, int k, vector<int> & visited){
        if(k == 0) ans.push_back(begin);
        visited[begin] = 1;
        for(auto & ite : graph[begin]){
            if(visited[ite] == 0){
                dfs(graph, ite, k-1, visited);
            }
        }
        return;
    }

    void buildGraph(TreeNode * root, vector<vector<int>> & graph){
        if(root == nullptr) return;
        if(root->left){
            graph[root->val].push_back(root->left->val);
            graph[root->left->val].push_back(root->val);
            buildGraph(root->left, graph);
        }
        if(root->right){
            graph[root->val].push_back(root->right->val);
            graph[root->right->val].push_back(root->val);
            buildGraph(root->right, graph);
        }
        return ;
    }
};


int main() {


    return 0;
}
