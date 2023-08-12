#ifndef __INCLUDE_CHANNEL_H__
#define __INCLUDE_CHANNEL_H__

#include "include.h"
using namespace std;
class Channel{
public:
    string id;
    string name;
    bool fav = false;
    Channel(string, string);
    void print();
};

#endif 