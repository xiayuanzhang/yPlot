#ifndef QSHADOWHELPER_H
#define QSHADOWHELPER_H

#include <QWidget>
class QPainter;

class QDrawShadowHelper : public QObject
{
    Q_OBJECT

    //Q_PROPERTY(QColor clientBgColor READ getClientBgColor WRITE setClientBgColor)

public:
    explicit QDrawShadowHelper(QWidget* w, int shadowSize = 10, QObject *parent = 0);
    ~QDrawShadowHelper();
    void setShadowSize(int shadowSize);
    void paint(QPainter* p);
    int shadowSize();

//    QColor getClientBgColor() const;
//    void setClientBgColor(const QColor &value);

    QColor getClientBorderColor() const;
    void setClientBorderColor(const QColor &value);

public slots:
    void hide();
    void show();
protected:
    QImage makeShadowImage(int shadowSize, bool activated);
    bool splitRect(const QRect &rcSrc, int shadowSize, QRect *parrayRect, int nArrayCount);
private:
    int m_shadowSize;
    QImage m_img;
    QRect m_arrayImageGrid[9];
    QColor m_clientBorderColor;
    QColor m_clientBgColor;
    QWidget *m_widget;
    bool m_show;
};

#endif // QSHADOWHELPER_H
