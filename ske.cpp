#ifndef SKE_H
#define SKE_H
#include "ske-lib.h"
#endif

SKE::SKE(int secpar, string name, int mode)
{
    if(secpar < 16){
        throw std::runtime_error("Error: secpar not long enough");
    }

    this->block_instance = new BLOCK(secpar, name, mode);
    // this->key = block_instance->get_key();
    this->secpar = secpar;
}

vb SKE::encrypt(vb message) const
{
    return this->block_instance->encrypt(message);
}

vb SKE::decrypt(vb enc) const
{
    return this->block_instance->decrypt(enc);
}

string SKE::get_mode() const
{
    return this->block_instance->get_mode();
}

string SKE::get_name() const
{
    return this->block_instance->get_name();
}
