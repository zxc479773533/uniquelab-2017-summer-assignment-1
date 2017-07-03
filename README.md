----------------
UniqueLab Summer Camp Assignment 0
---------------- 

**实现 C++ STL 中的 priority_queue 和 set. 无需实现template泛型，钦定类型为 T = double**
1. priorty_queue 需要实现 empty(), size(), top(), push(const T&), pop()方法
2. set 需要实现insert(const T&), erase(const T&), clear(), count(const T&), empty(), size(). 钦定数据结构内核为**左倾红黑树(LLRB)**

**所有接口以及功能参照 STL 文档**

本次任务时间仅一周，且部分新人C++需要重头学，因此无需实现迭代器, 大多数函数返回值改为void.

---华---丽---的---分---割---线---

7.2更新：优先队列算法总结已在个人github.io更新：

https://zxc479773533.github.io/algorithms/2017/07/02/Priority-Queue

7.3更新：
1. 修改了优先队列里面的一些问题，但对于大量的数据仍有些许bug.
2. 完成了二叉搜索树来进行练手.