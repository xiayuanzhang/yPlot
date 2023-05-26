#include "dataanalysis.h"

dataAnalysis::dataAnalysis()
{

}


dataAnalysis::~dataAnalysis()
{

}

int dataAnalysis::getChannelNum()
{
    return m_plotNum;
}

//需要计算帧率

//显示丢包率

#include <QDebug>
#include <windows.h>
//需要让他可以一次性解析多帧数据,然后直接更新多帧数据
void dataAnalysis::inputDataStream(QByteArray stream)
{
#if 0
    LARGE_INTEGER litmp;
    LONGLONG Qpart1,Qpart2,Useingtime;
    double dfMinus,dfFreq,dfTime;


    //获得CPU计时器的时钟频率
    QueryPerformanceFrequency(&litmp);//取得高精度运行计数器的频率f,单位是每秒多少次（n/s），
    dfFreq = (double)litmp.QuadPart;

    QueryPerformanceCounter(&litmp);//取得高精度运行计数器的数值
    Qpart1 = litmp.QuadPart; //开始计时
   #endif

    //qDebug()<<stream.size();
    for(int i = 0;i<stream.size();i++)
    {
        if(mavlink_parse_char(MAVLINK_COMM_0, static_cast<uint8_t>(stream.at(i)), &msg, &status))
        {
            mavlink_plot_t mplot;
            mavlink_plotname_t mplotname;
            QVector<double> newData;
            switch(msg.msgid)
            {
                //获取曲线数据
            case MAVLINK_MSG_ID_PLOT:
                    /*
                    数据结构 : 通道<数据帧<double>> newdata
                    QVector<double> ch1 = ch1_p1,ch1_p2...
                    QVector<double> ch2 = ch2_p1,ch2_p2...
                    ...
                    ----------------------------------------
                    QVector<QVector<double>> data = ch1,ch2...
                    */
                    if(plotBuff.size() == 0){
                        plotBuff.resize(PLOT_NUM_MAX);
                    }
                    
                    mavlink_msg_plot_decode(&msg, &mplot);

                    if(mplot.plotNum <= PLOT_NUM_MAX && mplot.plotNum >=0)
                        m_plotNum = mplot.plotNum;
                    else if(mplot.plotNum >PLOT_NUM_MAX)  //超过最大通道数量设置为最大数量
                        m_plotNum = PLOT_NUM_MAX;

                    for ( int i = 0;i<m_plotNum;i++) {
                        plotBuff[i].append(static_cast<double>(mplot.plot[i]));
                    }
                break;
                //获取曲线名称
            case MAVLINK_MSG_ID_PLOTNAME:
                plotNameBuff.clear(); //清除上一帧,只保留当前帧
                mavlink_msg_plotname_decode(&msg, &mplotname);
                 plotNameBuff.append(QString::fromLocal8Bit(mplotname.plotName0));
                  plotNameBuff.append(QString::fromLocal8Bit(mplotname.plotName1));
                   plotNameBuff.append(QString::fromLocal8Bit(mplotname.plotName2));
                    plotNameBuff.append(QString::fromLocal8Bit(mplotname.plotName3));
                     plotNameBuff.append(QString::fromLocal8Bit(mplotname.plotName4));
                      plotNameBuff.append(QString::fromLocal8Bit(mplotname.plotName5));
                       plotNameBuff.append(QString::fromLocal8Bit(mplotname.plotName6));
                        plotNameBuff.append(QString::fromLocal8Bit(mplotname.plotName7));
                         plotNameBuff.append(QString::fromLocal8Bit(mplotname.plotName8));
                          plotNameBuff.append(QString::fromLocal8Bit(mplotname.plotName9));
                           plotNameBuff.append(QString::fromLocal8Bit(mplotname.plotName10));
                            plotNameBuff.append(QString::fromLocal8Bit(mplotname.plotName11));
                break;
            default:
                break;
            }
        }
    }


    //解析完成之后发送信号
    if(plotBuff.size()!=0)
    {
        emit haveNewData(plotBuff); //使用emit的时候会阻塞当前函数,转而执行槽函数
        plotBuff.clear(); //清空缓存
    }
    if(plotNameBuff.size()!=0)
    {
        emit haveNewName(plotNameBuff); //使用emit的时候会阻塞当前函数,转而执行槽函数
        plotNameBuff.clear();
    }
#if 0
    QueryPerformanceCounter(&litmp);//取得高精度运行计数器的数值
    Qpart2 = litmp.QuadPart; //终止计时

    dfMinus = (double)(Qpart2 - Qpart1);//计算计数器值
    dfTime = dfMinus / dfFreq;//获得对应时间，单位为秒,可以乘1000000精确到微秒级（us）
    Useingtime = dfTime*1000000;

    qDebug()<<"analysis"<<dfTime<<"s";
   #endif

        
}




