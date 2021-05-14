#ifndef SKE_H
#define SKE_H
#include "ske-lib.h"
#endif

PRG::PRG(int secpar, string name){
    owp_instance = new OWP(secpar, name);
    key_owp = owp_instance->get_key();
}

vb PRG::eval(vb input) const {
    vb intermediate = input;
    vb out;
    for(int i=0; i<input.size(); i++){
        out.push_back(owp_instance->hardcore(intermediate));
        // cout << "eval start";
        intermediate = owp_instance->eval(intermediate);
        // cout << "eval end " << i << endl;
    }
    cout << "\tPRG calc done" << endl;
    // intermediate = owp_instance->eval(intermediate);
    out.insert(out.end(), intermediate.begin(), intermediate.end());

    return out;
}

string PRG::get_name() const {return owp_instance->get_name();}
vb PRG::get_key() const {return key_owp;}