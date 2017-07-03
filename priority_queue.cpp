#include "priority_queue.h"

/* 交换两个数 */
void swap(double &u, double &v) {
    double t;
    t = u, u = v, v = t;
}

/* 判断队列是否为空,若为空，返回true */
bool Priority_queue::empty() const {
    if (PriQueue.size() == 0)
        return true;
    else
        return false;
}

/* 返回队列中数据的个数 */
size_t Priority_queue::size() const {
    return PriQueue.size();
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
    while (PriQueue[k] > PriQueue[(k - 1) / 2]) {
        swap(PriQueue[k], PriQueue[(k - 1) / 2]), k = (k - 1) / 2;
        if (k == 0)
            break;
    }
}

/* 队列头部的数据出队 */
void Priority_queue::pop() {
    if (PriQueue.size() != 0) {
        int m = 0, n, k = PriQueue.size() - 1; //k是最后一个位置的下标
        while (k >= 2 * m + 1) { //若不满足，则说明PriQueue[m]没有子结点
            if (k >= 2 * m + 2) { //若满足，则说明PriQueue[m]有两个子结点
                n = (PriQueue[2 * m + 1] >= PriQueue[2 * m + 2])? 2 * m  + 1 : 2 * m + 2;
                swap(PriQueue[m], PriQueue[n]);
                m = n;
            }
            else
                n = 2 * m  + 1, m = n;
        }
        swap(PriQueue[m], PriQueue[k]);
        PriQueue.pop_back();
    }
} 