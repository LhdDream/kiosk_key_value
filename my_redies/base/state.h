//
// Created by kiosk on 19-8-15.
//

#ifndef MY_REDIES_STATE_H
#define MY_REDIES_STATE_H


//字典的操作状态
const int  DICT_OK  = 0;
const int DICT_ERR  = 1;
/*
 * 事件执行状态
 */
// 成功
const int  AE_OK = 0 ;
// 出错
const int AE_ERR  = -1;
/*
 * 文件事件状态
 */
// 未设置
const int  AE_NONE  = 0;
// 可读
const int  AE_READABLE  = 1 ;
// 可写
const int  AE_WRITABLE  = 2;

/*
 * 时间处理器的执行 flags
 */
// 文件事件
const int  AE_FILE_EVENTS = 1;
// 时间事件
const int  AE_TIME_EVENTS  = 2;
// 所有事件
const int  AE_ALL_EVENTS  = (AE_FILE_EVENTS|AE_TIME_EVENTS);
// 不阻塞，也不进行等待
const int  AE_DONT_WAIT = 4;

/*
 * 决定时间事件是否要持续执行的 flag
 */
const int  AE_NOMORE  = -1;

/* Macros */
#define AE_NOTUSED(V) ((void) V)

const int ANET_OK   = 0;
const int ANET_ERR     =   -1;
const int  ANET_ERR_LEN   =  256;

/* Flags used with certain functions. */
const int  ANET_NONE   = 0;
const int  ANET_IP_ONLY  =  (1<<0);
#endif //MY_REDIES_STATE_H
