#ifndef SKE_H
#define SKE_H
#include "ske-lib.h"
#endif

/*! \class PRG
    This is a length doubling pesudorandom generator, which uses the RSA OWP.
*/
/*! \fn PRG::PRG(int secpar, string name)
    \brief Constructor
    \param secpar security parameter
    \param name name of the underlying OWP

*/
PRG::PRG(int secpar, string name)
{
    owp_instance = new OWP(secpar, name);
    key_owp = owp_instance->get_key();
}

/*! \fn PRG::eval(vb input)
    Evaluates output of PRG for the given input. It is based on the one-bit stretch PRG (used length of input number of times)
    \param input the input boolean vector
    \return output of PRG in the form of a boolean vector (of double length)

*/
vb PRG::eval(vb input) const
{
    vb intermediate = input;
    vb out;
    for (int i = 0; i < input.size(); i++)
    {
        out.push_back(owp_instance->hardcore(intermediate));
        // cout << "eval start";
        intermediate = owp_instance->eval(intermediate);
        // cout << "eval end " << i << endl;
    }
    // cout << "\tPRG calc done" << endl;

    out.insert(out.end(), intermediate.begin(), intermediate.end());

    return out;
}
/*! \fn PRG::get_name()
    \return returns the name of the OWP being used.
*/
string PRG::get_name() const { return owp_instance->get_name(); }

/*! \fn PRG::get_key()
    \return returns the key(p||q||e)
*/
vb PRG::get_key() const { return key_owp; }