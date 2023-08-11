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

void CSV::read(vector<vector<Channel>> &contens){
    wchar_t str[128];
    wstring buf = L"",separator = L",";
    vector<wstring> sep;
    wstring::size_type pos = 0,prev = 0;
    int l = 0,sl = separator.length();
    int ct = 0;
    while(ifs.getline(str,100)){
        ct = 0;
        pos = 0;prev = 0;
        buf = wstring(str) + separator;
        wcout << buf;
        l = buf.length();

        for(;pos < l && (pos = buf.find(separator, pos)) != wstring::npos; prev = (pos+=sl)) {
            wstring item = buf.substr(prev,pos - prev);
            ct++;
            wcout << item << endl;
        }

    }
}