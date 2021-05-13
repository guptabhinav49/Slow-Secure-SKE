// #include <bits/stdc++.h>
#ifndef SKE_H
#define SKE_H
#include "ske-lib.h"
#endif

OWP::OWP(string t, vb i1, vb i2){
    name = t;
    index1 = i1;
    // cout << "sda" << endl;
}

vector<bool> OWP::eval(vector<bool> const &x) const{
    return x;
}

bool OWP::hardcore(vector<bool> const &x) const{
    return 1;
}

string OWP::get_name(){ return name;}