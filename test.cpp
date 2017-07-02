#include<iostream>
#include "set.h"
#include "priority_queue.h"

int main() {
/* test for priority_queue */
  Priority_queue a;
  /* 测试数据选自算法导论6.5-1 */
  /* push测试 */
  a.push(15);
  a.push(13);
  a.push(9);
  a.push(5);
  a.push(12);
  a.push(8);
  a.push(7);
  a.push(4);
  a.push(0);
  a.push(6);
  a.push(2);
  a.push(1);
  /* top和size测试 */
  cout << "Top:" << a.top() << ", Size:" << a.size() << endl;
  /* pop测试 */
  cout << "Top:" << a.pop() << ", Now size:" << a.size() << endl;
  cout << "Top:" << a.pop() << ", Now size:" << a.size() << endl;
  cout << "Top:" << a.pop() << ", Now size:" << a.size() << endl;
  cout << "Top:" << a.pop() << ", Now size:" << a.size() << endl;
  cout << "Top:" << a.pop() << ", Now size:" << a.size() << endl;
  cout << "Top:" << a.pop() << ", Now size:" << a.size() << endl;
  cout << "Top:" << a.pop() << ", Now size:" << a.size() << endl;
  /* empty测试 */
  cout << "Top:" << a.pop() << ", Isempty:" << a.empty() << endl;
  cout << "Top:" << a.pop() << ", Isempty:" << a.empty() << endl;
  cout << "Top:" << a.pop() << ", Isempty:" << a.empty() << endl;
  cout << "Top:" << a.pop() << ", Isempty:" << a.empty() << endl;
  cout << "Top:" << a.pop() << ", Isempty:" << a.empty() << endl;
  cout << "Top:" << a.pop() << ", Isempty:" << a.empty() << endl;
  cout << "Top:" << a.pop() << ", Isempty:" << a.empty() << endl;
  
/* test for red-black-tree */
  
    return 0;
}