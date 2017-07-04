#include  "AVL_tree.h"

/* 查找数据对应的结点接口 */
AVLNode* AVL_tree::Find(const T& key) {
    return find(root, key);
}

/* 查找数据对应的结点实现 */
AVLNode* AVL_tree::find(AVLNode* tree, const T& key) {
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

/* 返回AVL树的高度接口 */
int AVL_tree::Height() {
    return height(root);
}

/* 返回AVL树的高度实现 */
int AVL_tree::height(AVLNode* tree) {
    if (tree == NULL)
        return 0;
    else
        return 1 + std::max(height(tree->left), height(tree->right));
}

/* 查找最小数接口 */
AVLNode* AVL_tree::FindMin() {
    return find_min(root);
}

/* 查找最小数实现 */
AVLNode* AVL_tree::find_min(AVLNode* tree) {
    if (tree->left == NULL)
        return tree;
    else
        return find_min(tree->left);
}

/* 查找最大数接口 */
AVLNode* AVL_tree::FindMax() {
    return find_max(root);
}

/* 查找最大数实现 */
AVLNode* AVL_tree::find_max(AVLNode* tree) {
    if (tree->right == NULL)
        return tree;
    else
        return find_max(tree->right);
}
/* 插入结点接口 */
void AVL_tree::Insert (const T& key) {
    root = ins(root, key);
}

/* 插入结点实现 */
AVLNode* AVL_tree::ins(AVLNode* tree, T key) {
    if (tree == NULL)
        tree = new AVLNode(key, NULL, NULL);
    else if (key < tree->key) { //插入左子树
        tree->left = ins(tree->left, key);
        if (height(tree->left) - height(tree->right) == 2) { //树失去平衡
            if (key < tree->left->key) //插在左子树的左侧
                tree = LeftLeftRotation(tree);
            else //插在左子树的右侧
                tree = LeftRightRotation(tree);
        }
    }
    else if (key > tree->key) { //插入右子树
        tree->right = ins(tree->right, key);
        if (height(tree->right) - height(tree->left) == 2) { //树失去平衡
            if (key < tree->right->key) //插在右子树的左侧
                tree = RightLeftRotation(tree);
            else //插在右子树的右侧
                tree = RightRightRotation(tree);
        }
    }
    else //什么也不做
        cout << "This node has been added!" << endl;
    /* 处理高度 */
    tree->height = 1 + std::max(height(tree->left), height(tree->right));
    return tree;
}

/* 删除结点接口 */
void AVL_tree::Delete(const T& key) {
    AVLNode *z = find(root, key);
    if (z != NULL)
        root = del(root, z);
    else
        cout << "This node isn't exist!" << endl;
}

/* 删除结点实现 */
AVLNode* AVL_tree::del(AVLNode* tree, AVLNode* z) {
    if (tree == NULL || z == NULL)
        return NULL;
    else if (z->key < tree->key) { //要删除的结点在左子树上
        tree->left = del(tree->left, z);
        if (height(tree->right) - height(tree->left) == 2) { //树失去平衡
            if (height(tree->right->left) > height(tree->right->right)) //等价于右子树左侧有插入
                tree = RightLeftRotation(tree);
            else //等价于右子树右侧有插入
                tree = RightRightRotation(tree);
        }
    }
    else if (z->key > tree->key) { //要删除的结点的右子树上
        tree->right = del(tree->right, z);
        if (height(tree->left) - height(tree->right) == 2) { //数失去平衡
            if (height(tree->left->right) > height(tree->left->left)) //等价于左子树右侧插入
                tree = LeftRightRotation(tree);
            else //等价于左子树左侧插入
                tree = LeftLeftRotation(tree);
        }
    }
    else { //删除该结点
        if (!(tree->left || tree->right)) //若该结点是树叶
            tree = NULL;
        else {
            if (tree->left && tree->right) { //如果有两个子结点
                if (height(tree->left) >height(tree->right)) { //如左子树比右子树高
                    AVLNode *max = find_max(tree->left);
                    tree->key = max->key;
                    tree->left = del(tree->left, max);
                }
                else { //右子树比左子树高
                    AVLNode *min = find_min(tree->right);
                    tree->key = min->key;
                    tree->right = del(tree->right, min);
                }
            }
            else { //若只有一个结点
                AVLNode *temp = tree;
                tree = (tree->left != NULL)? tree->left : tree->right;
                delete(temp);
            }
        }
    }
    return tree;
}

/* LL旋转 */
AVLNode* AVL_tree::LeftLeftRotation(AVLNode* k1) {
    AVLNode *k2 = k1->left;
    k1->left = k2->right;
    k2->right = k1;
    k1->height = 1 + std::max(height(k1->left), height(k1->right));
    k2->height = 1 + std::max(height(k2->left), k1->height);
    return k2;
}

/* RR旋转 */
AVLNode* AVL_tree::LeftRightRotation(AVLNode* k1) {
    AVLNode *k2 = k1->right;
    k1->right = k2->left;
    k2->left = k1;
    k1->height = 1 + std::max(height(k1->left), height(k1->right));
    k2->height = 1 + std::max(height(k2->right), k1->height);    
    return k2;
}

/* LR旋转 */
AVLNode* AVL_tree::RightLeftRotation(AVLNode* k1) {
    k1->left = RightRightRotation(k1->left);
    return LeftLeftRotation(k1);
}

/* RL旋转 */
AVLNode* AVL_tree::RightRightRotation(AVLNode* k1) {
    k1->right = LeftLeftRotation(k1->right);
    return RightRightRotation(k1);
}