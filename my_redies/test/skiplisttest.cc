//
// Created by kiosk on 19-9-7.
//
#include"../base/skiplist.cc"
#include"../util/Prena.h"
int main()
{
    Prena temp;
    skiplist<int> a1(&temp);
    a1.Insert(5);
    if(a1.Delete(5) == true)
    {
        printf("ok\n");
    }
    else
    {
        printf("error\n");
    }
    return 0;
}
