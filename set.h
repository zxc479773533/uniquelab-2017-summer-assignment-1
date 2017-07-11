#ifndef SET //include保护
#define SET


/* 左倾红黑树 */
#include <iostream>
#include <algorithm>

using T = double; //数据类型，本次任务要求使用double
using std::cout;
using std::endl; //测试用输出

enum RBTColor {BLACK, RED};

class RBTNode {
    public:
        bool color; //存储颜色
        T key; //存储数据
        RBTNode *left; //左子结点
        RBTNode *right; //右子结点
    //构造函数
        RBTNode(RBTColor c, T value, RBTNode *l, RBTNode *r) :
        color(c), key(value), left(l), right(r) {};
};

class Set {
    public:
        void insert(const T& element); //插入指定的结点
        void erase(const T& element); //删除指定的结点
        void clear(); //清空树
        int count(const T& element) const; //返回该数据是否存在
        bool empty(); //返回该树是否为空
        size_t size(); //返回树中结点的个数
    //析构函数
        ~Set() {delete root;}
    private:
        RBTNode *root = NULL;
        int currentsize = 0;
        /* 接口 */
        RBTNode* ins(RBTNode* tree, T key); //插入
        RBTNode* del(RBTNode* tree, T key); //删除
        void _clear(RBTNode* tree); //清空
        /* 内部操作函数 */
        RBTNode* find(RBTNode* tree, T key) const; //查找
        bool isred(RBTNode* node); //判断是否为红色
        RBTNode* find_min(RBTNode* tree); //查找最小值
        RBTNode* rotate_left(RBTNode* node); //执行左旋
        RBTNode* rotate_right(RBTNode* node); //执行右旋
        RBTNode* color_flip(RBTNode* node); //执行改色
        RBTNode* fix_up(RBTNode* node); //调整
        RBTNode* move_red_left(RBTNode* tree); //移动红色到左侧
        RBTNode* move_red_right(RBTNode* tree); //移动红色到右侧
        RBTNode* delete_min(RBTNode* tree); //删除tree的最大结点
};

#endif