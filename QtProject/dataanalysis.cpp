#include "dataanalysis.h"


dataAnalysis::dataAnalysis()
{

}

void dataAnalysis::setDataType(QString type)
{
    dataType = type;
}

void dataAnalysis::setChannelNum(int num)
{
    channels = num;
}

void dataAnalysis::inputDataStream(QByteArray stream)
{
    if(stream.size()<=0) return ; //数据长度不够返回
    inputDataBuff.append(stream);  //stream有数据，则将其放入缓冲区中
     //检查是否同时包含帧头和帧尾,使用while处理，以防出现了多帧数据
    while(inputDataBuff.contains(frameNameHead)
          &&inputDataBuff.contains(frameNameEnd)){
        int s = inputDataBuff.indexOf(frameNameHead,0);//找到帧头的位置
        int e = inputDataBuff.indexOf(frameNameEnd,0);
        if(s<e){    //帧头要出现在帧尾之前才是合理的
            //截取数据部分放到数据名缓存数组列表中
            dataNameBuff.append(
                        inputDataBuff.mid(s+frameNameHead.size()
                                          ,e-s-frameNameHead.size()));
            inputDataBuff.remove(s,e+frameNameEnd.size()-s); //删除掉这一部分
        }
        else{
            inputDataBuff.remove(0,e+frameNameEnd.size()); //删除掉错误的这一部分数据
        }
    }
    //检查是否同时包含帧头和帧尾,使用while处理，以防出现了多帧数据
    while(inputDataBuff.contains(frameDataHead)
         &&inputDataBuff.contains(frameDataEnd)){
       int ds = inputDataBuff.indexOf(frameDataHead,0);//找到帧头的位置
       int de = inputDataBuff.indexOf(frameDataEnd,0);
       if(ds<de){    //帧头要出现在帧尾之前才是合理的
           //截取数据部分放到数据名缓存数组列表中 
           dataBuff.append(
                       inputDataBuff.mid(ds+frameDataHead.size()
                                         ,de-ds-frameDataHead.size()));
           inputDataBuff.remove(ds,de+frameDataEnd.size()-ds); //删除掉这一部分
       }
       else{
           inputDataBuff.remove(0,de+frameDataEnd.size()); //删除掉错误的这一部分数据
       }
    }
    if(dataNameBuff.size()>0){
        analysisDataName();   //解析数据名缓存数据中的值
        dataNameBuff.clear();
    }
    if(dataBuff.size()>0){

        analysisData();   //解析数据名缓存数据中的值
        dataBuff.clear();
    }
}

void dataAnalysis::clearAnalysisBuff()
{
    inputDataBuff.clear();
    dataBuff.clear();
    dataNameBuff.clear();
}

int dataAnalysis::dataTypeSize()
{
    if(dataType == "uint8"){
        return 1;
    }
    else if(dataType == "uint16"){
        return 2;
    }
    else if(dataType == "uint32"){
        return 4;
    }
    else if(dataType == "int8"){
        return 1;
    }
    else if(dataType == "int16"){
        return 2;
    }
    else if(dataType == "int32"){
        return 4;
    }
    else if(dataType == "float"){
        return 4;
    }
    else if(dataType == "double"){
        return 8;
    }
    return -1;
}


double dataAnalysis::dataChange(char *p)
{

    double result;
    int size = dataTypeSize();
    if(dataType == "uint8"){
        unsigned char a;
        char* q = reinterpret_cast<char*>(&a); //p指向result的低字节
        for(int index = 0; index <size; index++)
        {
            *(q + index) = *(p + index); //data_char指向数据的高字节
        }
        result = static_cast<double>(a);
        return result;
    }
    else if(dataType == "uint16"){
        unsigned short int a;
        char* q = reinterpret_cast<char*>(&a); //p指向result的低字节
        for(int index = 0; index <size; index++)
        {
            *(q + index) = *(p + index); //data_char指向数据的高字节
        }
        result = static_cast<double>(a);
        return result;
    }
    else if(dataType == "uint32"){
        unsigned int a;
        char* q = reinterpret_cast<char*>(&a); //p指向result的低字节
        for(int index = 0; index <size; index++)
        {
            *(q + index) = *(p + index); //data_char指向数据的高字节
        }
        result = static_cast<double>(a);
        return result;
    }
    else if(dataType == "int8"){
        char a;
        char* q = reinterpret_cast<char*>(&a); //p指向result的低字节
        for(int index = 0; index <size; index++)
        {
            *(q + index) = *(p + index); //data_char指向数据的高字节
        }
        result = static_cast<double>(a);
        return result;
    }
    else if(dataType == "int16"){
        short int a;
        char* q = reinterpret_cast<char*>(&a); //p指向result的低字节
        for(int index = 0; index <size; index++)
        {
            *(q + index) = *(p + index); //data_char指向数据的高字节
        }
        result = static_cast<double>(a);
        return result;
    }
    else if(dataType == "int32"){
        int a;
        char* q = reinterpret_cast<char*>(&a); //p指向result的低字节
        for(int index = 0; index <size; index++)
        {
            *(q + index) = *(p + index); //data_char指向数据的高字节
        }
        result = static_cast<double>(a);
        return result;
    }

    else if(dataType == "float"){
        float a;
        char* q = reinterpret_cast<char*>(&a); //p指向result的低字节
        for(int index = 0; index <size; index++)
        {
            *(q + index) = *(p + index); //data_char指向数据的高字节
        }
        result = static_cast<double>(a);
        return result;
    }
    else if(dataType == "double"){
        double a;
        char* q = reinterpret_cast<char*>(&a); //p指向result的低字节
        for(int index = 0; index <size; index++)
        {
            *(q + index) = *(p + index); //data_char指向数据的高字节
        }
        result = static_cast<double>(a);
        return result;
    }
    return 0;
}


void dataAnalysis::analysisDataName()
{
    //dataNameBuff中也许存在多帧数据，但是对数组名的更新没有那么严格，所以解析一帧就行了
    QVector<QString> name;
    int last_n = -1;
    int now_n = 0;
    for(int i = 0;i<=dataNameBuff[0].count(",");i++){
        now_n = dataNameBuff[0].indexOf(",",last_n+1); //最后一次循环找不到逗号，返回-1
        //最后一次循环，没有逗号 -1-last_n <0,会自动获取剩下的全部内容
        name.append(dataNameBuff[0].mid(last_n+1,now_n-last_n-1));
        last_n = now_n;
    }
    if(name != newName){   //名字出现了变化再更新
        newName = name;
        emit haveNewName(newName);
    }

}

void dataAnalysis::analysisData()
{
    newDataList.clear(); //先清除掉之前的内容。
    QVector<double> newData;
    QByteArray dataArray;
    for(int j = 0;j<dataBuff.size();j++){
        for(int i = 0;i<channels;i++){
            dataArray = dataBuff[j].mid(i*dataTypeSize(),dataTypeSize());
            newData.append(dataChange(dataArray.data()));
        }
        newDataList.append(newData);
        newData.clear();
        dataArray.clear();
    }
    emit haveNewData(newDataList);
}



