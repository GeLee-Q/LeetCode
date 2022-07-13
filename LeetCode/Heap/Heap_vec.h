
#include <algorithm>
#include <vector>
#include <utility>

using namespace std;

class Heap_vec{

private:
    vector<int> a;
    int capacity;
    int size;
public:
    explicit Heap_vec(int __capacity);

    void insert(int data);
    void heapify(vector<int> & a, int n , int i);
    void removeMax();
    void build(vector<int> & a, int n);

    void _sort(vector<int> & b, int n);
};

Heap_vec::Heap_vec(int __capacity) {
    //构造函数
    a = vector<int>(capacity + 1);
    capacity = __capacity;
    size = 0;
}

void Heap_vec::heapify(vector<int> &a, int n, int i) {
    //自上往下堆化,每次都将把而二叉树的根节点为子树的最大值。
    while(true){
        int maxPos  = i;
        if(i*2 <= n && a[i] < a[i*2]) maxPos = i*2;
        if(i*2 + 1 <= n && a[maxPos] < a[i*2 + 1]) maxPos = i * 2 + 1;
        if(maxPos == i) break;
        swap(a[i] , a[maxPos]);
        i = maxPos;
    }
}

void Heap_vec::insert(int data) {
    //n = 堆中的数目的多少
    // i 为 从哪里开始建堆
    if(size >= capacity) return;
    ++size;
    a[size] = data;
    int i = size;
    //自下而上构造大顶堆
    while(i/2 > 0 && a[i] > a[i/2]){
        swap(a[i/2], a[i]);
        i = i/2;
    }
}

void Heap_vec::removeMax() {
    if(size == 0) return ;
    a[1] = a[size];
    --size;
    heapify(a, size, 1);
}

void Heap_vec::build(vector<int> &a, int n) {
    //对于完全二叉树来说， n/2 to n 都是叶子节点
    for(int i = n / 2; i >= 1; i--){
        heapify(a, n ,i);
    }
}

void Heap_vec::_sort(vector<int> &b, int n) {
    build(b,n);
    int k = n;
    while(k > 1){
        swap(b[n] , b[1] );
        --k;
        heapify(b, k , 1);
    }
}


