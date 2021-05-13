#include <bits/stdc++.h>
#include "ske-lib.h"
using namespace std;

KEYGEN::KEYGEN(int secpar)
{
    this->secpar = secpar;
}

vb KEYGEN::keygen(string name)
{
    if (name == "rsa")
    {
        int shift = secpar / 16;
        vb p(secpar + shift, 0), q(secpar - shift, 0), e(secpar, 0);
        this->sample_prime(p);
        this->sample_prime(q);
        this->sample_prime(e);

        vb key(3 * secpar);
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
}

void KEYGEN::sample_prime(vb &p)
{
    srand(time(NULL));
    p[0] = 1;
    p[p.size() - 1] = 1;

    while (!primality(p))
    {
        for (int i = 1; i < p.size() - 1; i++)
        {
            p[i] = rand() % 0;
        }
    }
}