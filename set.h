/* 左倾红黑树 */
#include <iostream>
#include <algorithm>

using T = double; //数据类型，本次任务要求使用double
using std::cout;
using std::endl; //测试用输出

enum RBTColor {RED, BLACK};

class RBTNode {
    public:
        RBTColor color; //存储颜色
        T key; //存储数据
        RBTNode *left; //左子结点
        RBTNode *right; //右子结点
        RBTNode *parent; //父结点
    //构造函数
        RBTNode(RBTColor c, T value, RBTNode *l, RBTNode *r, RBTNode *p) :
        color(c), key(value), left(l), right(r), parent(p) {};
};

class Set {
    public:
        void insert(const T& element); //插入指定的结点
        void erase(const T& element); //删除指定的结点
        void clear(); //清空树
        int count(const T& element) const; //返回该数据是否存在
        bool empty(); //返回该树是否为空
        size_t size(); //返回树中结点的个数
    private:
        RBTNode *root = NULL;
        /* 接口 */
        void ins(RBTNode* tree, RBTNode* node); //插入
        void del(RBTNode* node); //删除
        void _clear(RBTNode* tree); //删除
        int _count(const T&); //判断数据是否存在
        size_t _size(RBTNode*  tree); //计数
        /* 内部操作函数 */
        RBTNode* find(RBTNode* tree, const T&); //查找
        RBTNode* find_min(RBTNode* tree); //查找最小值
        RBTNode* find_max(RBTNode* tree); //查找最大值
        /* 结点相关操作 */
        RBTNode* son(RBTNode* tree); //返回单儿子时的儿子结点
        RBTNode* sibling(RBTNode* tree); //返回兄弟结点
        RBTNode* grandparent(RBTNode* tree); //返回祖父结点
        RBTNode* uncle(RBTNode* tree); //返回叔父结点
        /* 红黑树特有部分函数 */
        void leftrotation(RBTNode* tree); //执行左旋
        void rightrotation(RBTNode* tree); //执行右旋
        void changecolor(RBTNode* tree); //执行改色
        /* 插入删除的辅助函数 */
        void insadjust(RBTNode* node); //插入调整
        void del_adjust1(RBTNode* node); //删除调整一
        void del_adjust2(RBTNode* node); //删除调整二
        void del_adjust3(RBTNode* node); //删除调整三
        void del_adjust4(RBTNode* node); //删除调整四
};