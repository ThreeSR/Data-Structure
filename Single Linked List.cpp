// 单链表
struct ListNode {
    int val;  // 节点上存储的元素
    ListNode *next;  // 指向下一个节点的指针
    ListNode(int x) : val(x), next(NULL) {}  // 节点的构造函数
};

/* 
如果不用构造函数也可以，但是没办法直接赋值：
ListNode* head = new ListNode();
head->val = 5;

如果使用构造函数：

ListNode* head = new ListNode(5);

*/