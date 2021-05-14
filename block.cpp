#ifndef SKE_H
#define SKE_H
#include "ske-lib.h"
#endif

/*!
    \class BLOCK
    This class blockwise encrpyts the input message, after calling the class PRF multiple times (i.e. for each block of message).
*/

/*!
    \fn BLOCK::BLOCK(int secpar, string name, int mode)
    This is the constructor for this class.
    \param secpar Security parameter
    \param name Name of the OWP primitive to be used for the defining the PRF used (only one option as of now)
    \param mode Mode (CBC only as of now)
*/
BLOCK::BLOCK(int secpar, string name, int mode)
{   
    this->secpar = secpar;
    this->prf_instance = new PRF(secpar, name);
    this->mode = mode;
    this->key_size = prf_instance->get_key_size(); //size = 3* secpar
}

/*!
    \fn BLOCK::encrypt(vb message)
    Encrypt message block-wise
    \param message Message to be encrypted by this object.
    \return The encrypted bool-vector
*/
vb BLOCK::encrypt(vb message) const
{   
    vb enc;
    if (mode == 0)
    {
        // int key_size = this->key_block.size(); //k = 3*(security parameter)
        int len = message.size();       //length of message
        int num_blocks = len / key_size;       //number of blocks.

        // cout << "numbocks: " << num_blocks << endl;
        vb r(key_size);
        randomr(r);
        // cout << "r: ";
        // print_vb(r);


        enc = vb(len);
        vb zero(len + key_size, 0);
        // cout << "before xor:\t"; print_vb(enc);
        enc.insert(enc.end(), r.begin(), r.end());

        // xor_vec(zero, r, enc, len, len + key_size);
        
        // cout << "after:\t"; print_vb(enc);
        for (int i = 0; i < num_blocks; i++)
        {
            increment(r);
            vb enc_key = this->prf_instance->eval(r);
            xor_vec(message, enc_key, enc, i * key_size, (i + 1) * key_size);
        }
        increment(r);
        vb enc_key = this->prf_instance->eval(r);
        reverse(enc_key.begin(), enc_key.end());

        xor_vec(message, enc_key, enc, key_size * num_blocks, len);
        // cout << "incR: ";
        // print_vb(r);
        // cout << "enc_key: ";
        // print_vb(enc_key);
    }
    return enc;
}

/*!  
    \fn BLOCK::decrypt(vb enc)
    Decrypts the ciphertext blockwise
    \param enc Ciphertext to be decrypted
    \return Decrypted bool vector from the input ciphertext
*/
vb BLOCK::decrypt(vb enc) const
{   
    vb message;
    if (mode == 0)
    {
        // int k = this->key_block.size(); //k = 3*(security parameter)
        int len = enc.size();           //length of encryption
        int num_blocks = len / key_size - 1;   //number of message blocks.

        cout << "num_blocks: " << num_blocks << endl;

        vb r(key_size);

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
        // cout << "r: ";
        // print_vb(r);
        vb dec_key = this->prf_instance->eval(r);
        reverse(dec_key.begin(), dec_key.end());
        // cout << "dec_key: ";
        // print_vb(dec_key);
        xor_vec(enc, dec_key, message, key_size * num_blocks, len - key_size);
    }
    return message;
}

/*!
    \fn BLOCK::get_mode()
    Getter to get the current mode of encryption.
    \return returns the mode
*/
string BLOCK::get_mode() const
{
    if (this->mode == 0)
        return "CTR";

    return NULL;
}

/*!
    \fn BLOCK::get_name()
    Getter to get the primitive in use.
    \return returns the primitive name as a string.
*/
string BLOCK::get_name() const
{
    return this->prf_instance->get_name();
}
