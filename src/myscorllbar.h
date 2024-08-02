#ifndef MYSCORLLBAR_H
#define MYSCORLLBAR_H

#include <QObject>
#include <QScrollBar>

class MyScorllBar : public QObject
{
    Q_OBJECT
public:
    explicit MyScorllBar(QScrollBar *scrollbar = nullptr,QObject *parent = nullptr);

    /**
     * @brief setPageRange 设置当前窗口显示的范围
     * @param min watch窗口的Lower
     * @param max watch窗口的Upper
     * @note  通过换算之后, 滑动条范围为 (0 , rangMax), value在这个范围中
     */
    void setPageRange(int min, int max);

    /**
     * @brief setRange 设置滚动条的总范围
     * @param min 0
     * @param max bufferSize的大小
     */
    void setRange(int min, int max);

Q_SIGNALS:
    void sliderMoved(int min,int max);


private Q_SLOTS:
    /**
     * @brief slot_sliderMoved 当滚动条的值发生改变时发出该信号.
     * @param value
     */
    void slot_sliderMoved(int position);

private:
    QScrollBar *m_scrollBar;
    int m_rangeMin = 0;
    int m_rangeMax = 100;

    int m_valueMin = 0;
    int m_valueMax = 50;

    bool isPressed = false;
};

#endif // MYSCORLLBAR_H
