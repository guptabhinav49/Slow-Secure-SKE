#include <bits/stdc++.h>>

#include "ske-lib.h"

using namespace std;

void BLOCK::increment(vb &r)
{
    int first = 0;
    int k = r.size();
    for (int i = 0; i < k; i++)
    {
        if (!r[k - i - 1])
        {
            r[k - i - 1] = 1;
            break;
        }
        else
        {
            r[k - i - 1] = 0;
        }
    }
}

void BLOCK::xor_vec(vb &message, vb &key, vb &enc, int start, int end)
{
    for (int i = start; i < end; i++)
    {
        enc[i] = message[i] ^ key[i % (end - start)];
    }
}

void BLOCK::randomr(vb &r)
{
    srand(time(NULL));
    for (int i = 0; i < r.size(); i++)
    {
        r[i] = rand() % 2;
    }
}

BLOCK::BLOCK(vb key, int mode, string name)
{
    this->prf_instance = new PRF(name, key);
    this->mode = mode;
    this->key_block = key;
}

vb BLOCK::encrypt(vb message)
{
    if (mode == 0)
    {
        int k = this->key_block.size(); //k = 3*(security parameter)
        int len = message.size();       //length of message
        int num_blocks = len / k;       //number of blocks.

        vb r(k);
        this->randomr(r);

        vb enc(len + k);
        vb zero(len + k, 0);
        this->xor_vec(zero, r, enc, len, len + k);

        for (int i = 0; i < num_blocks; i++)
        {
            this->increment(r);
            vb enc_key = this->prf_instance->eval(r);
            this->xor_vec(message, enc_key, enc, i * k, (i + 1) * k);
        }
        this->increment(r);
        vb enc_key = this->prf_instance->eval(r);
        this->xor_vec(message, enc_key, enc, k * num_blocks, len);
    }
}

vb BLOCK::decrypt(vb enc)
{
    if (mode == 0)
    {
        int k = this->key_block.size(); //k = 3*(security parameter)
        int len = enc.size();           //length of encryption
        int num_blocks = len / k - 1;   //number of message blocks.

        vb r(k);

        for (int i = 0; i < k; i++)
            r[i] = enc[len - k + i];

        vb message(len - k);

        for (int i = 0; i < num_blocks; i++)
        {
            this->increment(r);
            vb dec_key = this->prf_instance->eval(r);
            this->xor_vec(enc, dec_key, message, i * k, (i + 1) * k);
        }
        this->increment(r);
        vb dec_key = this->prf_instance->eval(r);
        this->xor_vec(message, dec_key, enc, k * num_blocks, len - k);
    }
}

string BLOCK::get_mode()
{
    if (this->mode == 0)
        return "CTR";
}

string BLOCK::get_name()
{
    return this->prf_instance->get_name();
}
