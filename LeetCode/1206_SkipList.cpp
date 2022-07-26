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


struct Node{
    Node * right;
    Node * down;
    int val;
    Node(Node * _right, Node * _down, int _val)
            :right(_right), down(_down), val(_val){}
};


class Skiplist {
private:
    Node * head;
    const static int MAX_LEVEL = 32;
    vector<Node* > pathList; // 搜索路劲

public:
    Skiplist() {
        //初始化 头节点
        head = new Node(nullptr, nullptr, -1);
        pathList.reserve(MAX_LEVEL);
    }

    bool search(int target) {
        Node * p = head;
        while(p){
            //  向右找到目标区间
            while(p->right && p->right->val < target){
                p = p->right;
            }
            // 横向没有找到目标值，则继续往下走
            if(!p->right || target < p->right->val){
                p = p->down;
            }else if(p->right->val == target){
                return true;
            }
        }
        return false;
    }

    void add(int num) {
        pathList.clear();
        Node * p = head;
        // 找到prevs节点, 同时记录之前下来的每一层
        while(p){
            while(p->right && p->right->val < num){
                p = p->right;
            }
            pathList.push_back(p);
            p = p->down;
        }

        bool insertUp = true;
        Node * downNode = nullptr;

        //自下而上的搜索路径
        while(insertUp && pathList.size() > 0){
            Node * insert = pathList.back();
            pathList.pop_back();

            // 在路径的每一层插入相应的节点，同时更新下节点
            insert->right = new Node(insert->right, downNode, num);
            downNode = insert->right;

            insertUp = (rand() & 1) == 0;
        }

        /*
        如果直接一路添加上去，重新添加头节点
         */
        // if(insertUp)
        // {
        //     head = new Node(new Node(NULL,downNode,num), head, -1);
        // }

    }

    bool erase(int num) {
        Node * p = head;
        bool seen = false;
        while(p){
            //  向右找到目标区间
            while(p->right && p->right->val <  num){
                p = p->right;
            }
            // 横向没有找到目标值，则继续往下走
            if(!p->right ||  num < p->right->val){
                p = p->down;
            }else if(p->right->val ==  num){
                seen = true;
                p->right = p->right->right;
                p = p->down;
            }
        }
        return seen;
    }
};

/**
 * Your Skiplist object will be instantiated and called as such:
 * Skiplist* obj = new Skiplist();
 * bool param_1 = obj->search(target);
 * obj->add(num);
 * bool param_3 = obj->erase(num);
 */

int main() {


    return 0;
}
