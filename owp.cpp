#ifndef SKE_H
#define SKE_H
#include "ske-lib.h"
#endif

/*! \class OWP
    One Way Permutation Class, specifically implements the RSA function (along with prime sampling)

*/

/*! \fn OWP::OWP(int secpar, string t)
     Constructor
    \param secpar is the security parameter
    \param t is the name of the OWP to be used
    \return an OWP object

*/
OWP::OWP(int secpar, string t)
{
    this->secpar = secpar;
    name = t;
    KeyGen_RSA *keygen_instance = new KeyGen_RSA(secpar);
    key = keygen_instance->keygen(t, N, e);
    nbits = (N.to_bitstring()).size();
    cout << N << " " << e << endl;
}

/*!
    \fn OWP::eval(vb const &x)
    Evaluates output of OWP on the input vector
    \param x: the input boolean vector.
    \return a boolean vector of the same size as the input
*/
vb OWP::eval(vb const &x) const
{
    vb out;

    if (name == "RSA")
    {
        bigint x_dash;
        x_dash = x;
        x_dash = x_dash % N;
        x_dash = x_dash.modexp(N, e);
        out = x_dash.to_bitstring();
    }
    if (out.size() != nbits)
    {
        reverse(out.begin(), out.end());
        while (out.size() != nbits)
            out.push_back(0);

        reverse(out.begin(), out.end());
    }

    return out;
}

/*!
    \fn OWP::hardcore(vb const &x) const
    This function calculates the hardcore bit for the input boolean vector.
    \param x: the input boolean vector
*/

bool OWP::hardcore(vb const &x) const
{
    return x[x.size() - 1];
}

/*! \fn OWP::get_name()
    \return returns the name of the OWP being used.
*/
string OWP::get_name() const { return name; }

/*! \fn OWP::get_key()
    \return returns the key(p||q||e)
*/
vb OWP::get_key() const { return key; }