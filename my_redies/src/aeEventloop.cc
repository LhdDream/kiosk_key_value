//
// Created by kiosk on 19-8-28.
//
#include "aeEventloop.h"
aeEventloop::aeEventloop() {

}
aeEventloop::~aeEventloop() {

}
void aeEventloop::loop()
{
    stop.store(false);
    while(!stop.load())
    {
        if(before)
            before(); // 如果有before　执行before
        aeProcessEvents(AE_ALL_EVENTS);
    }
}
int aeEventloop::aeProcessEvents(int flags) {
    if((flags & AE_FILE_EVENTS ) == 0 && (flags & AE_TIME_EVENTS) == 0)
    {
        return 0;
    }

}