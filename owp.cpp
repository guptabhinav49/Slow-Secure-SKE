// #include <bits/stdc++.h>
#ifndef SKE_H
#define SKE_H
#include "ske-lib.h"
#endif

OWP::OWP(int secpar, string t){
    this->secpar = 
    name = t;
    KeyGen_RSA *keygen_instance = new KEYGEN(secpar);
    key = keygen_instance->keygen(t, N, e);
}

vector<bool> OWP::eval(vector<bool> const &x) const{
    vb out;

    if(name == "RSA"){
        bigint x_dash;
        x_dash = x;

        x_dash = x_dash^e % N;
        out = x_dash.to_bitstring();
    }

    return out;
}

bool OWP::hardcore(vector<bool> const &x) const{
    vb x_dash;
    x_dash = x;

    x_dash = x_dash^e % N;
    bv out = x_dash.to_bitstring();

    return out[out.size()-1]; 
}

string OWP::get_name(){ return name;}
vb OWP::get_key(){return key;}