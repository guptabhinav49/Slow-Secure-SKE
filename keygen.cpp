// #include <bits/stdc++.h>
#include "ske-lib.h"
// using namespace std;

KEYGEN::KEYGEN(int secpar)
{
    this->secpar = secpar;
}

vb KEYGEN::keygen(string name, bigint &N, bigint &e)
{   
    vb key;
    if (name == "RSA")
    {
        int shift = secpar / 16;
        vb p(secpar + shift, 0), q(secpar - shift, 0), et(secpar, 0);
        sample_prime(p);
        sample_prime(q);
        sample_prime(et);

        bigint P, Q, E;
        P = p, Q = q;
        N = P*Q;
        e = et;

        key = vb(3 * secpar);
        for (int i = 0; i < 3 * secpar; i++)
        {
            if (i < secpar - shift)
                key[i] = p[i];
            else if (i < 2 * secpar)
                key[i] = q[i];
            else
                key[i] = e[i];
        }
    }
    return key;
}