//
// Created by kiosk on 19-8-15.
//

#ifndef MY_REDIES_STATE_H
#define MY_REDIES_STATE_H
//采用状态机的方式来进行
#include <iostream>
#include "sds.h"
#include <string>
class status{
public:
    // error type
    status() noexcept  = default;
    ~status() = default;
    status operator = (const status &) = delete;
    //error
    //error typde
    static bool OK() { return code == Ok;} //
    static bool IsNotFound() { return code == NotFound;}
    static bool ISNotSupported() {return code == NotSupported ;}
    static bool IsInvalidargument() {return code == Invalidargument;}
    static void Setcode(size_t status_) { code = status_;}
    [[nodiscard]] std::string tostring() const {
        switch (code) {
            case Ok: {
                return "OK";
            }
            case NotFound: {
                return "NotFound";
            }
            case NotSupported: {
                return "NotSupported";
            }
            case Invalidargument:
            {
                return "Invalidargument";
            }
            default:
                break;
        }
    };
private:
    enum Status{
        Ok = 0,
        NotFound = 1, //没有找到
        NotSupported = 2, // 不支持
        Invalidargument //  无效参数
    };
    static unsigned long  code ;
};
unsigned  long status::code = 0 ;
#endif //MY_REDIES_STATE_H
