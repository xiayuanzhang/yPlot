#include <QVBoxLayout>
#include <QPainter>
#include <QMap>
#include <QMainWindow>
#include "qshadowhelper.h"

QDrawShadowHelper::QDrawShadowHelper(QWidget* w, int shadowSize, QObject *parent)
    : QObject(parent)
    , m_shadowSize(shadowSize)
    , m_clientBorderColor(QColor("#C9C9C9"))
    , m_widget(w)
    , m_show(true)
{
    m_widget->setAttribute(Qt::WA_TranslucentBackground);
    //m_widget->setWindowFlags(m_widget->windowFlags() | Qt::FramelessWindowHint);
    m_clientBgColor = m_widget->palette().color(QPalette::Window);
    setShadowSize(m_shadowSize);
}

QDrawShadowHelper::~QDrawShadowHelper()
{

}

void QDrawShadowHelper::setShadowSize(int shadowSize)
{
    m_shadowSize = shadowSize;
    if (!m_img.isNull()) {
        m_img = QImage();
    }
    m_img = makeShadowImage(m_shadowSize, true);
    int nImageWidth = m_img.width();
    int nImageHeight = m_img.height();
    splitRect(QRect(0, 0, nImageWidth, nImageHeight), shadowSize, m_arrayImageGrid, 9);
}

inline unsigned char MakeAlpha(int i, double f, int nSize)
{
    if (i == nSize)
        f *= 1.2;
    double f2 = 1 - cos((double)i / nSize * 3.14 / 2);
    return int(fabs((i * f) * f2));
}

