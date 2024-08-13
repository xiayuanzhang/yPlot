#include "plotdemo.h"
#include <qmath.h>
#include "data/yframe.h"

PlotDemo::PlotDemo(QObject *parent)
: QObject(parent)
{
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &PlotDemo::update);
}

void PlotDemo::start(int interval_ms)
{
    timer->start(interval_ms);
}

void PlotDemo::stop()
{
    timer->stop();
}



void PlotDemo::update()
{
    m_count += 0.01;
    for(int i = 0;i<6;++i)
    {
        m_ch[i] = qSin(m_count + i*0.5) * 100;
        if(i % 2 == 0){
            m_ch[i] = m_ch[i] * 3;
        }
    }
    QByteArray data;
    data.resize(24);
    //拷贝数据
    memcpy(data.data(), m_ch, 24);
    QByteArray sendbuff = YFrame::packData(YPLOT_ID_PLOT, data);
    emit readyRead(sendbuff);
}
