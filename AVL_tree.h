/* AVL树 */
#include <iostream>
#include <algorithm>

using T = int; //数据类型，钦定整形
using std::cout;
using std::endl;

class AVLNode {
    public:
        T key; //存储数据
        int height; //结点高度
        AVLNode *left; //左子结点
        AVLNode *right; //右子结点
    //构造函数
        AVLNode(T value, AVLNode *l, AVLNode *r) :
        key(value), height(0), left(l), right(r) {};
};

class AVL_tree {
    public:
        AVLNode* Find(const T&); //查找数据对应的结点
        int Height(); //返回AVL树的高度
        AVLNode* FindMin(); //查找最小结点
        AVLNode* FindMax(); //查找最大结点
        void Insert (const T&); //插入结点
        void Delete(const T&); //删除结点
    private:
        AVLNode *root = NULL; //根结点
        /* 接口 */
        AVLNode* find(AVLNode* tree, const T&);
        int height(AVLNode* tree);
        AVLNode* find_min(AVLNode* tree);
        AVLNode* find_max(AVLNode* tree);
        AVLNode* ins(AVLNode* tree, T key);
        AVLNode* del(AVLNode* tree, AVLNode* node);
        /* 旋转操作 */
        AVLNode* LeftLeftRotation(AVLNode* tree);
        AVLNode* LeftRightRotation(AVLNode* tree);
        AVLNode* RightLeftRotation(AVLNode* tree);
        AVLNode* RightRightRotation(AVLNode* tree);
};