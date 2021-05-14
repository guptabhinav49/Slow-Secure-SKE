#ifndef SKE_H
#define SKE_H
#include "ske-lib.h"
#endif
/*!
    \class SKE
    Topmost class that the user will use to perform the symmteric key encryption. Object will be initialised with a security parameter, name of the OWP primitive and mode of encryption.
*/

/*!
    \fn SKE::SKE(int secpar, string name, int mode)
    Constructor for the class.
    \param secpar Security parameter.
    \param name Name of the OWP primitive.
    \param mode Mode of encryption
*/
SKE::SKE(int secpar, string name, int mode)
{
    if(secpar < 16){
        throw std::runtime_error("Error: secpar not long enough");
    }

    this->block_instance = new BLOCK(secpar, name, mode);
    // this->key = block_instance->get_key();
    this->secpar = secpar;
}

/*!
    \fn SKE::encrypt(vb message) const
    Encrypts the input message.
    \param message Bool-vector to be encrypted
    \return CPA-SKE secure encryption
*/
vb SKE::encrypt(vb message) const
{
    return this->block_instance->encrypt(message);
}

/*!
    \fn SKE::decypt(vb enc) const
    Dencrypts the input ciphertext.
    \param enc Bool-vector to be decrypted
    \return Decrypted ciphertext
*/
vb SKE::decrypt(vb enc) const
{
    return this->block_instance->decrypt(enc);
}

/*!
    \fn SKE::get_mode()
    Getter to get the current mode of encryption.
    \return returns the mode
*/
string SKE::get_mode() const
{
    return this->block_instance->get_mode();
}

/*!
    \fn SKE::get_name()
    Getter to get the primitive in use.
    \return returns the primitive name as a string.
*/
string SKE::get_name() const
{
    return this->block_instance->get_name();
}
