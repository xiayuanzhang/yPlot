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


QVector<YFrame::YFrame_t> YFrame::parseData()
{
    QVector<YFrame_t> frames{};
    while(m_queue.size() >= 4)
    {

        uint8_t head = 0;
        m_queue.query(0,&head,1);
        if(head != 0x55)
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
        frames.append(frame);
    }
    return frames;
}


void YFrame::parseDataWithSignal()
{
    QVector<YFrame_t> frames = parseData();
    emit frameReceived(frames);
}

QByteArray YFrame::packData(const YFrame_t &frame)
{
    QByteArray data;
    data.append(0x55);
    data.append(frame.id);
    data.append((frame.len >> 8) & 0xFF);
    data.append(frame.len & 0xFF);
    data.append(frame.data);
    return data;
}

QByteArray YFrame::packData(int id, const QByteArray &data)
{
    YFrame_t frame;
    frame.id = id;
    frame.len = data.size();
    frame.data = data;
    return packData(frame);
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
    data.split(',').forEach([&result](const QByteArray &item){
        result.append(QString::fromUtf8(item));
    });
    return result;
}
