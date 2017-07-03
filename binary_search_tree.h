/* 二叉查找树 */
#include <iostream>
#include <algorithm>

using T = int; //数据类型，钦定整型
using std::cout;
using std::endl; //测试用输出

class BSTNode {
    public:
        T key; //存储数据
        BSTNode *left; //左子结点
        BSTNode *right; //右子结点
        BSTNode *parent; //父结点
    //构造函数
        BSTNode(T value, BSTNode *l, BSTNode *r, BSTNode *p) :
        key(value), left(l), right(r), parent(p) {};
};

class Binary_search_tree {
    public:
        void MakeEmpty(); //清空树
        BSTNode *Find(const T&); //查找数据对应的结点
        BSTNode* FindMin(); //查找最小结点
        BSTNode* FindMax(); //查找最大结点
        void Insert(const T&); //插入结点
        void Delete(const T&); //删除结点
    private:
        BSTNode *root = NULL; //根结点
        /* 接口 */
        void make_empty(BSTNode* tree);
        BSTNode* find(BSTNode* tree, const T&);
        BSTNode* find_min(BSTNode* tree);
        BSTNode* find_max(BSTNode* tree);
        void ins(BSTNode* tree, BSTNode* node);
        void del(BSTNode* node);
};