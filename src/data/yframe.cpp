#include "yframe.h"

YFrame::YFrame(QObject *parent)
    : QObject{parent}
{
    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, &YFrame::parseDataWithSignal);
}

YFrame::~YFrame()
{

}

void YFrame::startAutoParse(int interval_ms)
{
    m_timer->start(interval_ms);
}

void YFrame::stopAutoParse()
{
    m_timer->stop();
}

void YFrame::clear()
{
    m_queue.clear();
}

void YFrame::receiveData(const QByteArray &data)
{
    for(int i = 0; i < data.size(); i++)
    {
        m_queue.push(data.at(i));
    }
}


QVector<YFrame_t> YFrame::parseData()
{
    QVector<YFrame_t> fff{};
    QByteArray ad123;
    ad123.resize(1024);
    while(m_queue.size() >= 4)
    {
        m_queue.query(0,(uint8_t*)ad123.data(),1024);
        uint8_t head = 0;
        m_queue.query(0,&head,1);
        if(head != 0xAA)
        {
            m_queue.pop();
            continue;
        }
        uint16_t len = 0;
        m_queue.query(2, (uint8_t*)&len, 2);
        if(m_queue.size() < len + 4)
            break;

        YFrame_t frame;

        m_queue.pop(); //删除帧头 0x55
        frame.id = m_queue.pop(); //取出id
        frame.len = len;
        m_queue.pop(); //删除数据长度
        m_queue.pop(); //删除数据长度

        //取出数据
        for(int i = 0; i < len; i++)
        {
            frame.data.append(m_queue.pop());
        }
        fff.append(frame);
    }
    return fff;
}


void YFrame::parseDataWithSignal()
{
    QVector<YFrame_t> frames = parseData();
    if(frames.size() > 0)
        emit frameReceived(frames);
}

QByteArray YFrame::packData(const YFrame_t &frame)
{
    QByteArray data;
    data.append(0xAA);
    data.append(frame.id);
    data.append(frame.len & 0xFF);
    data.append((frame.len >> 8) & 0xFF);
    data.append(frame.data);
    return data;
}

QByteArray YFrame::packData(uint8_t id, const QByteArray &data)
{
    YFrame_t frame;
    frame.id = id;
    frame.len = data.size();
    frame.data = data;
    return packData(frame);
}

QByteArray YFrame::packData(uint8_t id, uint8_t cmd)
{
    QByteArray data;
    data.append(cmd);
    return packData(id, data);
}

QVector<float> YFrame::byteArrayToFloat(const QByteArray &data)
{
    QVector<float> result;
    for(int i = 0; i < data.size(); i += 4)
    {
        float value;
        memcpy(&value, data.data() + i, 4);
        result.append(value);
    }
    return result;
}

QVector<QString> YFrame::byteArrayToQString(const QByteArray &data)
{
    QVector<QString> result;
    QByteArrayList dataList = data.split(',');
    for(int i =0;i<dataList.size();++i){
        result.append(QString::fromUtf8(dataList[i]));
    }
    return result;
}
