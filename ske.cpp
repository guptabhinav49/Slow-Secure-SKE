#include <bits/stdc++.h>
#include "ske-lib.h"

using namespace std;

SKE::SKE(string name, int secpar, int mode)
{
    vb key;
    this->keygen_instance = new KEYGEN(secpar);
    //key = Keygen(secpar)
    this->block_instance = new BLOCK(key, mode, name);
    this->key = key;
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
