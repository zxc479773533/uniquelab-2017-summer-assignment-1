#ifndef PQ
#define PQ

/* 说明，该优先队列以数据表示优先级，数据越大，表示优先级越高 */
#include <iostream>
#include <algorithm>
#include <vector>

using T = double; //数据类型，本次任务要求使用double
using std::vector; //存储类型使用vector
using std::cout;
using std::endl; //测试用输出

class Priority_queue {
    public:
        bool empty() const; //判断队列是否为空
        size_t size() const; //返回队列中数据的个数
        const T& top() const; //返回队列的头部数据
        void push(const T& val); //在队列尾部增加一个数据
        void pop(); //队列头部的数据出队
    //析构函数
        ~Priority_queue() {PriQueue.resize(0);}
    private:
        vector<T> PriQueue; //存储类型vector
        int currentsize = 0; //属性：当前队列大小
};

#endif