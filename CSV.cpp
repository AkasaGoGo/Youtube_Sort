#include "include/include.h"
using namespace std;

CSV::CSV(string str){
    fname = str;
    ifs.open(fname);
    if(ifs.fail()){
        cout << "Can not open your file.";
        exit(-1);
    }
}

void CSV::read(vector<Channel> &contents){
    char str[1024];
    string buf,separator = u8",";
    vector<string> sep;
    string::size_type pos = 0,prev = 0;
    int l = 0,sl = separator.length();
    while(ifs.getline(str,500)){
        vector<string> bufline;
        pos = 0;prev = 0;
        buf = string(str) + separator;
        l = buf.length();
        for(;pos < l && (pos = buf.find(separator, pos)) != string::npos; prev = (pos+=sl)) {
            string item = buf.substr(prev,pos - prev);
            bufline.push_back(item);
            cout << item << endl;
        }
        contents.push_back(Channel(bufline[2],bufline[0]));

    }
}