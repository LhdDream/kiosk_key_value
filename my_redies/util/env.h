//
// Created by kiosk on 19-10-16.
//

#ifndef MY_REDIES_ENV_H
#define MY_REDIES_ENV_H
//对于写入文件的简单接口封装
#include "../base/state.h"
#include "../base/sds.h"
class  WritableFile {
        public:
        WritableFile() = default;

        WritableFile(const WritableFile&) = delete;
        WritableFile& operator=(const WritableFile&) = delete;

        virtual ~WritableFile() = default;
        virtual bool Append(const std::string & data) = 0;
        virtual bool Close() = 0;
        virtual bool Flush() = 0;
};

#endif //MY_REDIES_ENV_H