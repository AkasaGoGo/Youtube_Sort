#ifndef __INCLUDE_CSV_H__
#define __INCLUDE_CSV_H__

#include "include.h"
using namespace std;

class CSV{
public:
    string fname;
    ifstream ifs;

    void open(string);
    void read(vector<Channel> &contents);
};

#endif