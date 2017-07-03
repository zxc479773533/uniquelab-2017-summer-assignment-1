#include "binary_search_tree.h"

int main() {
/* binary search tree */
    Binary_search_tree a;
    /* 测试数据选自数据结构于算法分析图4-15 */
    /* Insert测试 */
    a.Insert(6);
    a.Insert(2);
    a.Insert(8);
    a.Insert(1);
    a.Insert(4);
    a.Insert(3);
    /* Find测试 */
    BSTNode *b = a.Find(2);
    cout << "Now let's find 2 in our tree." << endl;
    cout << "b:" << b->key << endl;
    cout << "b->left:" << b->left->key << endl;
    cout << "b->right:" << b->right->key << endl;
    cout << "b->parent:" << b->parent->key << endl;
    /* FindMax和FindMix测试 */
    cout << "Max:" << a.FindMax()->key << endl;
    cout << "Min:" << a.FindMin()->key << endl;
     /* MakeEmpty测试 */
    a.MakeEmpty();
    cout << "Max:" << a.FindMax()->key << endl;
    cout << "Min:" << a.FindMin()->key << endl;
    /* Delete测试 */
    a.Insert(6);
    a.Insert(2);
    a.Insert(8);
    a.Insert(1);
    a.Insert(4);
    a.Insert(3);
    a.Delete(8);
    a.Delete(1);
    cout << "Max:" << a.FindMax()->key << endl;
    cout << "Min:" << a.FindMin()->key << endl;
    return 0;
}