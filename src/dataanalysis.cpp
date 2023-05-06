﻿#include "dataanalysis.h"

dataAnalysis::dataAnalysis()
{

}


dataAnalysis::~dataAnalysis()
{

}

int dataAnalysis::getChannelNum()
{
    return channels;
}

//需要计算帧率

//显示丢包率


void dataAnalysis::inputDataStream(QByteArray stream)
{
    qDebug()<<stream.size();
    for(int i = 0;i<stream.size();i++)
    {
        if(mavlink_parse_char(MAVLINK_COMM_0, static_cast<uint8_t>(stream.at(i)), &msg, &status))
        {
            QVector<double> newData;
            QVector<QString> newName;
            char *namebuff;

            mavlink_plot_t mplot;
            mavlink_plotname_t mplotname;
            switch(msg.msgid)
            {
            case MAVLINK_MSG_ID_PLOT:
                    mavlink_msg_plot_decode(&msg, &mplot);
                    if(mplot.plotNum <= PLOT_NUM_MAX && mplot.plotNum >=0)
                        channels = mplot.plotNum;
                    else if(mplot.plotNum >PLOT_NUM_MAX)
                        channels = PLOT_NUM_MAX;

                    for ( int i = 0;i<channels;i++) {
                        newData.append(static_cast<double>(mplot.plot[i]));
                    }
                    emit haveNewData(newData);
                break;
            case MAVLINK_MSG_ID_PLOTNAME:

                mavlink_msg_plotname_decode(&msg, &mplotname);
                namebuff = reinterpret_cast<char*>(&mplotname);

                for ( int i = 0;i<PLOT_NUM_MAX;i++) {
                    namebuff += i*PLOT_NAME_MAXLEN;
                    newName.append(namebuff);
                }
                emit haveNewName(newName);
                break;
            default:
                break;
            }
        }
    }
}




