#ifndef SKE_H
#define SKE_H
#include "ske-lib.h"
#endif

void print_vb(vb const &a)
{
    for (int i = 0; i < a.size(); i++)
        cout << a[i];
    cout << endl;
}

void randomr(vb &r)
{
    // srand(time(NULL));
    for (int i = 0; i < r.size(); i++)
    {
        r[i] = rand() % 2;
    }
}

bool primality(vb p)
{
    bigint b;
    b = p;
    if (b == 0 || b == 1)
        return false;
    if(b==2)
        return true;

    for (bigint i = 3; i * i < b; i += 1)
    {
        if (b % i == 0)
            return false;
    }
    return true;
}

void sample_prime(vb &p)
{
    // srand(time(NULL));

    int i = 0;
    while (!primality(p))
    {   
        bigint b;
        b = p;
        // cout << i++  << " " << b << endl;
        // print_vb(p);
        randomr(p);
        p[0] = 1;
        p[p.size() - 1] = 1;
    }
}

void increment(vb &r)
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

void xor_vec(vb &message, vb &key, vb &enc, int start, int end)
{
    for (int i = start; i < end; i++)
    {
        enc[i] = message[i] ^ key[i % (end - start)];
    }
}
