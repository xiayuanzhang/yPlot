#ifndef YFRAME_H
#define YFRAME_H

#include <QObject>
#include <QVector>
#include "ringqueue.h"

/**
 * @brief The YFrame class 数据格式为
 * 0x55 id(u8) len(u16) data[0] data[1] ... data[len-1]
 */
class YFrame : public QObject
{
    Q_OBJECT
public:
    typedef struct _YFrameType
    {
        int id;
        int len;
        QByteArray data;

        //构造函数
        _YFrameType()
            : id{0}
            , len{0}
        {

        }
    } YFrame_t;

    explicit YFrame(QObject *parent = nullptr);


    QVector<YFrame_t> parseData();
    void parseDataWithSignal();

    QByteArray packData(const YFrame_t &frame);
    QByteArray packData(int id, const QByteArray &data = {});

public slots:
    void receiveData(const QByteArray &data);

signals:
    //不使用引用, 方便可以在不同线程中使用
    void frameReceived(QVector<YFrame_t> frame);

private:
    RingQueue<uint8_t> m_queue{1024*1024*10}; //10M缓存

};

#endif // YFRAME_H
