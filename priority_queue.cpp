#include "priority_queue.h"

/* 交换两个数 */
void swap(double &u, double &v) {
 double t;
 t = u, u = v, v = t;
}

/* 判断队列是否为空,若为空，返回true */
bool Priority_queue::empty() const {
  double e = 1e-6; //给定一个判断是否为0的精确度
  if (PriQueue[0] > e || PriQueue[0] < -e)
    return false;
  else
    return true;
}

/* 对二叉树进行深度优先搜索 */
size_t Priority_queue::DFS(int i) const {
  double e = 1e-6; //给定一个判断是否为0的精确度
  if (PriQueue[i] > e || PriQueue[i] < -e)
    return 1 + DFS(2 * i + 1) + DFS(2 * i + 2); //递归公式
  else
    return 0;
}

/* 返回队列中数据的个数 */
size_t Priority_queue::size() const {
  return this->DFS(0);
}

/* 返回队列的头部数据 */
const T& Priority_queue::top() const {
  return PriQueue[0];
}


/* 在队列尾部增加一个数据 */
void Priority_queue::push(const T& val) {
  int k;
  PriQueue.push_back(val);
  k = PriQueue.size() - 1; //k是新增的位置的下标
  while (PriQueue[k] > PriQueue[(k - 1) / 2])
    swap(PriQueue[k], PriQueue[(k - 1) / 2]), k = (k - 1) / 2;
}

/* 队列头部的数据出队 */
T Priority_queue::pop() {
  int m = 0, n, k = PriQueue.size() - 1;
  double end = PriQueue[k];
  while (PriQueue[2 * m + 1] || PriQueue[2 * m + 2]) {
    n = (PriQueue[2 * m + 1] >= PriQueue[2 * m + 2])? 2 * m  + 1 : 2 * m + 2;
    swap(PriQueue[m], PriQueue[n]);
    m = n;
  }
  swap(PriQueue[m], end);
  PriQueue[k] = 0;
  return end;
}