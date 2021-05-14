#ifndef SKE_H
#define SKE_H
#include "ske-lib.h"
#endif

PRF::PRF(int secpar, string name){
    this->secpar = secpar;
    prg_instance = new PRG(secpar, name);
    key_prg = prg_instance->get_key();
}

vb PRF::eval(vb index) const{
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
    cout << "PRF calc done" << endl;
    return out;
}

string PRF::get_name() const {return prg_instance->get_name();}
int PRF::get_key_size() const {return key_prg.size();}