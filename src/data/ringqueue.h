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
    explicit RingQueue(int size = 4096)
        : m_size{size}
        , m_head{0}
        , m_tail{0}
        , m_data{new T[size]}
    {

    }


    ~RingQueue()
    {
        delete[] m_data;
    }

    void push(const T &value)
    {
        if(isFull())
            return;

        m_data[m_tail] = value;
        m_tail = (m_tail + 1) % m_size;
    }

    T pop() //出队
    {
        if(isEmpty())
            return T{};

        T value = m_data[m_head];
        m_head = (m_head + 1) % m_size;
        return value;
    }

    int size() const
    {
        return (m_tail - m_head + m_size) % m_size;
    }


    bool isEmpty() const
    {
        return m_head == m_tail;
    }

    bool isFull() const
    {
        return (m_tail + 1) % m_size == m_head;
    }

    void clear()
    {
        m_head = m_tail = 0;
    }


    //查询相对head+offset处的字符是什么, nums表示要查询多少个
    bool query(int offset, T *buffer, int nums) const
    {
        if(nums <= 0 || offset < 0)
            return false;
        if(offset + nums > size())
            return false;

        for(int i = 0; i < nums; ++i)
        {
            buffer[i] = m_data[(m_head + offset + i) % m_size];
        }

        return true;
    }

    //从head+offset开始, 检索buffer处于队列中的位置, 返回的是相对head的位置
    int index(int offset, T *buffer, int nums) const
    {
        if(nums <= 0 || offset < 0)
            return -1;
        if(offset + nums > size())
            return -1;

        //检索整个队列中 和buffer 完全一致的数据相对head的位置
        for(int i = m_head + offset; i < size(); ++i) //m_head + offset开始,检索到队列末尾
        {
            bool isMatch = true;
            for(int j = 0; j < nums; ++j) //连续检索buffer的数据, 长度为nums
            {
                if(m_data[(m_head + i + j) % m_size] != buffer[j])
                {
                    isMatch = false;
                    break;
                }
            }
            if(isMatch) //找到了
                return i - m_head; //返回相对head的位置
        }
        return -1;
    }


private:
    int m_size;
    int m_head;
    int m_tail;
    T *m_data;
};

#endif // RINGQUEUE_H
