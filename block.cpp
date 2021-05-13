// #include <bits/stdc++.h>

#ifndef SKE_H
#define SKE_H
#include "ske-lib.h"
#endif

// using namespace std;

BLOCK::BLOCK(vb key, int mode, string name)
{
    this->prf_instance = new PRF(name, key);
    this->mode = mode;
    this->key_block = key;
}

vb BLOCK::encrypt(vb message)
{   
    vb enc;
    if (mode == 0)
    {
        int k = this->key_block.size(); //k = 3*(security parameter)
        int len = message.size();       //length of message
        int num_blocks = len / k;       //number of blocks.

        vb r(k);
        randomr(r);

        enc = vb(len + k);
        vb zero(len + k, 0);
        xor_vec(zero, r, enc, len, len + k);

        for (int i = 0; i < num_blocks; i++)
        {
            increment(r);
            vb enc_key = this->prf_instance->eval(r);
            xor_vec(message, enc_key, enc, i * k, (i + 1) * k);
        }
        increment(r);
        vb enc_key = this->prf_instance->eval(r);
        xor_vec(message, enc_key, enc, k * num_blocks, len);
    }
    return enc;
}

vb BLOCK::decrypt(vb enc)
{   
    vb message;
    if (mode == 0)
    {
        int k = this->key_block.size(); //k = 3*(security parameter)
        int len = enc.size();           //length of encryption
        int num_blocks = len / k - 1;   //number of message blocks.

        vb r(k);

        for (int i = 0; i < k; i++)
            r[i] = enc[len - k + i];

        message = vb(len - k);

        for (int i = 0; i < num_blocks; i++)
        {
            increment(r);
            vb dec_key = this->prf_instance->eval(r);
            xor_vec(enc, dec_key, message, i * k, (i + 1) * k);
        }
        increment(r);
        vb dec_key = this->prf_instance->eval(r);
        xor_vec(message, dec_key, enc, k * num_blocks, len - k);
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
