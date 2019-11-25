//
// Created by kiosk on 19-11-21.
//

#ifndef MY_REDIES_VERSION_H
#define MY_REDIES_VERSION_H
#include <list>
//在合并的过程中会造成文件的增加和删除，这样会生成新的Version
//Version 会被追加写入到Manifest中
//版本控制　,从大量文件中快速定位文件
//相当于是对于所有的sst文件机型一个记录
//达到一定程度会写入到manifest之中
class Version //分层记录一下所有的sst文件信息,包括文件大小,文件编号
        //引用基础等，记录Compaction相关的状态信息
        //对于每一层也有相应的影响
{
public:
private:
};
#endif //MY_REDIES_VERSION_H
