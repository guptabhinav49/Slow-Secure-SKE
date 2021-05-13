// #include <bits/stdc++.h>
#ifndef SKE_H
#define SKE_H
#include "ske-lib.h"
#endif

OWP::OWP(string t, vb i1, vb i2={0}){
    name = t;
    index1 = i1;
    index2 = i2;
}

vector<bool> OWP::eval(vector<bool> const &x) const{
    vb out;

    if(name == "RSA"){
        bigint N, e, x_dash;
        N = index1, e = index2;
        x_dash = x;

        x_dash = x_dash^e % N;

        out = x_dash.to_bitstring();
    }

    return out;
}

bool OWP::hardcore(vector<bool> const &x) const{
    return 1;
}

string OWP::get_name(){ return name;}