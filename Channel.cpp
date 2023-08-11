#include "include/include.h"
using namespace std;

Channel::Channel(wstring id, wstring name){
    this->id = id;
    this->name = name;
}

void Channel::print(){
    wcout << id << ":name:" << name << "\n";
}