#include "myscorllbar.h"
#include <QDebug>

MyScorllBar::MyScorllBar(QScrollBar *scrollbar, QObject *parent)
    : QObject{parent}
    , m_scrollBar{scrollbar}
{
    connect(m_scrollBar, &QScrollBar::sliderMoved, this, &MyScorllBar::slot_sliderMoved);
    connect(m_scrollBar, &QScrollBar::sliderPressed,this, [this](){isPressed = true;});
    connect(m_scrollBar, &QScrollBar::sliderReleased,this, [this](){isPressed = false;});
}

void MyScorllBar::setPageRange(int min, int max)
{
    if(isPressed)
        return;
    m_valueMin = min;
    m_valueMax = max;
    int w = 0;
    //占满
    if(m_valueMin <=  m_rangeMin && m_valueMax >= m_rangeMax){
        m_scrollBar->setRange(m_rangeMin,m_rangeMax);
        m_scrollBar->setPageStep(m_rangeMax - m_rangeMin);
        m_scrollBar->setValue(m_rangeMin);
    } else if(m_valueMin < m_rangeMin){ //左边超出边界
        if(m_valueMax < m_rangeMin){
            w = (m_rangeMax - m_rangeMin) /10;
            m_scrollBar->setRange(m_rangeMin,m_rangeMax-w);
            m_scrollBar->setPageStep(w);
        }else{
            w = m_valueMax - m_rangeMin;
            m_scrollBar->setRange(m_valueMin,m_rangeMax-w);
            m_scrollBar->setPageStep(w);
        }
        m_scrollBar->setValue(m_rangeMin);
    }else if(m_valueMax > m_rangeMax){  //右边超出边界
        if(m_valueMin > m_rangeMax){
            w = (m_rangeMax - m_rangeMin) /10;
            m_scrollBar->setRange(m_rangeMin,m_rangeMax-w);
            m_scrollBar->setPageStep(w);
        }else{
            w = m_rangeMax - m_valueMin;
            m_scrollBar->setRange(m_valueMin,m_rangeMax-w);
            m_scrollBar->setPageStep(w);
        }
        m_scrollBar->setValue(m_rangeMax-w);
    }
    //PageStep = 视窗宽度
    //value = 视窗lower
    //value+PageSetp = 视窗upper
    w = m_valueMax - m_valueMin;
    m_scrollBar->setRange(m_rangeMin, m_rangeMax - w);
    m_scrollBar->setPageStep(w);
    m_scrollBar->setValue(m_valueMin);
}


void MyScorllBar::setRange(int min, int max)
{
    if(isPressed)
        return;
    int width = m_valueMax - m_valueMin;
    m_rangeMin = min;
    m_rangeMax = max;

    m_scrollBar->setRange(m_rangeMin, m_rangeMax - width);  //真实范围是最大值减去page值
}


void MyScorllBar::slot_sliderMoved(int position)
{
    Q_UNUSED(position);
    int value = m_scrollBar->value();
    emit sliderMoved(value , value+m_scrollBar->pageStep());
}
