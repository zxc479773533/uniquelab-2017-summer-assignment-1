#include "set.h"

/* ------接口与主要操作部分------ */

/* 插入指定的结点接口 */
void Set::insert(const T& key) {
    root = ins(root, key);
    RBTNode* new_node = find(root, key);
    insadjust(new_node);
}

/* 插入指定的结点实现 */
RBTNode* Set::ins(RBTNode* tree, T key) {
    if (tree == NULL)
        tree = new RBTNode(RED, key, NULL, NULL, NULL);
    else if (key < tree->key) { //插入左子树
        tree->left = ins(tree->left, key);
        tree->left->parent = tree;
    }
    else if (key > tree->key) { //插入右子树
        tree->right = ins(tree->right, key);
        tree->right->parent = tree;
    }
    else //什么也不做
        cout << "This node has been added!" << endl;
    return tree;
}

/* 删除指定的结点接口 */
void Set::erase(const T& key) {
    RBTNode *node = find(root, key);
    if (node == NULL)
        cout << "This node isn't exist!" << endl;
    else
        del(node);
}

/* 删除指定的结点实现 */
void Set::del(RBTNode* node) {
    if (node->left != NULL && node->left != NULL) { //若要删除的结点有两个子结点
        RBTNode *min = find_min(node->right);
        node->key = min->key;
        del(min);
    }
    else { //其他情况，若是叶子把一个NULL当做儿子
        RBTNode *P = node->parent; //父结点
        RBTNode *N = son(node); //儿子结点
        RBTColor N_color = (N != NULL)? N->color : BLACK; //儿子结点颜色，空结点当做黑色
        if (node->color == RED) { //若要删除的结点为红
            if (P->left == node) //用N替换该结点
                P->left = N;
            else
                P->right = N;
            N->parent = P;
            delete(node);
        }
        else if (node->color == BLACK && N_color == RED) { //若要删除的结点为黑，其儿子为红
            N->color = BLACK; //将其变成黑
            if (P->left == node) //用N替换该结点
                P->left = N;
            else
                P->right = N;
            N->parent = P;
            delete(node);
        }
        else { //若该结点和N均为黑色
            if (P->left == node) //用N替换该结点
                P->left = N;
            else
                P->right = N;
            N->parent = P;
            delete(node);
            del_adjust1(N);
        }
    }
}
/* 清空树接口 */
void Set::clear() {
    _clear(root);
}

/* 清空树实现 */
void Set::_clear(RBTNode* tree) {
    while(tree != NULL) {
        delete(tree->left);
        delete(tree->right);
        delete(tree);
    }
}

/* 判断数据是否存在接口 */
int Set::_count(const T& key) {
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
    return _size(root);
}

/* 计数 */
size_t Set::_size(RBTNode*  tree) {
    if (tree == NULL)
        return 0;
    else
        return 1 + _size(tree->left) + _size(tree->right);
}

/* ------内部操作函数部分------ */

