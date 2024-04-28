#ifndef RINGQUEUE_H
#define RINGQUEUE_H

/**
 * @brief The RingQueue class
 * 1. 这是一个环形队列
 * 2. 该环形队列非线程安全
 * 3. 当队满时, push操作会被忽略
 * 4. 当队空时, pop操作会返回一个默认构造的T对象(具体内容由T的默认构造函数决定)
 */
template<typename T>
class RingQueue
{
public:
    explicit RingQueue(int size = 4096);
    ~RingQueue();

    void push(const T &value);
    T pop();
    int size() const;
    bool isEmpty() const;
    bool isFull() const;


    //查询相对head+offset处的字符是什么, nums表示要查询多少个
    bool query(int offset, T *buffer, int nums) const;

    //从head+offset开始, 检索buffer处于队列中的位置, 返回的是相对head的位置
    int index(int offset, T *buffer, int nums) const;


private:
    int m_size;
    int m_head;
    int m_tail;
    T *m_data;
};

#endif // RINGQUEUE_H
