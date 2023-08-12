#include "include/include.h"
using namespace std;

Channel::Channel(string id, string name){
    this->id = id;
    this->name = name;
}

void Channel::print(){
    cout << id << ":name:" << name << "\n";
}