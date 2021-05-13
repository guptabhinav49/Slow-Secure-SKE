#include "ske-lib.h"

void randomr(vb &r)
{
    srand(time(NULL));
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
    for (bigint i = 3; i * i < b; i += 1)
    {
        if (primality(i.to_bitstring()) && b % i == 0)
            return false;
    }
    return false;
}

void sample_prime(vb &p)
{
    srand(time(NULL));

    while (!primality(p))
    {
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
