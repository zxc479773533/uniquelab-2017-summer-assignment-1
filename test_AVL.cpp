#include "AVL_tree.h"

int main() {
/* AVL tree */
    AVL_tree a;
    a.Insert(5);
    cout << a.Height() << endl;
    a.Insert(2);
    cout << a.Height() << endl;
    a.Insert(8);
    cout << a.Height() << endl;
    a.Insert(1);
    cout << a.Height() << endl;
    a.Insert(4);
    cout << a.Height() << endl;
    a.Insert(7);
    cout << a.Height() << endl;
    a.Insert(3);
    cout << a.Height() << endl;
    cout << "----------------" << endl;
    a.Delete(5);
    cout << a.Height() << endl;
    a.Delete(2);
    cout << a.Height() << endl;
    a.Delete(7);
    cout << a.Height() << endl;
    a.Delete(1);
    cout << a.Height() << endl;
    a.Delete(4);
    cout << a.Height() << endl;
    a.Delete(9);
    cout << a.Height() << endl;
    a.Delete(6);
    cout << a.Height() << endl;
    a.Delete(8);
    cout << a.Height() << endl;
    a.Delete(3);
    cout << a.Height() << endl;    
    return 0;
}