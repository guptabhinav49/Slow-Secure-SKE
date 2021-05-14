// #include <bits/stdc++.h>
#ifndef SKE_H
#define SKE_H
#include "ske-lib.h"
#endif

OWP::OWP(int secpar, string t){
    this->secpar = secpar;
    name = t;
    KeyGen_RSA *keygen_instance = new KeyGen_RSA(secpar);
    key = keygen_instance->keygen(t, N, e);
    cout << N <<  " " << e << endl;
}

vector<bool> OWP::eval(vector<bool> const &x) const{
    vb out;

    if(name == "RSA"){
        bigint x_dash;
        x_dash = x;
        // cout << "YO";
        x_dash = x_dash.modexp(N, e);
        // cout << "MODEXP iter done" << endl;
        out = x_dash.to_bitstring();
    }
    if(out.size() != x.size()){
        reverse(out.begin(), out.end());
        while(out.size() != x.size())
            out.push_back(0);
        
        reverse(out.begin(), out.end());
    }

    return out;
}

bool OWP::hardcore(vector<bool> const &x) const{
    return x[x.size()-1]; 
}

string OWP::get_name(){ return name;}
vb OWP::get_key(){return key;}