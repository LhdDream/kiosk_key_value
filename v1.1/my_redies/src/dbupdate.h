//
// Created by kiosk on 19-9-15.
//

#ifndef MY_REDIES_DBUPDATE_H
#define MY_REDIES_DBUPDATE_H
//这里编写对于更新key_value 的操作，如果put的话，会新插入一个kv数组
//key存在的话，直接插入
//key删除策略等待键过期或者返回最新更新的时间中的key
//使用一个结构体或者map来标示当前key的版本

#include "../base/sds.h"
#include "../util/bloom_filter.h"

//删除键和正常的键


class dbupdate{
public:
private:
};
#endif //MY_REDIES_DBUPDATE_H
