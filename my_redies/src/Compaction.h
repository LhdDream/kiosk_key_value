//
// Created by kiosk on 19-10-6.
//

#ifndef MY_REDIES_COMPACTION_H
#define MY_REDIES_COMPACTION_H
//进行sstable的合并操作
//提供两种合并方式
//通过引用计数，如果用户不使用那块内存才进行合并
#include "../base/options.h" // 标志每一层的文件个数
//可以写为异步操作
class Compaction
{
public:
private:
};
#endif //MY_REDIES_COMPACTION_H
