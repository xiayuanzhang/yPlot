#ifndef JSONFILE_H
#define JSONFILE_H

#include <QObject>
#include <QString>
#include <QFile>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QVariantMap>

//只能读取一级对象，，不能读取嵌套对象
class jsonFile
{
public:
    jsonFile();
    ~jsonFile();
    bool open(QString fileDir);  //打开文件，并
    void close();


    void write(const QString &key, const QVariant& value);

    QString readString(const QString &key);
    bool readBool(const QString &key);
    int readInt(const QString &key);
    float readFloat(const QString &key);

private:
    QString m_fileDir;
    QVariantMap m_cache;
};

#endif // JSONFILE_H
