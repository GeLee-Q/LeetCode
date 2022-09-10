#include <cstdio>
#include <algorithm>
#include <cstdint>
#include <vector>
#include <queue>
#include <cmath>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <iostream>
#include <string>
#include <map>
#include <iosfwd>
#include <sstream>
#include <stack>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <set>
#include <chrono>

using namespace std;




#define TICK(x) auto bench_##x = std::chrono::steady_clock::now();
#define TOCK(x) printf("%s: %lfs\n", #x, std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::steady_clock::now() - bench_##x).count());





class Node{
public:
    int key;
    int val;
    Node * prev;
    Node * next;
    Node(int _key, int _val) : key(_key), val(_val), prev(nullptr), next(nullptr){};
};


class DoubleList{

public:
    Node * head;
    Node * tail;

    DoubleList(): head(new Node(0 , 0)), tail(new Node(0, 0)){
        head->next = tail;
        tail->prev = head;
    }

    void addFirst(Node * node){
        node->next = head->next;
        node->prev = head;

        head->next->prev = node;

        head->next = node;
    }

    Node *  deleteNode(Node * node){
        node->next->prev = node->prev;

        node->prev->next = node->next;

        return node;
    }

    Node * deleteLast(){
        if(head->next != tail){
            return deleteNode(tail->prev);
        }
        return nullptr;
    }
};





class LRUCache {
public:
    int cap;
    DoubleList dll;
    unordered_map<int, Node* > m1;
    int cnt = 0;

    LRUCache(int capacity) {
        cap = capacity;
        cnt = 0;
    }

    /*
    每次取用，更新节点到头部
    首先删除该节点
    再将该节点添加到头部
     */
    int get(int key) {
        if(m1.count(key) == 0) return -1;

        int val = m1[key]->val;
        Node * node = dll.deleteNode(m1[key]);
        dll.addFirst(node);

        return val;
    }

    void put(int key, int value) {
        if(m1.count(key) != 0){
            m1[key]->val = value;
            // 更新值后，更新到头部
            get(key);
        }
        else
        {
            if(cnt == cap){
                Node * delNode = dll.deleteLast();
                m1.erase(delNode->key);
                delete delNode;
                cnt--;
            }

            Node * newNode = new Node(key, value);
            m1[key] = newNode;

            dll.addFirst(newNode);
            cnt++;
        }
    }

    ~LRUCache(){
        Node * cur = dll.head->next;
        while(cur != dll.tail){
            cur = cur->next;
            delete(cur->prev);
        }

        delete (dll.head);
        delete (dll.tail);
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */