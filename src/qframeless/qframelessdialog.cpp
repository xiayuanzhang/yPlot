#include "qframelessdialog.h"

QFramelessDialog::QFramelessDialog(QWidget *parent, bool resizeEnable, bool shadowBorder, bool winNativeEvent)
    : QDialog(parent)
    , m_framelessHelper(0)
{
    m_framelessHelper = new QFramelessHelper(this, resizeEnable, shadowBorder, winNativeEvent, this);
}

QFramelessHelper *QFramelessDialog::framelessHelper()
{
    return m_framelessHelper;
}

void QFramelessDialog::paintEvent(QPaintEvent *e)
{
    if (m_framelessHelper == 0)
        return;
    m_framelessHelper->paintEvent(e);
}

#if (QT_VERSION >= QT_VERSION_CHECK(6,0,0))
bool QFramelessDialog::nativeEvent(const QByteArray &eventType, void *message, qintptr *result)
#else
bool QFramelessDialog::nativeEvent(const QByteArray &eventType, void *message, long *result)
#endif
{
    if (m_framelessHelper == 0)
        return false;
    return m_framelessHelper->nativeEvent(eventType, message, result);
}

#if (QT_VERSION < QT_VERSION_CHECK(5,0,0))
#ifdef Q_OS_WIN
bool QFramelessDialog::winEvent(MSG *message, long *result)
{
    return nativeEvent("windows_generic_MSG", message, result);
}
#endif
#endif

