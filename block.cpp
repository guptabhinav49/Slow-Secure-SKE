// #include <bits/stdc++.h>

#ifndef SKE_H
#define SKE_H
#include "ske-lib.h"
#endif

// using namespace std;

BLOCK::BLOCK(int secpar, int mode, string name)
{   
    this->secpar = secpar;
    this->prf_instance = new PRF(secpar, name);
    this->mode = mode;
    this->key_size = PRF->get_key_size(); //size = 3* secpar
}

vb BLOCK::get_key(){return key_block;}

vb BLOCK::encrypt(vb message)
{   
    vb enc;
    if (mode == 0)
    {
        // int key_size = this->key_block.size(); //k = 3*(security parameter)
        int len = message.size();       //length of message
        int num_blocks = len / key_size;       //number of blocks.

        vb r(key_size);
        randomr(r);

        enc = vb(len + key_size);
        vb zero(len + key_size, 0);
        xor_vec(zero, r, enc, len, len + key_size);

        for (int i = 0; i < num_blocks; i++)
        {
            increment(r);
            vb enc_key = this->prf_instance->eval(r);
            xor_vec(message, enc_key, enc, i * key_size, (i + 1) * key_size);
        }
        increment(r);
        vb enc_key = this->prf_instance->eval(r);
        xor_vec(message, enc_key, enc, key_size * num_blocks, len);
    }
    return enc;
}

vb BLOCK::decrypt(vb enc)
{   
    vb message;
    if (mode == 0)
    {
        // int k = this->key_block.size(); //k = 3*(security parameter)
        int len = enc.size();           //length of encryption
        int num_blocks = len / key_size - 1;   //number of message blocks.

        vb r(k);

        for (int i = 0; i < key_size; i++)
            r[i] = enc[len - key_size + i];

        message = vb(len - key_size);

        for (int i = 0; i < num_blocks; i++)
        {
            increment(r);
            vb dec_key = this->prf_instance->eval(r);
            xor_vec(enc, dec_key, message, i * key_size, (i + 1) * key_size);
        }
        increment(r);
        vb dec_key = this->prf_instance->eval(r);
        xor_vec(message, dec_key, enc, key_size * num_blocks, len - key_size);
    }
    return message;
}

string BLOCK::get_mode()
{
    if (this->mode == 0)
        return "CTR";

    return NULL;
}

string BLOCK::get_name()
{
    return this->prf_instance->get_name();
}