QImage QDrawShadowHelper::makeShadowImage(int shadowSize, bool activated)
{
    int size = shadowSize * 2 + 10;
    QImage image(size, size, QImage::Format_ARGB32);
    image.fill(QColor(Qt::black));

    //
    double f = activated ? 4.0 : 1.0;
    //
    QSize szImage = image.size();
    //
    //left
    for (int y = shadowSize; y < szImage.height() - shadowSize; y++) {
        for (int x = 0; x < shadowSize; x++) {
            int i = x + 1;
            int alpha = MakeAlpha(i, f, shadowSize);

#if (QT_VERSION <= QT_VERSION_CHECK(5,6,0))
            image.setPixel(x, y, QColor(0, 0, 0, alpha).rgba());
#else
            image.setPixelColor(x, y, QColor(0, 0, 0, alpha));
#endif

        }
    }
    //right
    for (int y = shadowSize; y < szImage.height() - shadowSize; y++) {
        for (int x = szImage.width() - shadowSize - 1; x < szImage.width(); x++) {
            int i = szImage.width() - x;
            int alpha = MakeAlpha(i, f, shadowSize);
#if (QT_VERSION <= QT_VERSION_CHECK(5,6,0))
            image.setPixel(x, y, QColor(0, 0, 0, alpha).rgba());
#else
            image.setPixelColor(x, y, QColor(0, 0, 0, alpha));
#endif
        }
    }
    //top
    for (int y = 0; y < shadowSize; y++) {
        int i = y + 1;
        for (int x = shadowSize; x < szImage.width() - shadowSize; x++) {
            int alpha = MakeAlpha(i, f, shadowSize);
#if (QT_VERSION <= QT_VERSION_CHECK(5,6,0))
            image.setPixel(x, y, QColor(0, 0, 0, alpha).rgba());
#else
            image.setPixelColor(x, y, QColor(0, 0, 0, alpha));
#endif
        }
        //
    }
    //bottom
    for (int y = szImage.height() - shadowSize - 1; y < szImage.height(); y++) {
        int i = szImage.height() - y;
        for (int x = shadowSize; x < szImage.width() - shadowSize; x++) {
            int alpha = MakeAlpha(i, f, shadowSize);
#if (QT_VERSION <= QT_VERSION_CHECK(5,6,0))
            image.setPixel(x, y, QColor(0, 0, 0, alpha).rgba());
#else
            image.setPixelColor(x, y, QColor(0, 0, 0, alpha));
#endif
        }
    }

    //
    int parentRoundSize = 0;
    //
    for (int x = 0; x < shadowSize + parentRoundSize; x++) {
        for (int y = 0; y < shadowSize + parentRoundSize; y++) {
            int xx = (shadowSize + parentRoundSize) - x;
            int yy = (shadowSize + parentRoundSize) - y;
            int i = int(sqrt(double(xx * xx + yy * yy)));
            i = std::min<int>(shadowSize + parentRoundSize, i);
            i -= parentRoundSize;
            i = shadowSize - i;
            //
            int alpha = MakeAlpha(i, f, shadowSize);
#if (QT_VERSION <= QT_VERSION_CHECK(5,6,0))
            image.setPixel(x, y, QColor(0, 0, 0, alpha).rgba());
#else
            image.setPixelColor(x, y, QColor(0, 0, 0, alpha));
#endif
        }
    }

    //
    for (int x = szImage.width() - shadowSize - parentRoundSize; x < szImage.width(); x++) {
        for (int y = 0; y < shadowSize + parentRoundSize; y++) {
            int xx = (shadowSize + parentRoundSize) - (szImage.width() - x);
            int yy = (shadowSize + parentRoundSize) - y;
            int i = int(sqrt(double(xx * xx + yy * yy)));
            i = std::min<int>(shadowSize + parentRoundSize, i);
            i -= parentRoundSize;
            i = shadowSize - i;
            //
            int alpha = MakeAlpha(i, f, shadowSize);
#if (QT_VERSION <= QT_VERSION_CHECK(5,6,0))
            image.setPixel(x, y, QColor(0, 0, 0, alpha).rgba());
#else
            image.setPixelColor(x, y, QColor(0, 0, 0, alpha));
#endif
        }
    }
    //
    for (int x = 0; x < shadowSize + parentRoundSize; x++) {
        for (int y = szImage.height() - shadowSize - parentRoundSize; y < szImage.height(); y++) {
            int xx = (shadowSize + parentRoundSize) - x;
            int yy = (shadowSize + parentRoundSize) - (szImage.height() - y);
            int i = int(sqrt(double(xx * xx + yy * yy)));
            i = std::min<int>(shadowSize + parentRoundSize, i);
            i -= parentRoundSize;
            i = shadowSize - i;
            //
            int alpha = MakeAlpha(i, f, shadowSize);
#if (QT_VERSION <= QT_VERSION_CHECK(5,6,0))
            image.setPixel(x, y, QColor(0, 0, 0, alpha).rgba());
#else
            image.setPixelColor(x, y, QColor(0, 0, 0, alpha));
#endif
        }
    }
    //
    for (int x = szImage.width() - shadowSize - parentRoundSize; x < szImage.width(); x++) {
        for (int y = szImage.height() - shadowSize - parentRoundSize; y < szImage.height(); y++) {
            int xx = (shadowSize + parentRoundSize) - (szImage.width() - x);
            int yy = (shadowSize + parentRoundSize) - (szImage.height() - y);
            int i = int(sqrt(double(xx * xx + yy * yy)));
            i = std::min<int>(shadowSize + parentRoundSize, i);
            i -= parentRoundSize;
            i = shadowSize - i;
            //
            int alpha = MakeAlpha(i, f, shadowSize);
#if (QT_VERSION <= QT_VERSION_CHECK(5,6,0))
            image.setPixel(x, y, QColor(0, 0, 0, alpha).rgba());
#else
            image.setPixelColor(x, y, QColor(0, 0, 0, alpha));
#endif
        }
    }
    return image;
}

