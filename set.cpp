#include "set.h"

/* ------接口与主要操作部分------ */

/* 插入指定的结点接口 */
void Set::insert(const T& key) {
    if (find(root, key) == NULL) {
        currentsize++;
        root = ins(root, key);
    }
    root->color = BLACK;
}

/* 插入指定的结点实现 */
RBTNode* Set::ins(RBTNode* tree, T key) {
    /* 如果是空，刚好插入 */
    if (tree == NULL)
        return new RBTNode(RED, key, NULL, NULL);
    /* 标准插入 */
    if (tree->key > key)
        tree->left = ins(tree->left, key);
    else
        tree->right = ins(tree->right, key);
    fix_up(tree);
    return tree;
} //PS：这样做的好处在于一边插入一边调整，比红黑树简化了很多

/* 删除指定的结点接口 */
void Set::erase(const T& key) {
    if (find(root, key) != NULL) {
        currentsize--;
        root = del(root, key);
        if (root != NULL)
            root->color = BLACK;
    }
}

/* 删除指定的结点实现 */
RBTNode* Set::del(RBTNode* tree, T key) {
    /* 若没有要删除的结点 */
    if (tree == NULL)
        return NULL;
    /* 向左 */
    if (tree->key > key) {
        /* 若左儿子与左儿子的左儿子同时为黑色 */
        if (tree->left != NULL && !isred(tree->left) && !isred(tree->left->left))
            tree = move_red_left(tree);
        tree->left = del(tree->left, key);
    }
    /* 相等或者向右 */
    else {
        /* 若左侧是红结点，那么两种情况都要右旋保持平衡 */
        if (isred(tree->left))
            tree = rotate_right(tree);
        /* 如果相等且右侧没有结点 */
        if (tree->key == key && tree->right == NULL) {
            RBTNode *t = tree->left;
            delete(tree);
            return t;
        }
        /* 若右儿子与右儿子的左儿子同时为黑色 */
        if (tree->right != NULL && !isred(tree->right) && !isred(tree->right->left))
            tree = move_red_right(tree);
        /* 不相等，可以向右递归了 */
        if (tree->key < key)
            tree->right = del(tree->right, key);
        /* 若相等 */
        else {
            tree->key = find_min(tree->right)->key;
            tree->right = delete_min(tree->right);
        }
        
    }
    tree = fix_up(tree);
    return tree;
}

/* 清空树接口 */
void Set::clear() {
    _clear(root);
    root = NULL;
    currentsize = 0;
}

/* 清空树实现 */
void Set::_clear(RBTNode* tree) {
    if (tree == NULL)
        return;
    _clear(tree->left);
    _clear(tree->right);
    delete(tree);
}

/* 返回该数据是否存在 */
int Set::count(const T& key) const {
    if (find(root, key) != NULL)
        return 1;
    else
        return 0;
}

/* 返回该树是否为空 */
bool Set::empty() {
    if (root == NULL)
        return true;
    else
        return false;
}

/* 返回树中结点的个数 */
size_t Set::size() {
    return currentsize;
}

/* ------内部操作函数------ */

/* 查找 */
RBTNode* Set::find(RBTNode* node, T key) const {
    RBTNode* p = node;
    while (p != NULL) {
        if (p->key > key)
            p = p->left;
        else if (p->key < key)
            p = p->right;
        else
            return p;
    }
    return NULL;
}

/* 查找最小数 */
RBTNode* Set::find_min(RBTNode* tree) {
    if (tree->left == NULL)
        return tree;
    else
        return find_min(tree->left);
}

/* 判断是否为红色 */
bool Set::isred(RBTNode* node) {
    if (node == NULL || node->color == BLACK)
        return false;
    else
        return true;
} //新增函数，好处在于不用再去讨论空的情况了，减少的麻烦

/* 执行左旋 */
RBTNode* Set::rotate_left(RBTNode* k1) {
    RBTNode *k2 = k1->right;
    k1->right = k2->left;
    k2->left = k1;
    k2->color = k2->left->color;
    k2->left->color = RED;
    return k2;  //返回结构顶点
}

/* 执行右旋 */
RBTNode* Set::rotate_right(RBTNode* k1) {
    RBTNode *k2 = k1->left;
    k1->left = k2->right;
    k2->right = k1;
    k2->color = k2->right->color;
    k2->right->color = RED;
    return k2; //返回结构顶点
}

/* 执行改色 */
RBTNode* Set::color_flip(RBTNode* k1) {
    k1->color = !k1->color;
    if (k1->left != NULL)
        k1->left->color = !k1->left->color;
    if (k1->right != NULL)
    k1->right->color = !k1->right->color;
    return k1;
}

/* 调整 */
RBTNode* Set::fix_up(RBTNode* node) {
    /* 如果是右儿子插入，化归为左儿子插入的问题 */
    if (isred(node->right))
        node = rotate_left(node);
    /* 如果是左儿子插入，右旋 */
    if (node->left != NULL && isred(node->left) && isred(node->left->left))
        node = rotate_right(node);
    /* 判断是否需要改色,并且将改色问题递归上去 */
    if (isred(node->left) && isred(node->right))
        color_flip(node);
    return node;
} //该函数用来调整，对某结点使用之后，该结点基本结构的颜色都已经解决

/* 移动红色到左侧 */
RBTNode* Set::move_red_left(RBTNode* tree) {
    /* 第一步，反色 */
    color_flip(tree); //两边一起改为红保证黑结点数量
    /* 第二步：如果如果tree的右儿子上出现了两个连续红色结点 */
    if (tree->right != NULL && isred(tree->right->left)) {
        tree->right = rotate_right(tree->right);
        tree = rotate_left(tree);
        color_flip(tree);
    }
    return tree;
}

/* 移动红色到右侧 */
RBTNode* Set::move_red_right(RBTNode* tree) {
    /* 第一步，反色 */
    color_flip(tree); //两边一起改为红保证黑结点数量
    /* 第二步：如果如果tree的左儿子上出现了两个连续红色结点 */
    if (tree->left != NULL && isred(tree->left->left)) {
        tree = rotate_right(tree);
        color_flip(tree);
    }
    return tree;
}

/* 删除tree的最小结点 */
RBTNode* Set::delete_min(RBTNode* tree) {
    /* 删除操作 */
    if (tree->left == NULL) {
        delete(tree);
        return NULL;
    }
    /* 若子结点和孙结点有不为黑的，就不能操作，否则有两个连续红色 */
    if (!isred(tree->left) && !isred(tree->left->left))
        tree = move_red_left(tree);
    /* 向下递归 */
    tree->left = delete_min(tree->left);
    /* 修正 */
    return fix_up(tree);
}