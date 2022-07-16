#include "qframelesswidget.h"
#include <QDebug>
QFramelessWidget::QFramelessWidget(QWidget *parent, bool resizeEnable, bool shadowBorder, bool winNativeEvent)
    : QWidget(parent)
    , m_framelessHelper(0)
{    
    m_framelessHelper = new QFramelessHelper(this, resizeEnable, shadowBorder, winNativeEvent, this);
}

QFramelessHelper *QFramelessWidget::framelessHelper()
{
    return m_framelessHelper;
}

void QFramelessWidget::paintEvent(QPaintEvent *e)
{
    if (m_framelessHelper == 0)
        return;
    m_framelessHelper->paintEvent(e);
}

#if (QT_VERSION >= QT_VERSION_CHECK(6,0,0))
bool QFramelessWidget::nativeEvent(const QByteArray &eventType, void *message, qintptr *result)
#else
bool QFramelessWidget::nativeEvent(const QByteArray &eventType, void *message, long *result)
#endif
{
    if (m_framelessHelper == 0)
        return false;
    return m_framelessHelper->nativeEvent(eventType, message, result);
}

#if (QT_VERSION < QT_VERSION_CHECK(5,0,0))
#ifdef Q_OS_WIN
bool QFramelessWidget::winEvent(MSG *message, long *result)
{
    return nativeEvent("windows_generic_MSG", message, result);
}
#endif
#endif

