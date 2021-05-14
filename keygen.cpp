#ifndef SKE_H
#define SKE_H
#include "ske-lib.h"
#endif

/*! \class KeyGen_RSA
    Generates p,q,e for RSA.
    
*/

/*!
    \fn KeyGen_RSA::KeyGen_RSA(int secpar)
    \brief Constructor
    \param secpar security parameter
*/
KeyGen_RSA::KeyGen_RSA(int secpar)
{
    this->secpar = secpar;
}

/*! \fn KeyGen_RSA::keygen(string name, bigint &N, bigint &e) const
    \brief Generates key and stores N,e in the given bigint references. We use the Miller-Rabin primality test.
*/
vb KeyGen_RSA::keygen(string name, bigint &N, bigint &e) const
{
    vb key;
    if (name == "RSA")
    {
        vb p(secpar, 0), q(secpar, 0), et(8, 0);
        sample_prime(p);
        cout << "p done!" << endl;
        sample_prime(q);
        cout << "q done!" << endl;
        sample_prime(et);
        cout << "et done!" << endl;

        bigint P, Q;
        P = p, Q = q;
        N = P * Q;
        e = et;

        key = vb(3 * secpar);
        for (int i = 0; i < 3 * secpar; i++)
        {
            if (i < secpar)
                key[i] = p[i];
            else if (i < 2 * secpar)
                key[i] = q[i];
            else
                key[i] = et[i];
        }
    }
    return key;
}