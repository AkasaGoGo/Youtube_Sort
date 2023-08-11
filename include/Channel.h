#ifndef __INCLUDE_CHANNEL_H__
#define __INCLUDE_CHANNEL_H__

#include "include.h"
using namespace std;
class Channel{
    wstring id;
    wstring name;
    Channel(wstring, wstring);
    void print();
};

#endif 