// #ifndef SKE_H
// #define SKE_H
#include "ske-lib.h"
// #endif

OWF::OWF(string t, int i){
    name = t;
    index = i;
}

vector<bool> OWF::eval(vector<bool> const &x) const{
    return x;
}

bool OWF::hardcore(vector<bool> const &x) const{
    return 1;
}
