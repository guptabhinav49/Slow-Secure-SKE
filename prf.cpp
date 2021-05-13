#ifndef SKE_H
#define SKE_H
#include "ske-lib.h"
#endif

PRF::PRF(string name, vb key){
    prg_instance = new PRG(name, key);
    key_prg = key;
}

vb PRF::eval(vb index){
    vb out = key_prg;
    for(int i=0; i<index.size(); i++){
        out = prg_instance->eval(out);
        if(index[i]){
            out = vb(out.begin(), out.begin()+out.size()/2);
        }
        else{
            out = vb(out.begin() + out.size()/2, out.begin()+out.size());
        }
    }
    return out;
}

string PRF::get_name(){return prg_instance->get_name();}