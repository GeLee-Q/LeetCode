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

struct node {
    node(){
        ls = rs = val = lazy = 0;
    }
    int ls; // 当前节点的左右子节点在tr的下标
    int rs;
    int val; // 当前节点值的数
    int lazy; // 为懒标记 , 该标记表明，该区间每个点都要加上lazy
}tr[120010];// 数组构造线段树;

int N = 1e9;
int idx = 1;

void lazyCreate(int u){
    if(!tr[u].ls){
        tr[u].ls = ++idx;
    }

    if(!tr[u].rs){
        tr[u].rs = ++idx;
    }
}

void pushUp(int u){
    // 该节点的val 等于其左右子节点的val相加
    tr[u].val = tr[tr[u].ls].val + tr[tr[u].rs].val;
}

void pushDown(int u, int l, int r){
    int delta = tr[u].lazy;
    int mid = (l + r) >> 1;
    //更新该节点 左右节点的 懒标记
    tr[tr[u].ls].lazy += delta;
    tr[tr[u].rs].lazy += delta;
    //更新val
    tr[tr[u].ls].val += (mid - l + 1) * delta;
    tr[tr[u].rs].val += (r - mid) * delta;
    //清除标记
    tr[u].lazy = 0;
}



void updata(int u, int l, int r, int start, int end, int delta){
    // [l , r] 当前节点区间 u 为当前节点的编号
    // [s , e] 修改的区间 delta为修改量
    if(l > end || r < start){ // 没有交集
        return;
    }else if(start <= l && r <= end ){ // 完全包含
        tr[u].val += (r - l + 1) * delta;
        tr[u].lazy += delta;
        return;
    }else {
        int m = (l + r) >> 1;
        lazyCreate(u);
        pushDown(u, l, r); // 更新下一层节点的值
        if (start <= m) {
            updata(tr[u].ls, l, m, start, end, delta);
        }
        if (end > m) {
            updata(tr[u].rs, m + 1, r, start, end, delta);
        }
        //根据子节点更新自己的值
        pushUp(u);
    }
}



int query(int u, int l, int r, int start, int end){
    // u 当前节点的编号， [l , r] 节点区间， [s , e] 查询区间;

    // 如果当前区间是查询区间的子集时
    if(l > end || r < start){ // 没有交集
        return 0;
    }else if(start <= l && r <= end ){ // 完全包含
        return tr[u].val;
    }else {
        lazyCreate(u);
        pushDown(u, l, r); // 更新下一层节点的值

        int m = (l + r) >> 1;
        int res = 0;
        if(start <= m){
            res += query(tr[u].ls, l , m , start, end);
        }
        if(end > m){
            res += query(tr[u].rs, m + 1, r, start ,end);
        }
        return res;
    }

}


int main() {

    vector<vector<int>> test = {{10, 20},{15, 25}, {20,30}};

    for(auto &  ite: test){
        int res = query(1 , 1, N + 1, ite[0] + 1, ite[1]);
        if( res > 0 ){
            cout << "false" << endl;
            continue;
        }
        updata(1 , 1 , N + 1, ite[0] + 1, ite[1], 1);
        cout << "True " << endl;
    }
    return 0;
}



