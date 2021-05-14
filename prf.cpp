#ifndef SKE_H
#define SKE_H
#include "ske-lib.h"
#endif

/*! \class PRF
    Pseudo Random Function Class, based on a Tree structure of PRGs. The Key used is (p||q||e)
*/

/*! \fn PRF::PRF(int secpar, string name)
    \brief Constructor
    \param secpar security parameter
    \param name name of the underlying security parameter.
*/
PRF::PRF(int secpar, string name)
{
    this->secpar = secpar;
    prg_instance = new PRG(secpar, name);
    key_prg = prg_instance->get_key();
}

/*! \fn PRF::eval(vb index)
    \brief evaluates the PRF on the given input  (same size as input)
    \param index Input Boolean Vector
    \return returns the output of the PRF
*/
vb PRF::eval(vb index) const
{
    vb out = key_prg;
    for (int i = 0; i < index.size(); i++)
    {
        out = prg_instance->eval(out);
        if (index[i])
        {
            out = vb(out.begin(), out.begin() + out.size() / 2);
        }
        else
        {
            out = vb(out.begin() + out.size() / 2, out.begin() + out.size());
        }
    }
    cout << "PRF calc done" << endl;
    return out;
}

/*! \fn PRF::get_name()
    \return returns the name of the OWP being used.
*/
string PRF::get_name() const { return prg_instance->get_name(); }

/*! \fn PRF::get_key()
    \return returns the key size (3 x secpar in case of name="RSA")
*/
int PRF::get_key_size() const { return key_prg.size(); }