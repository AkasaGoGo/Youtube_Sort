#include "include/include.h"
using namespace std;

Channel::Channel(string id, string name,string url){
    this->id = id;
    this->name = name;
    this->url = url;
}

void Channel::print(){
    cout << id << ":name:" << name << "\n";
}