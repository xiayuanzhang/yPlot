#ifndef YFRAME_H
#define YFRAME_H

#include <QObject>
#include <QVector>
#include <QTimer>
#include "data/ringqueue.h"

#define ID_PLOTNAME 0x01
#define ID_PLOT 0x02
#define ID_INFO 0x03
#define ID_DEBUG  0x04
#define ID_WARING 0x05

#define ID_SENDCMD 0x10


typedef struct _YFrameType
{
    uint8_t id;
    uint16_t len;
    QByteArray data;

    //构造函数
    _YFrameType()
        : id{0}
        , len{0}
    {

    }
} YFrame_t;

/**
 * @brief The YFrame class 数据格式为
 * 0x55 id(u8) len(u16) data[0] data[1] ... data[len-1]
 */
class YFrame : public QObject
{
    Q_OBJECT
public:


    explicit YFrame(QObject *parent = nullptr);
    ~YFrame();
    void startAutoParse(int interval_ms = 10);
    void stopAutoParse();

    void clear();
    QVector<YFrame_t> parseData();
    void parseDataWithSignal();

    static QByteArray packData(const YFrame_t &frame);
    static QByteArray packData(uint8_t id, const QByteArray &data = {});
    static QByteArray packData(uint8_t id, const QString &data = {});
    static QByteArray packData(uint8_t id, uint8_t cmd);

    static QVector<float> byteArrayToFloat(const QByteArray &data);
    //以,分割的字符串转换为QVector<QString>
    static QVector<QString> byteArrayToQString(const QByteArray &data);
public slots:
    void receiveData(const QByteArray &data);

signals:
    //不使用引用, 方便可以在不同线程中使用
    void frameReceived(QVector<YFrame_t> frame);

private:
    QTimer *m_timer{nullptr};
    RingQueue<uint8_t> m_queue{1024*1024*10}; //10M缓存

};

#endif // YFRAME_H
