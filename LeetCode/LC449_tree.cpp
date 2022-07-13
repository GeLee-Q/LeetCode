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



 struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 };

class Codec {

public:

    // Encodes a tree to a single string.
    void traverse(TreeNode * root , vector<int> & num){
        if(!root) return;
        num.push_back(root->val);
        traverse(root->left, num);
        traverse(root->right, num);
    }

    string serialize(TreeNode* root) {
        TreeNode * node = root;
        vector<int> num;

        traverse(node, num);
        if(num.size() == 0) return "";

        string s;
        for(int i = 0 ; i < num.size() -1 ; ++i){
            s = s + to_string(num[i]) + ",";
        }

        s += to_string(num.back());
        return s;
    }

    // Decodes your encoded data to tree.

    vector<int> stringToNum(string & s1){
        vector<int> num;
        int pos = 0;
        int start = 0;
        while(pos < s1.size()){
            while(pos < s1.size() && s1[pos] == ','){
                pos++;
            }
            start = pos;
            while(pos < s1.size() && s1[pos] != ','){
                pos++;
            }
            if(start < s1.size()){
                string tmp = s1.substr(start, pos - start);
                num.push_back(stoi(tmp));
            }
        }
        return num;
    }

    TreeNode * dfs(vector<int> & num){
        if(num.size() == 0) return nullptr;
        TreeNode * root = new TreeNode(num[0]);
        vector<int> left;
        vector<int> right;
        for(auto val : num){
            if(val < num[0]){
                left.push_back(val);
            }else if(val > num[0]){
                right.push_back(val);
            }

        }
        root->left =  dfs(left);
        root->right = dfs(right);
        return root;
    }

    TreeNode* deserialize(string data) {
        vector<int> num = stringToNum(data);
        return dfs(num);
    }
};


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

TreeNode* stringToTreeNode(string input) {
    trimLeftTrailingSpaces(input);
    trimRightTrailingSpaces(input);
    input = input.substr(1, input.length() - 2);
    if (!input.size()) {
        return nullptr;
    }

    string item;
    stringstream ss;
    ss.str(input);

    getline(ss, item, ',');
    TreeNode* root = new TreeNode(stoi(item));
    queue<TreeNode*> nodeQueue;
    nodeQueue.push(root);

    while (true) {
        TreeNode* node = nodeQueue.front();
        nodeQueue.pop();

        if (!getline(ss, item, ',')) {
            break;
        }

        trimLeftTrailingSpaces(item);
        if (item != "null") {
            int leftNumber = stoi(item);
            node->left = new TreeNode(leftNumber);
            nodeQueue.push(node->left);
        }

        if (!getline(ss, item, ',')) {
            break;
        }

        trimLeftTrailingSpaces(item);
        if (item != "null") {
            int rightNumber = stoi(item);
            node->right = new TreeNode(rightNumber);
            nodeQueue.push(node->right);
        }
    }
    return root;
}

string treeNodeToString(TreeNode* root) {
    if (root == nullptr) {
        return "[]";
    }

    string output = "";
    queue<TreeNode*> q;
    q.push(root);
    while(!q.empty()) {
        TreeNode* node = q.front();
        q.pop();

        if (node == nullptr) {
            output += "null, ";
            continue;
        }

        output += to_string(node->val) + ", ";
        q.push(node->left);
        q.push(node->right);
    }
    return "[" + output.substr(0, output.length() - 2) + "]";
}

int main() {
    string line;
    while (getline(cin, line)) {
        TreeNode* root = stringToTreeNode(line);
//        TreeNode* ret = Solution().CodecDriver(root);
        Codec* ser = new Codec();
        Codec* deser = new Codec();
        string tree = ser->serialize(root);
        TreeNode* ans = deser->deserialize(tree);

        string out = treeNodeToString(ans);
        cout << out << endl;
    }
    return 0;
}