/* 查找 */
RBTNode* Set::find(RBTNode* tree, const T& key) {
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

/* 查找最小数 */
RBTNode* Set::find_min(RBTNode* tree) {
    if (tree->left == NULL)
        return tree;
    else
        return find_min(tree->left);
}

/* 查找最大数 */
RBTNode* Set::find_max(RBTNode* tree) {
    if (tree->right == NULL)
        return tree;
    else
        return find_max(tree->right);
}

/* 返回单儿子时的儿子结点 */
RBTNode* Set::son(RBTNode* tree) {
    if (tree->left != NULL)
        return tree->left;
    else
        return tree->right;
}

/* 返回兄弟结点 */
RBTNode* Set::sibling(RBTNode* tree) {
    if (tree == tree->parent->left)
        return tree->parent->right;
    else
        return tree->parent->left;
}

/* 返回祖父结点 */
RBTNode* Set::grandparent(RBTNode* tree) {
    return tree->parent->parent;
}

/* 返回叔父结点 */
RBTNode* Set::uncle(RBTNode* tree) {
    RBTNode* g = grandparent(tree);
    if (tree->parent == g->left)
        return g->right;
    else
        return g->left;
}

/* 执行左旋 */
void Set::leftrotation(RBTNode* k1) {
    RBTNode *k2 = k1->right;
    RBTNode *p = k1->parent;
    RBTColor t = k1->color;
    k1->right = k2->left;
    k2->left->parent = k1;
    k2->left = k1;
    k1->parent = k2;
    k2->parent = p;
    k1->color = k2->color;
    k2->color = t;
}

/* 执行右旋 */
void Set::rightrotation(RBTNode* k1) {
    RBTNode *k2 = k1->left;
    RBTNode *p = k1->parent;
    RBTColor t = k1->color;
    k1->left = k2->right;
    k2->right->parent = k1;
    k2->right = k1;
    k1->parent = k2;
    k2->parent = p;
    k1->color = k2->color;
    k2->color = t;
}

/* 执行改色 */
void Set::changecolor(RBTNode* tree) {
    if (tree->color == BLACK && tree->left->color == RED && tree->right->color == RED) {
        tree->left->color = tree->right->color = BLACK;
        tree->color = RED;
    }
}

/* ------插入和删除的辅助函数部分------ */

/* 调整 */
void Set::insadjust(RBTNode* node) {
    if (node->parent->color == BLACK) { //若父结点为黑
        if(node == node->parent->right) //若以右儿子插入
            leftrotation(node->parent);
    }
    else { //若父结点为红
        if (node == node->parent->left) { //若以左儿子插入
            rightrotation(node->parent);
            changecolor(node->parent);
            insadjust(node->parent); //把node->parent视为刚插入的结点递归
        }
        else { //若以右儿子插入
            leftrotation(node->parent);
            rightrotation(node->parent);
            changecolor(node);
            insadjust(node); //把node视为刚插入的结点递归            
        }
        
    }
}

/* 删除调整一 */
void Set::del_adjust1(RBTNode* N) {
    if (N->parent != NULL) //若N不是根节点，进入情形二
        del_adjust2(N);
}

/* 删除调整二 */
void Set::del_adjust2(RBTNode* N) {
    RBTNode *S = sibling(N);
    RBTNode *P = N->parent;
    if (S != NULL && S->color == RED) { //若N的兄弟是红色
        rightrotation(P);
        P->color = BLACK;
        if (P->left != NULL)
            P->left->color = RED;
    }
    else
        del_adjust3(N);
}

/* 删除调整三 */
void Set::del_adjust3(RBTNode* N) {
    RBTNode *S = sibling(N);
    RBTNode *P = N->parent;
    if (P->color == BLACK && 
    (S->color == BLACK || S == NULL) &&
    (S->left->color == BLACK || S->left == NULL) &&
    (S->right->color == BLACK || S->right == NULL)) {
        if (P->left == N) { //若N是P的左儿子
            leftrotation(P);
            P->color = RED;
            del_adjust1(S);
        }
        else { //若N是P的右儿子
            if (S != NULL)
                S->color = RED;
            del_adjust1(P);
        }
    }
    else if (P->color == RED && 
    (S->color == BLACK || S == NULL) &&
    (S->left->color == BLACK || S->left == NULL) &&
    (S->right->color == BLACK || S->right == NULL)) {
        P->color = BLACK;
        S->color = RED;
        if (P->left == N) //若N是P的左儿子
            leftrotation(P);
    }
    else {
        if (P->left == N) { //若N是P的左儿子
            leftrotation(P);
            rightrotation(P);
            del_adjust4(S->right);
        }
        else //若N是P的右儿子
            del_adjust4(N);
    }
}

/* 删除调整四 */
void Set::del_adjust4(RBTNode* N) {
    RBTNode *S = sibling(N);
    RBTNode *P = N->parent;
    rightrotation(P);
    S->left->color = BLACK;
}