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
    status() noexcept : code(Ok) {
    }
    ~status() = default;
    status operator = (const status &) = delete;
    //error
    //error typde
    bool OK() { return code == Ok;} //
    bool IsNotFound() { return code == NotFound;}
    bool ISNotSupported() {return code == NotSupported ;}
    bool IsInvalidargument() {return code == Invalidargument;}
    void Setcode(size_t status_) { code = status_;}
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
    unsigned long  code;
};
#endif //MY_REDIES_STATE_H
