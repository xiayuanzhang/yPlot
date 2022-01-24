#include "jsonfile.h"

//将文件中的数据读取到m_cache中，操作完成之后将m_cache写入到文件
//但是这样的话，内容会不会重复？没有重复，具体原因还不知道。

jsonFile::jsonFile()
{

}

jsonFile::~jsonFile()
{
    close();
}



bool  jsonFile::open(QString fileDir)
{
    m_fileDir = fileDir;
    QFile file(fileDir+"/config.json");
    if (!file.open(QIODevice::ReadOnly))
    {
        QFile *ff = new QFile(fileDir+"/config.json");
        ff->open(QIODevice::ReadWrite); //如果文件不存在，就自己创建文件
        ff->write("{}");
        ff->close();
        return false;
    }
    QByteArray allData = file.readAll();
    file.close();

    QJsonParseError jsonError;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(allData, &jsonError);
    if (jsonError.error != QJsonParseError::NoError)
    {
        return false;

    }

    QJsonObject root = jsonDoc.object();
    m_cache = root.toVariantMap(); //将json转换为QMap

    m_fileDir = fileDir;
    return true;
}


void jsonFile::close()
{
    QJsonObject root = QJsonObject::fromVariantMap(m_cache);
    QJsonDocument jsonDoc(root);
    QByteArray data = jsonDoc.toJson(QJsonDocument::Compact);
    QFile file(m_fileDir+"/config.json");
    if (file.open(QIODevice::WriteOnly))
    {
        file.write(data);
        file.close();
    }
}

//使用的insert为什么，不是直接插入，遇到相同的时候是修改相同的值？
void jsonFile::write(const QString &key, const QVariant &value)
{
    m_cache.insert(key, value);
}

QString jsonFile::readString(const QString &key)
{

    if (m_cache.contains(key))
    {
        return m_cache.value(key).toString();
    }
    return "";
}

bool jsonFile::readBool(const QString &key)
{
    if (m_cache.contains(key))
    {
        return m_cache.value(key).toBool();
    }

    return false;
}

int jsonFile::readInt(const QString &key)
{
    if (m_cache.contains(key))
    {
        return m_cache.value(key).toInt();
    }

    return 0;
}

float jsonFile::readFloat(const QString &key)
{
    if (m_cache.contains(key))
    {
        return m_cache.value(key).toFloat();
    }

    return 0.0f;
}


