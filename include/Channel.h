#ifndef __INCLUDE_CHANNEL_H__
#define __INCLUDE_CHANNEL_H__

#include "include.h"
using namespace std;
class Channel{
public:
    string id;
    string name;
    string url;
    bool fav = false;
    Channel(string, string, string);
    void print();
};

#endif 