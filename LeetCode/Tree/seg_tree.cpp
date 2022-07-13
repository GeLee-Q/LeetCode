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
        int ls = 0; // 当前节点的左右子节点在tr的下标
        int rs = 0;

        int val = 0; // 当前节点值的数

        int lazy = 0; // 为懒标记 , 该标记表明，该区间每个点都要加上lazy
    };

    int N = 1e9;
    int MAXN = 120010;
    int idx = 1;

    vector<node> tr(MAXN);// 数组构造线段树

    void lazyCreate(int u){
        if(tr[u].ls == 0){
            tr[u].ls = idx++;
        }

        if(tr[u].rs == 0){
            tr[u].rs = idx++;
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
        //清楚标记
        tr[u].lazy = 0;
    }



    void updata(int u , int l , int r, int start , int end , int delta){
        // [l , r] 当前节点区间 u 为当前节点的编号
        // [s , e] 修改的区间 delta为修改量
        if(l > end && r < start){ // 没有交集
            return;
        }else if(start <= l && r <= end ){ // 完全包含
            tr[u].val += (start - end + 1) * delta;
            tr[u].lazy += delta;
            return;
        }else {
            int m = (l + r) >> 1;
            lazyCreate(u);
            pushDown(u, l, r); // 更新下一层节点的值
            if (start < m) {
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
        if(l > end && r < start){ // 没有交集
            return 0;
        }else if(start <= l && r <= end ){ // 完全包含
            return tr[u].val;
        }else {
            int m = (l + r) >> 1;
            lazyCreate(u);
            pushDown(u, l, r); // 更新下一层节点的值

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