#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<cmath>
#include<string>
#include<stack>
#include<queue>
#include<cstring>
#include<map>
#include<iterator>
#include<list>
#include<set>
#include<functional>
#include<memory.h> // 低版本G++编译器不支持，若使用这种G++编译器此段应注释掉
#include<iomanip>
#include<vector>
#include<cstring>
#define scd(n) scanf("%d", &n)
#define scf(n) scanf("%f", &n)
#define scc(n) scanf("%c", &n)
#define scs(n) scanf("%s", n)
#define prd(n) printf("%d", n)
#define prf(n) printf("%f", n)
#define prc(n) printf("%c", n)
#define prs(n) printf("%s", n)
#define rep(i, a, n) for (int i = a; i <= n; i++) // i为循环变量，a为初始值，n为界限值，递增
#define per(i, a, n) for (int i = a; i >= n; i--) // i为循环变量， a为初始值，n为界限值，递减
#define pb push_back
#define fi first
#define se second
#define mp make_pair
using namespace std;
const int inf = 0x3f3f3f3f; // 无穷大
const int maxn = 2e5+2; // 最大值
typedef long long ll;
typedef long double ld;
typedef pair<ll, ll>  pll;
typedef pair<int, int> pii;
//*******************************分割线，以上为代码自定义代码模板***************************************//

int father[maxn];

struct Node {
	int left;
	int right;
	int value;
}node[maxn << 2];

void BuildTree(int i, int l, int r) { // 自上而下地建造树
	node[i].left = l;
    	node[i].right = r;
	node[i].value = 0; // 赋初值，都是0。这些数值的更新之后再做，先把树型结构做出来
	if (l == r) { // 说明到了叶子节点
		father[l] = i;       // 保存l（是字母l，不是数字1）位置的输入数值在线段树中的下标，因为i是node的标号，代表第i个node
		return;            // 到了叶子结点自然要返回
	}
	BuildTree(i << 1, l, (l + r) / 2);  // 初始化左子树
	BuildTree(i << 1 | 1, (l + r) / 2 + 1, r); // 初始化右子树。
}

void UpdateTree(int i) { // 自下而上地update树
	if (i == 1) return; // 说明已到达根节点
	int fi = i >> 1; // 获取父结点的下标
	// node[fi].value = max(node[fi << 1].value, node[fi << 1 | 1].value); // 获得最大值
	node[fi].value = node[fi << 1].value + node[fi << 1 | 1].value; // 获得两段区间总和   具体获得什么需要根据题目要求而定
	UpdateTree(fi);
}
// 区间查询，调用函数时为QueryTree(1,l,r)，即从根节点自上往下查询
int QueryTree(int i,int l,int r){
	int sum = 0;
	if (l == node[i].left && r == node[i].right) {
		// 如果刚好就是这个区间，我们直接返回
		sum += node[i].value;
		return sum;
	}
	i = i << 1; // 如果没有刚刚好，那么就先查询这个节点的左子节点
	if (l <= node[i].right) {
		// 说明部分包含左子树
		if (r <= node[i].right) {
			// 说明全包含在左子树
			sum += QueryTree(i, l, r);
		}
		else {
			sum += QueryTree(i, l, node[i].right); // 只包含部分
		}
	}
	i += 1; // 查询右子节点
	if (r >= node[i].left) {
		// 说明部分包含右子树
		if (l >= node[i].left){
			// 说明全包含在右子树。
			sum += QueryTree(i, l, r);
		}
		else {
			sum += QueryTree(i, node[i].left, r); // 部分包含
		}
	}
	return sum; // 返回求得的区间和
}
int main(){ // 主函数处理
	freopen("in.txt", "r", stdin); // 提交的时候要注释掉
	ios::sync_with_stdio(false); // 打消iostream中输入输出缓存，节省时间。
	cin.tie(0); cout.tie(0); // 可以通过tie(0)（0表示NULL）来解除cin与cout的绑定，进一步加快执行效率。
	int n, m, g;
	while (cin >> n >> m) {
		BuildTree(1, 1, n);
		rep (i, 1, n) {
			cin >> g;
			node[father[i]].value = g;
			UpdateTree(father[i]);
		}
		char ch;
		int a, b;
		while (m--) {
			cin >> ch >> a >> b;
			if (ch == 'Q'){
				cout << QueryTree(1, a, b) << endl;;
			}
			else {
				node[father[a]].value = b;
				UpdateTree(father[a]);
			}
		}
	}
	return 0;
}

// reference https://blog.csdn.net/hzf0701/article/details/107859659?utm_medium=distribute.pc_relevant.none-task-blog-baidujs_title-1&spm=1001.2101.3001.4242