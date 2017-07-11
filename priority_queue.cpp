#include "priority_queue.h"

/* 判断队列是否为空,若为空，返回true */
bool Priority_queue::empty() const {
    return !currentsize;
}

/* 返回队列中数据的个数 */
size_t Priority_queue::size() const {
    return currentsize;
}

/* 返回队列的头部数据 */
const T& Priority_queue::top() const {
        return PriQueue[1];
}

/* 在队列尾部增加一个数据 */
void Priority_queue::push(const T& val) {
    if (PriQueue.size() == 0)
        PriQueue.resize(1);
    if (currentsize == PriQueue.size() - 1) //重新分配空间
        PriQueue.resize(PriQueue.size() * 2);
    int k = ++currentsize; //k是新的空位置
    for ( ; k > 1 && val > PriQueue[k / 2]; k /= 2)
        PriQueue[k] = PriQueue[k / 2]; //上滤，把空位置上移
    PriQueue[k] = val; //插入新值
}

/* 队列头部的数据出队 */
void Priority_queue::pop() {
    if (empty())
        cout << "This priority queue is empty!" << endl;
    else {
        int i, child; //child是i的子结点序号
        T temp = PriQueue[currentsize--]; //将最后一个位置的值储存
        for (i = 1; i * 2 <= currentsize; i = child) {
            child = i * 2;
            if (child != currentsize && PriQueue[child] < PriQueue[child + 1]) //选择大的子结点
                child++;
            if (temp < PriQueue[child]) //下虑，把空位置下移
                PriQueue[i] = PriQueue[child];
            else
                break;
        }
        PriQueue[i] = temp;
    }
}