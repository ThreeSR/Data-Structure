class DisjointSet {
    private:
        int[maxNum] father; // maxNum根据题目要求来设定，比如LC547省份数量，maxNum设置为210即可。
    public:
        void init(int n) { // initialize disjoint set
            for (int i = 0; i < n; i++) {
                father[i] = i;
            }
        }
        // find函数有两种写法
        // 写法一
        int find(int x) {
            int root = x;
            while (root != father[root]) { // 寻根
                root = father[root];
            }
            int originalFather;
            while (x != root) {  // 路径压缩
                originalFather = father[x];
                father[x] = root;
                x = originalFather;
            }
        }
        // 写法二
        int find(int x) {
            return x == father[x] ? x : father[x] = find(father[x]);  // 代码简洁，并且已经有路径压缩包含其中。
        }
        // union的写法
        void union2(int x, int y) { // 这里取名为union2的原因是，union是C++中的一个关键字，以示不同。也可以取名为merge或者join
            int rootX = find(x);
            int rootY = find(y);
            if (rootX != rootY) {
                father[rootX] = rootY; // 合并
            }
        }
        bool same(int x, int y) {
            return find(x) == find(y); // 判断两个元素是不是来自于同一个集合
        }
};
int main() {
    DisjointSet UnionFind;
    int n = ... // 根据题目要求得到
    UnionFind.init(n); // n的来源是题目的内容，对并查集进行初始化
    // 之后根据题目要求进行相应处理即可
}