//
// Created by kiosk on 19-9-15.
//

#ifndef MY_REDIES_DBUPDATE_H
#define MY_REDIES_DBUPDATE_H
//这里编写对于更新key_value 的操作，如果put的话，会新插入一个kv数组
//key存在的话，直接插入
//key删除策略等待键过期或者返回最新更新的时间中的key
//仅仅只保存当前的时刻占用5bit
// 对于用户传来的key作为一个标示,并且使用sds进行粗糙南湖
//使用一个结构体或者map来标示当前key的版本
#endif //MY_REDIES_DBUPDATE_H
