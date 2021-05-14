// #include <bits/stdc++.h>
#ifndef SKE_H
#define SKE_H
#include "ske-lib.h"
#endif

using namespace std;

SKE::SKE(int secpar, string name = "RSA", int mode = 0)
{
    if(secpar < 16){
        throw std::runtime_error("Error: secpar not long enough");
    }

    this->block_instance = new BLOCK(secpar, name, mode);
    this->key = block_instance->get_key();
    this->secpar = secpar;
}

vb SKE::encrypt(vb message)
{
    return this->block_instance->encrypt(message);
}

vb SKE::decrypt(vb enc)
{
    return this->block_instance->decrypt(enc);
}

string SKE::get_mode()
{
    return this->block_instance->get_mode();
}

string SKE::get_name()
{
    return this->block_instance->get_name();
}
