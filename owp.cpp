#ifndef SKE_H
#define SKE_H
#include "ske-lib.h"
#endif

/*
    INIT OWP

    params:
        secpar: security parameter
        t: name of the OWP used (currently only 1 available)
*/
OWP::OWP(int secpar, string t){
    this->secpar = secpar;
    name = t;
    KeyGen_RSA *keygen_instance = new KeyGen_RSA(secpar);
    key = keygen_instance->keygen(t, N, e);
    nbits = (N.to_bitstring()).size();
    cout << N <<  " " << e << endl;
}

/*
    OWP evaluate- evaalutes output of OWP on the input vector

    params:
        x: input vector<bool>
*/
vector<bool> OWP::eval(vector<bool> const &x) const{
    vb out;

    if(name == "RSA"){
        bigint x_dash;
        x_dash = x;
        x_dash = x_dash%N;
        x_dash = x_dash.modexp(N, e);
        out = x_dash.to_bitstring();
    }
    // cout << out.size()  << " " << nbits << endl;
    if(out.size() != nbits){
        reverse(out.begin(), out.end());
        while(out.size() != nbits)
            out.push_back(0);
        
        reverse(out.begin(), out.end());
    }

    return out;
}

/*
    returns the hardcore predicate (in case of RSA simply any bit of the input)
*/
bool OWP::hardcore(vector<bool> const &x) const{
    return x[x.size()-1]; 
}

/*
    simple getter functions
*/
string OWP::get_name() const { return name;}
vb OWP::get_key() const {return key;}