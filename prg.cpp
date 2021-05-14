// #include <bits/stdc++.h>
#ifndef SKE_H
#define SKE_H
#include "ske-lib.h"
#endif

PRG::PRG(int secpar, string name){
    int shift = key.size()/48;
    
    vb vb1, vb2, vb3;
    vb1 = vb(key.begin(), key.begin() + key.size()/3 + shift);
    vb2 = vb(key.begin() + key.size()/3 + shift, key.begin() + 2*key.size()/3);
    vb3 = vb(key.begin() + 2*key.size()/3, key.end());

    bigint a, b;
    a = vb1;
    b = vb2;
    a *= b;

    owp_instance = new OWP(secpar, name);   //to be changed, just dummy info
    key_owp = owp_instance->get_key();
}

vb PRG::eval(vb input){
    vb intermediate = input;
    vb out;
    for(int i=0; i<input.size(); i++){
        out.push_back(owp_instance->hardcore(intermediate));
        intermediate = owp_instance->eval(intermediate);
    }
    // intermediate = owp_instance->eval(intermediate);
    out.insert(out.end(), intermediate.begin(), intermediate.end());

    return out;
}

string PRG::get_name(){return owp_instance->get_name();}
vb PRG::get_key(){return owp_instance->get_key();}