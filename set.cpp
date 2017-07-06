#include "set.h"

/* ------接口与主要操作部分------ */

/* 插入指定的结点接口 */
void Set::insert(const T& key) {
    RBTNode* new_node = new RBTNode(RED, key, NULL, NULL, NULL);
    if (root == NULL)
        root = new_node;
    else
        ins(root, new_node);
    insadjust(new_node);
}

/* 插入指定的结点实现 */
void Set::ins(RBTNode* tree, RBTNode* node) {
    RBTNode *p = tree, *pre = NULL;
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
            delete(p);
        }
    }
}

/* 删除指定的结点接口 */
void Set::erase(const T& key) {
    RBTNode *node = find(root, key);
    if (node != NULL)
        del(node);
}

/* 删除指定的结点实现 */
void Set::del(RBTNode* node) {
    if (node->left != NULL && node->left != NULL) { //若要删除的结点有两个子结点
        RBTNode *max = find_max(node->left);
        node->key = max->key;
        del(max);
    }
    else { //其他情况，若是叶子把一个NULL当做儿子
        RBTNode *P = node->parent; //父结点
        RBTNode *N = son(node); //儿子结点
        RBTColor N_color = (N != NULL)? N->color : BLACK; //儿子结点颜色，空结点当做黑色
        if (node->color == RED) { //若要删除的结点为红
            replace(node, N); //用N替换该结点
            if (N != NULL)
                N->parent = P;
            delete(node);
        }
        else if (node->color == BLACK && N_color == RED) { //若要删除的结点为黑，其儿子为红
            N->color = BLACK; //将其变成黑
            replace(node, N); //用N替换该结点
            N->parent = P; //此时N一定非空
            delete(node);
        }
        else { //若该结点和N均为黑色(N可能为NULL)
            replace(node, N); //用N替换该结点            
            if (N != NULL) {
                N->parent = P;
                del_adjust1(N); //进入情形一
            }
            delete(node);
        }
    }
}

/* 清空树接口 */
void Set::clear() {
    _clear(root);
    root = NULL;
}

/* 清空树实现 */
void Set::_clear(RBTNode* tree) {
    if (tree->left != NULL)
        _clear(tree->left);
    else if (tree->right != NULL)
        _clear(tree->right);
    delete(tree);
    tree = NULL;
}

/* 判断数据是否存在接口 */
int Set::count(const T& key) const {
    return _count(key);
}

/* 判断数据是否存在实现 */
int Set::_count(const T& key) const{
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
RBTNode* Set::find(RBTNode* tree, const T& key) const{
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
    if (k2->left != NULL)
        k2->left->parent = k1;
    k2->left = k1;
    k1->parent = k2;
    if (p != NULL && p->left == k1)
        p->left = k2;
    else if (p != NULL && p->right == k1)
        p->right = k2;
    k2->parent = p;
    k1->color = k2->color;
    k2->color = t;
    if (k1 == root)
        root = k2;
}

/* 执行右旋 */
void Set::rightrotation(RBTNode* k1) {
    RBTNode *k2 = k1->left;
    RBTNode *p = k1->parent;
    RBTColor t = k1->color;
    k1->left = k2->right;
    if (k2->right != NULL)
        k2->right->parent = k1;
    k2->right = k1;
    k1->parent = k2;
    if (p != NULL && p->left == k1)
        p->left = k2;
    else if (p != NULL && p->right == k1)
        p->right = k2;
    k2->parent = p;
    k1->color = k2->color;
    k2->color = t;
    if (k1 == root)
        root = k2;
}

/* 执行改色 */
void Set::changecolor(RBTNode* tree) {
    if (tree != root) {
        if (tree->color == BLACK && tree->left->color == RED && tree->right->color == RED) {
            tree->left->color = tree->right->color = BLACK;
            tree->color = RED;
        }
    }
    else
        tree->left->color = tree->right->color = BLACK;
}

/* ------插入和删除的辅助函数部分------ */

/* 插入调整 */
void Set::insadjust(RBTNode* node) {
    if (node->parent == NULL) //若是根结点
        node->color = BLACK;
    else {
        if (node->parent->color == BLACK) { //若父结点为黑
            if(node == node->parent->right) {
                if (sibling(node) == NULL || sibling(node)->color == BLACK)
                    leftrotation(node->parent);
                else {
                    changecolor(node->parent);
                    insadjust(node->parent);
                }
            }
        }
        else { //若父结点为红
            if (node == node->parent->left) { //若以左儿子插入
                rightrotation(grandparent(node));
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
}

/* 结点替换 */
void Set::replace(RBTNode* node, RBTNode* N) {
    RBTNode *P = node->parent; //父结点    
    if (P == NULL) { //若要被换掉的是根结点
        if (N != NULL)
            N->parent = NULL;
        root = N;
    }
    else {
        if (P->left == node)
            P->left = N;
        else
            P->right = N;
    }
}

/* 删除调整一 */
void Set::del_adjust1(RBTNode* N) {
    if (N != root) //若N不是根节点，进入情形二
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
    if (S == NULL) //S为空时直接向上一步递归
        del_adjust1(P);
    else if (P->color == BLACK && 
    (S->color == BLACK) &&
    (S->left == NULL || S->left->color == BLACK) &&
    (S->right == NULL || S->right->color == BLACK)) { //P为红，S为黑，且S的左右儿子为空或者为黑
        if (P->left == N) { //若N是P的左儿子
            leftrotation(P);
            P->color = RED;
            del_adjust1(S);
        }
        else { //若N是P的右儿子
            S->color = RED;
            del_adjust1(P);
        }
    }
    else if ((P->color == RED) && (S->color == BLACK) &&
    (S->left == NULL || S->left->color == BLACK) &&
    (S->right == NULL || S->right->color == BLACK)) { //P为红，S为黑，且S的左右儿子为空或者为黑
        P->color = BLACK;
        S->color = RED;
        if (P->left == N) //若N是P的左儿子
            leftrotation(P); 
    }
    else if ((P->color == RED) && (S->color == BLACK) &&
    (S->left != NULL && S->left->color == RED) &&
    (S->right == NULL || S->right->color == BLACK)) { //P为红，S为黑，且S的左儿子为红，右儿子为空或者为黑
        if (P->left == N) { //若N是P的左儿子
            leftrotation(P);
            leftrotation(P);
            if (S->right != NULL)
                del_adjust4(S->right);
        }
        else //若N是P的右儿子
            del_adjust4(N);
    }
    else if ((P->color == BLACK) && (S->color == BLACK) &&
    (S->left != NULL && S->left->color == RED) &&
    (S->right == NULL || S->right->color == BLACK)) { //P为黑，S为黑，且S的左儿子为红，右儿子为空或者为黑
        if (P->left == N) { //若N是P的左儿子
            leftrotation(P);
            leftrotation(P);
            if (S->right != NULL)
                del_adjust5(S->right);
        }
        else //若N是P的右儿子
            del_adjust5(N);
    }
}

/* 删除调整四 */
void Set::del_adjust4(RBTNode* N) {
    RBTNode *S = sibling(N);
    RBTNode *P = N->parent;
    rightrotation(P);
    S->left->color = BLACK;
}

/* 删除调整五 */
void Set::del_adjust5(RBTNode* N) {
    RBTNode *S = sibling(N);
    RBTNode *P = N->parent;
    rightrotation(P);
    S->left->color = BLACK;
}