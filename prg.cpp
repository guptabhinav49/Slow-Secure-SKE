// #include <bits/stdc++.h>
#ifndef SKE_H
#define SKE_H
#include "ske-lib.h"
#endif

PRG::PRG(string name, vb key){
    owp_instance = new OWP(name, key, key);   //to be changed, just dummy info
    index_owp = key;
}

vb PRG::eval(vb input){
    vb intermediate = input;
    vb out;
    for(ll i=0; i<input.size(); i++){
        out.push_back(owp_instance->hardcore(intermediate));
        intermediate = owp_instance->eval(intermediate);
    }
    // intermediate = owp_instance->eval(intermediate);
    out.insert(out.end(), intermediate.begin(), intermediate.end());

    return out;
}

string PRG::get_name(){return owp_instance->get_name();}