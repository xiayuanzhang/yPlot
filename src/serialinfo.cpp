#include "serialinfo.h"

SerialInfo::SerialInfo() {}

QTimer *SerialInfo::getFindPortTimer() const
{
    return findPortTimer;
}
