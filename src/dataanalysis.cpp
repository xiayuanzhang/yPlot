#include "dataanalysis.h"


dataAnalysis::dataAnalysis()
{

}



int dataAnalysis::getChannelNum()
{
    return channels;
}

void dataAnalysis::inputDataStream(QByteArray stream)
{
    if(stream.size()<=0) return ; //数据长度不够返回
    inputDataBuff.append(stream);  //stream有数据，则将其放入缓冲区中
    //安全判断，如果缓存数组里面内容太多就删除;避免用户没有给帧头帧尾，一直不解析数据
    if(inputDataBuff.size()>inputDataBuffSize)
        inputDataBuff.clear();

     //检查是否同时包含帧头和帧尾,使用while处理，以防出现了多帧数据
    int ns = 0,ne = 0,ds = 0,de = 0;
    while(1){

        ns = inputDataBuff.indexOf(frameNameHead,0);//找到帧头的位置
        ne = inputDataBuff.indexOf(frameNameEnd,ns);  //从帧头之后开始找帧尾的位置
        ds = inputDataBuff.indexOf(frameDataHead,ne);  //从名字帧尾之后开始找数据帧头的位置
        de = inputDataBuff.indexOf(frameDataEnd,ds);  //从帧头之后开始找帧尾的位置
        if(ns==-1|| ne==-1||ds==-1|| de==-1) break;  //帧头帧尾不齐全，不进行处理

        //必有 ns < ne <ds <de 所以不做安全判断
        //截取数据
        QByteArray name =inputDataBuff.mid(ns+frameNameHead.size()
                                           ,ne-ns-frameNameHead.size());

        QByteArray data = inputDataBuff.mid(ds+frameDataHead.size()
                                            ,de-ds-frameDataHead.size());
//        qDebug()<<data;
//        qDebug()<<data.size();

        //计算通道数量
        channels  = data.size() / 4;

        //进行解析
        analysisDataName(name);
        analysisData(data);

        //清除已解析数据
//        qDebug()<<"all   --   "<<inputDataBuff.mid(0,de+frameNameEnd.size());
        inputDataBuff.remove(0,de+frameNameEnd.size()); //删除数据帧尾和帧尾之前的数据

    }

}

void dataAnalysis::clearAnalysisBuff()
{
    inputDataBuff.clear();
    lastName.clear();
    channels = 0;
}


//int dataAnalysis::dataTypeSize()
//{
//    if(dataType == "uint8"){
//        return 1;
//    }
//    else if(dataType == "uint16"){
//        return 2;
//    }
//    else if(dataType == "uint32"){
//        return 4;
//    }
//    else if(dataType == "int8"){
//        return 1;
//    }
//    else if(dataType == "int16"){
//        return 2;
//    }
//    else if(dataType == "int32"){
//        return 4;
//    }
//    else if(dataType == "float"){
//        return 4;
//    }
//    else if(dataType == "double"){
//        return 8;
//    }
//    return -1;
//}


//double dataAnalysis::dataChange(char *p)
//{

//    double result;
//    int size = dataTypeSize();
//    if(dataType == "uint8"){
//        unsigned char a;
//        char* q = reinterpret_cast<char*>(&a); //p指向result的低字节
//        for(int index = 0; index <size; index++)
//        {
//            *(q + index) = *(p + index); //data_char指向数据的高字节
//        }
//        result = static_cast<double>(a);
//        return result;
//    }
//    else if(dataType == "uint16"){
//        unsigned short int a;
//        char* q = reinterpret_cast<char*>(&a); //p指向result的低字节
//        for(int index = 0; index <size; index++)
//        {
//            *(q + index) = *(p + index); //data_char指向数据的高字节
//        }
//        result = static_cast<double>(a);
//        return result;
//    }
//    else if(dataType == "uint32"){
//        unsigned int a;
//        char* q = reinterpret_cast<char*>(&a); //p指向result的低字节
//        for(int index = 0; index <size; index++)
//        {
//            *(q + index) = *(p + index); //data_char指向数据的高字节
//        }
//        result = static_cast<double>(a);
//        return result;
//    }
//    else if(dataType == "int8"){
//        char a;
//        char* q = reinterpret_cast<char*>(&a); //p指向result的低字节
//        for(int index = 0; index <size; index++)
//        {
//            *(q + index) = *(p + index); //data_char指向数据的高字节
//        }
//        result = static_cast<double>(a);
//        return result;
//    }
//    else if(dataType == "int16"){
//        short int a;
//        char* q = reinterpret_cast<char*>(&a); //p指向result的低字节
//        for(int index = 0; index <size; index++)
//        {
//            *(q + index) = *(p + index); //data_char指向数据的高字节
//        }
//        result = static_cast<double>(a);
//        return result;
//    }
//    else if(dataType == "int32"){
//        int a;
//        char* q = reinterpret_cast<char*>(&a); //p指向result的低字节
//        for(int index = 0; index <size; index++)
//        {
//            *(q + index) = *(p + index); //data_char指向数据的高字节
//        }
//        result = static_cast<double>(a);
//        return result;
//    }

//    else if(dataType == "float"){
//        float a;
//        char* q = reinterpret_cast<char*>(&a); //p指向result的低字节
//        for(int index = 0; index <size; index++)
//        {
//            *(q + index) = *(p + index); //data_char指向数据的高字节
//        }
//        result = static_cast<double>(a);
//        return result;
//    }
//    else if(dataType == "double"){
//        double a;
//        char* q = reinterpret_cast<char*>(&a); //p指向result的低字节
//        for(int index = 0; index <size; index++)
//        {
//            *(q + index) = *(p + index); //data_char指向数据的高字节
//        }
//        result = static_cast<double>(a);
//        return result;
//    }
//    return 0;
//}


void dataAnalysis::analysisDataName(QByteArray stream)
{
    //dataNameBuff中也许存在多帧数据，但是对数组名的更新没有那么严格，所以解析一帧就行了
    QVector<QString> newName;
    int last_n = -1;
    int now_n = 0;
    for(int i = 0;i<=stream.count(",");i++){
        now_n = stream.indexOf(",",last_n+1); //最后一次循环找不到逗号，返回-1
        //最后一次循环，没有逗号 -1-last_n <0,会自动获取剩下的全部内容
        newName.append(stream.mid(last_n+1,now_n-last_n-1));
        last_n = now_n;
    }
    while(newName.size() < channels){
        QString str ="ch" + QString::number(newName.size()+1);
        newName.append(str);
    }
    if(newName != lastName){   //名字出现了变化再更新
        lastName = newName;
        emit haveNewName(newName);
    }

}

void dataAnalysis::analysisData(QByteArray stream)
{
    QByteArray dataArray;
    QVector<double> newData;
    float a;
    char *p;
    char* q;
    for(int i = 0;i<channels;i++){
        dataArray = stream.mid(i*4,4); //截取4byte的数据
        p = dataArray.data();
        q = reinterpret_cast<char*>(&a); //p指向result的低字节
        for(int index = 0; index < 4; index++)
        {
            *(q + index) = *(p + index); //data_char指向数据的高字节
        }
        newData.append(static_cast<double>(a));
    }
    emit haveNewData(newData);
}