bool QDrawShadowHelper::splitRect(const QRect &rcSrc, int shadowSize, QRect *parrayRect, int nArrayCount)
{
    Q_ASSERT(nArrayCount == 9);
    //
    QRect* arrayRect = parrayRect;
    //
    int nWidth = rcSrc.width();
    int nHeight = rcSrc.height();
    //
//    if (ptTopLeft.x() <= 0)
//        return false;
//    if (ptTopLeft.y() <= 0)
//        return false;
//    if (ptTopLeft.x() >= nWidth / 2)
//        return false;
//    if (ptTopLeft.y() >= nHeight / 2)
//        return false;
    //
    int x1 = rcSrc.left() + 0;
    int x2 = rcSrc.left() + shadowSize;
    int x3 = rcSrc.left() + nWidth - shadowSize;
    //
    int y1 = rcSrc.top() + 0;
    int y2 = rcSrc.top() + shadowSize;
    int y3 = rcSrc.top() + nHeight - shadowSize;
    //
    arrayRect[0] = QRect(x1, y1, shadowSize, shadowSize);
    arrayRect[1] = QRect(x2, y1, nWidth - shadowSize * 2, shadowSize);
    arrayRect[2] = QRect(x3, y1, shadowSize, shadowSize);

    arrayRect[3] = QRect(x1, y2, shadowSize, nHeight - shadowSize * 2);
    arrayRect[4] = QRect(x2, y2, nWidth - shadowSize * 2, nHeight - shadowSize * 2);
    arrayRect[5] = QRect(x3, y2, shadowSize, nHeight - shadowSize * 2);

    arrayRect[6] = QRect(x1, y3, shadowSize, shadowSize);
    arrayRect[7] = QRect(x2, y3, nWidth - shadowSize * 2, shadowSize);
    arrayRect[8] = QRect(x3, y3, shadowSize, shadowSize);
    //
    return true;
}

QColor QDrawShadowHelper::getClientBorderColor() const
{
    return m_clientBorderColor;
}

void QDrawShadowHelper::setClientBorderColor(const QColor &color)
{
    if (m_clientBorderColor != color) {
        m_clientBorderColor = color;
        if (m_widget)
            m_widget->update();
    }
}

void QDrawShadowHelper::paint(QPainter *p)
{
    p->save();
    if (m_shadowSize > 0 && m_show)
    {
        QRect arrayDest[9];
        splitRect(m_widget->rect(), m_shadowSize, arrayDest, 9);
        for (int i = 0; i < 9; i++) {
            if (i == 4)
            {
//                p->setBrush(m_clientBgColor);
//                if (m_clientBorderColor.isValid())
//                {
//                    QRect rc1 = arrayDest[i].marginsRemoved(QMargins(0, 0, 1, 1));
//                    p->setPen(QPen(m_clientBorderColor, 1));
//                    p->drawRect(rc1);
//                }
//                else
//                {
//                    QRect rc1 = arrayDest[i].marginsRemoved(QMargins(0, 0, 1, 1));
//                    p->setPen(QPen(QColor("#3A3A4A")));
//                    p->drawRect(rc1);
//                }
            }
            else
            {
                const QRect& rcSrc = m_arrayImageGrid[i];
                const QRect& rcDest = arrayDest[i];
                p->drawImage(rcDest, m_img, rcSrc);
            }
        }
    }
    else
    {
        p->setBrush(m_clientBgColor);
        p->setPen(Qt::NoPen);
        p->drawRect(m_widget->rect());
    }
    p->restore();
}

int QDrawShadowHelper::shadowSize()
{
    return m_shadowSize;
}

void QDrawShadowHelper::hide()
{
    m_show = false;
    QLayout* lay = 0;
    if (m_widget->inherits("QMainWindow")){
        QMainWindow* window = qobject_cast<QMainWindow*>(m_widget);
        lay = window->centralWidget()->layout();
    } else {
        lay = m_widget->layout();
    }
    if (lay)
        lay->setContentsMargins(0, 0, 0, 0);
}

void QDrawShadowHelper::show()
{
    m_show = true;
    QLayout* lay = 0;
    if (m_widget->inherits("QMainWindow")){
        QMainWindow* window = qobject_cast<QMainWindow*>(m_widget);
        lay = window->centralWidget()->layout();
    } else {
        lay = m_widget->layout();
    }
    if (lay)
        lay->setContentsMargins(m_shadowSize, m_shadowSize, m_shadowSize, m_shadowSize);
}
