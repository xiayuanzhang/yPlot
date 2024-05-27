#include "mybuoy.h"

MyBuoy::MyBuoy(QCustomPlot *plot)
{

    qcp = plot;

    label = new QLabel(qcp);
    // 设置 QLabel 的背景为半透明的白色
    label->setStyleSheet("background-color: rgba(255, 255, 255, 255);border: 1px solid black;");
    label->setFont(QFont("Helvetica",9));
    // label->setMargin(-5);
    label->setVisible(false);
    label->setAttribute(Qt::WA_TransparentForMouseEvents); //鼠标事件传递

    keyLine = new VerticalLine(qcp);
    keyLine->setWidth(2);
    keyLine->setLineStyle(Qt::DotLine);
    keyLine->setVisible(true);
    keyLine->setVisible(false);
    keyLine->setAttribute(Qt::WA_TransparentForMouseEvents); //鼠标事件传递
}

MyBuoy::~MyBuoy()
{

}


void MyBuoy::setEnable(QCPGraph *plot, bool en)
{
    syncGraphNums();
    for(int i = 0; i< qcp->graphCount();i++){
        if(qcp->graph(i) == plot){
            isShow.replace(i,en);
            return;
        }
    }
}

void MyBuoy::setAllEnable(bool en)
{
    syncGraphNums();
    for(int i = 0;i<isShow.size();i++){
        isShow[i] = en;
        //        qDebug()<<isShow[i];
    }
}

bool MyBuoy::isEnable(QCPGraph *plot)
{
    syncGraphNums();
    for(int i = 0; i< qcp->graphCount();i++){
        if(qcp->graph(i) == plot){
            return isShow.at(i);
        }
    }
    return false;
}

void MyBuoy::refresh()
{
    if(enshow == false){
        keyLine->setVisible(false);
        label->setVisible(false);
        return;
    }
    // 检测鼠标是否在当前窗口
    if (!qcp->underMouse()) {
        keyLine->setVisible(false);
        label->setVisible(false);
        return;
    }

    if(qcp->graphCount() < 1)
        return;

    syncGraphNums();

    //设置显示内容
    clearText();

    int showCount = 0;

    double xKey = qcp->axisRect(0)->axis(QCPAxis::atBottom,0)->pixelToCoord(pixelPos.x()); //X的值不是整数!
    qint64 intKey = qRound64(xKey);
    //qDebug()<<xKey;

    int xIndex = 0;
    if(xKey - intKey > 0)
        xIndex = qcp->graph(0)->findBegin(xKey,true); //遍历查找 = xKey的索引或者略小于xKey的索引. 如果没有等于或略小于xKey的值, 将会返回0
    else
        xIndex = qcp->graph(0)->findBegin(xKey,false); //遍历查找 = xKey的索引或者略大于xKey的索引. 如果没有等于或略大于xKey的值, 将会返回0
    //    qDebug()<<xIndex;


    QString nameMax = QString("X=%1").arg(intKey);

    appendText(nameMax,Qt::black);
    for(int i = 0;i<qcp->graphCount();i++){
        if(isShow.at(i) == false)
            continue;
        showCount++;
        QString name = qcp->graph(i)->name();

        int index = name.lastIndexOf(".", name.lastIndexOf(".") - 1); // get the index of the second last dot
        if (index != -1) {
            name.remove(index, name.length() - index); // remove everything after the second last dot
        }
        if(xIndex >= qcp->graph(i)->dataCount() -1){
            xIndex = qcp->graph(i)->dataCount() -1;
        }
        if(xIndex <= 0){
            xIndex = 0;
        }

        double value = qcp->graph(i)->data()->at(xIndex)->value; //这个value的问题.
        //qDebug()<<"xIndex = "<<xIndex<<", value ="<<value<<", all ="<< qcp->graph(i)->dataCount();
        name += QString("= %1").arg(value);
        appendText(name,qcp->graph(i)->pen().color()); //添加值到label

        if(nameMax.size() < name.size()){
            nameMax = name;
        }
    }
    QFontMetrics fontm(label->font());
    nameMax += "xx"; //字符占位,增加宽度
    int wid = fontm.width(nameMax);
    int hig = int((fontm.height() + fontm.height()*0.5) * (showCount+0.5));
    label->resize(wid,hig);

    QPoint pos = pixelPos.toPoint();

    keyLine->setLength(qcp->rect().height());
    keyLine->setPosition(pos.x(),0);

    label->move(pos.x() + 20,pos.y() + 20);

    keyLine->setVisible(true);
    label->setVisible(true);
}

void MyBuoy::syncGraphNums()
{
    int nums = isShow.size() - qcp->graphCount();
    if(isShow.size() != qcp->graphCount()){
        //        qDebug()<<"nums"<<nums;
        isShow.resize(qcp->graphCount());
        if(nums < 0){
            for(int i =0;i< isShow.length();i++){
                isShow[i] = true;
                //                qDebug()<<isShow[i] ;
            }
        }
    }
}
