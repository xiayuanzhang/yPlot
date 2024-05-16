#ifndef MYSCORLLBAR_H
#define MYSCORLLBAR_H

#include <QObject>
#include <QScrollBar>

class MyScorllBar : public QObject
{
    Q_OBJECT
public:
    explicit MyScorllBar(QScrollBar *scrollbar = nullptr,QObject *parent = nullptr);

    void setValueRange(int min, int max);
    void setRange(int min, int max);

Q_SIGNALS:
    void valueChanged(int value);


private Q_SLOTS:
    void slot_valueChanged(int value);

private:
    QScrollBar *m_scrollBar;
    int m_rangeMin = 0;
    int m_rangeMax = 100;

    int m_valueMin = 0;
    int m_valueMax = 50;
};

#endif // MYSCORLLBAR_H
