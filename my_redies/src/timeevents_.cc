//
// Created by kiosk on 19-8-28.
//
#include "timeevents_.h"
void aeTimeEvent::settimeProc(aeTimeProc & db)
{
    timeProc = db;
}
void aeTimeEvent::setEvent(aeEvent &db)
{
    eventproc = db;
}
