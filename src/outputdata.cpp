
#include "outputdata.h"
#include <QFileDialog>

#include <QDebug>
outputData::outputData(QVector<QLineSeries*> ser)
{
    QString location = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);

    QString path = QFileDialog::getSaveFileName(nullptr, tr("设置保存路径"),
                                 location,
                                 tr("*.csv"));
    //下面这段处理程序，需要保证.csv这样的后缀长度为4，如.st就不行(想偷懒。。)
    QString type = path.right(4);

    //确认存在该文件类型，创建文件夹
    if(type == ".csv"){
        path.remove(path.size()-4,4);
        QDir *folder = new QDir;
        if(folder->mkdir(path)) //创建文件夹
            path = path+"/";
        //qDebug()<<path;
    }
    //错误警告，一般不会出错
    else{

    }


    //根据文件类型创建文件
    if(type == ".csv"){
        for(int i=0;i<ser.size();i++){
            outputCsv(path+ser.at(i)->name()+type,ser.at(i)->points());
        }
    }
}



//1.简介：
//  全称：Comma Separated Values。
//  是“逗号分隔值”的英文缩写，通常是纯文本文件，一般用wordWPS或是记事本打开。
//2.规则：
//（1）开头不留空，以行为单位。
//（2）可含或不含列名，含列名则居文件第一行。
//（3）一行数据不跨行，无空行，回车\n换行。
//（4）以半角逗号作分隔符，列为空也要表达其存在。
//（5）列内容如存在半角逗号（即,）则用半角引号（即""）将该字段值包含起来。
//（6）列内容如存在半角引号（即"）则应替换成半角双引号（""）转义，并用半角引号（即""）将该字段值包含起来。
//（7）文件读写时引号，逗号操作规则互逆。
//（8）内码格式不限，可为 ASCII、Unicode 或者其他。
//（9）不支持特殊字符

void outputData::outputCsv(QString fileName,QList<QPointF> data)
{
    if(QFile::exists(fileName)){
        QMessageBox::warning(nullptr,"错误" ,"文件已存在\n保存中止",QMessageBox::Ok);
        return;
    }
    QFile file(fileName);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QMessageBox::warning(nullptr,"错误" ,"文件打开失败\n保存中止",QMessageBox::Ok);
        return;
    }
    QTextStream outdata(&file);
    outdata<<tr("x,")<<tr("y,\n"); //表头
    for(int i = 0;i<data.size();i++){
        QByteArray x = QByteArray::number(data.at(i).x());
        QByteArray y = QByteArray::number(data.at(i).y());
        outdata<<tr(x.data())<<tr(",")<<tr(y.data())<<tr(",")<<tr("\n");
    }
    file.close();

}
