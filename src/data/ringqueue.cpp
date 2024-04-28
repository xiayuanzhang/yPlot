#include "ringqueue.h"

template<typename T>
RingQueue<T>::RingQueue(int size)
    : m_size{size}
    , m_head{0}
    , m_tail{0}
    , m_data{new T[size]}
{

}

template<typename T>
RingQueue<T>::~RingQueue()
{
    delete[] m_data;
}

template<typename T>
void RingQueue<T>::push(const T &value)
{
    if(isFull())
        return;

    m_data[m_tail] = value;
    m_tail = (m_tail + 1) % m_size;
}

template<typename T>
T RingQueue<T>::pop()
{
    if(isEmpty())
        return T{};

    T value = m_data[m_head];
    m_head = (m_head + 1) % m_size;
    return value;
}

template<typename T>
int RingQueue<T>::size() const
{
    return (m_tail - m_head + m_size) % m_size;
}

template<typename T>
bool RingQueue<T>::isEmpty() const
{
    return m_head == m_tail;
}

template<typename T>
bool RingQueue<T>::isFull() const
{
    return (m_tail + 1) % m_size == m_head;
}

template<typename T>
void RingQueue<T>::clear()
{
    m_head = m_tail = 0;
}

template<typename T>
bool RingQueue<T>::query(int offset, T *buffer, int nums) const
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

template<typename T>
int RingQueue<T>::index(int offset, T *buffer, int nums) const
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
