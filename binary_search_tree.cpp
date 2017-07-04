#include "binary_search_tree.h"

/* 清空树接口 */
void Binary_search_tree::MakeEmpty() {
    make_empty(root);
}

/* 清空树实现 */
void Binary_search_tree::make_empty(BSTNode* tree) {
    if (tree != NULL) {
        delete(tree->left);
        delete(tree->right);
        delete(tree);
    }
}
/* 查找数据对应的结点接口 */
BSTNode* Binary_search_tree::Find(const T& key) {
    return find(root, key);
}

/* 查找数据对应的结点实现 */
BSTNode* Binary_search_tree::find(BSTNode* tree, const T& key) {
    if (tree == NULL)
        return NULL;
    else {
        if (tree->key == key)
            return tree;
        else if (tree->key > key)
            return find(tree->left, key);
        else
            return find(tree->right, key);
    }
}

/* 查找最小数接口 */
BSTNode* Binary_search_tree::FindMin() {
    return find_min(root);
}

/* 查找最小数实现 */
BSTNode* Binary_search_tree::find_min(BSTNode* tree) {
    if (tree->left == NULL)
        return tree;
    else
        return find_min(tree->left);
}

/* 查找最大数接口 */
BSTNode* Binary_search_tree::FindMax() {
    return find_max(root);
}

/* 查找最大数实现 */
BSTNode* Binary_search_tree::find_max(BSTNode* tree) {
    if (tree->right == NULL)
        return tree;
    else
        return find_max(tree->right);
}

/* 插入结点接口 */
void Binary_search_tree::Insert(const T& key) {
    BSTNode* new_node = new BSTNode(key, NULL, NULL, NULL);
    if (root == NULL)
        root = new_node;
    else
        ins(root, new_node);
}

/* 插入结点实现 */
void Binary_search_tree::ins(BSTNode* tree, BSTNode* node) {
    BSTNode *p = tree, *pre = NULL;
    while (p != NULL) {
        if (p->key == node->key)
            break;
        else if (p->key > node->key) {
            pre = p;
            p = p->left;
        }
        else if (p->key < node->key) {
            pre = p;
            p = p->right;
        }
        if (p == NULL) {
            if (pre->key > node->key)
                pre->left = node;
            else
                pre->right = node;
            node->parent = pre;
        }
    }
}

/* 删除结点接口 */
void Binary_search_tree::Delete(const T& key) {
    BSTNode* p = find(root, key);
    if (p)
        del(p);
}

/* 删除结点实现 */
void Binary_search_tree::del(BSTNode* tree) {
    BSTNode* pre = tree->parent;
    if (!(tree->left || tree->right)) { //若为叶子结点
        (pre->key > tree->key) ? pre->left = NULL : pre->right = NULL;
        delete(tree);    
    }
    else {
        if (tree->left && tree->right) { //若有两个结点
            BSTNode *r_min = find_min(tree->right);
            tree->key = r_min->key; //用右子树的最小结点代替它
            del(r_min);
        }
        else { //若有一个结点
            if (tree->left) //若只有左结点
                (pre->key > tree->key) ? pre->left = tree->left : pre->right = tree->left;
            else
                (pre->key > tree->key) ? pre->left = tree->right : pre->right = tree->right;                
        }
    }
}