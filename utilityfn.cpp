#ifndef SKE_H
#define SKE_H
#include "ske-lib.h"
#endif

/*!
    \fn print_vb()
    Prints the bool vector to stdout  
*/
void print_vb(vb const &a)
{
    for (int i = 0; i < a.size(); i++)
        cout << a[i];
    cout << endl;
}

/*!
    \fn randomr(vb &r)
    Stores a random bit string in the input
    \param r reference to a bit string
*/
void randomr(vb &r)
{
    // srand(time(NULL));
    for (int i = 0; i < r.size(); i++)
    {
        r[i] = rand() % 2;
    }
}

/*!
    \fn millerTest(bigint b, bigint b1)
    This is second part of the miller-rabin primality check.
    \param b integer to be checked for being prime 
    \param b1 Odd number such that b = b1*2^r
    \return whether miller-test outputs True or False
*/

bool millerTest(bigint b, bigint b1)
{
    const int MAX_LEN = 200;
    vb r(MAX_LEN);

    randomr(r);
    bigint a;
    a = r;
    a = bigint(2) + a % (b - 3);

    bigint x = a.modexp(b, b1);
    if (x == 1 || x == b - 1)
        return true;

    //runs 'r-1' times

    // b1*=2;
    while (b1 != b - 1)
    {
        x = x.modexp(b, 2);
        if (x == 1)
            return false;
        if (x == b - 1)
            return true;

        b1 *= 2;
    }
    return false;
}

/*!
    \fn primality(bigint b)
    Checks whether b is prime or not.

    \param b Integer that is being tested for prime.
    \return Whether b is prime or not.
*/

bool primality(bigint b)
{
    if (b == 0 || b == 1)
    {
        return false;
    }
    if (b == 2)
        return true;
    if (b % 2 == 0)
        return false;

    bigint b1 = b - 1;

    int PROB_K = 1;
    while (b1 != 0 && b1 % 2 == 0)
    {
        b1 /= 2;
        PROB_K++;
    }

    PROB_K *= 2;
    for (int i = 0; i < PROB_K; i++)
    {
        if (!millerTest(b, b1))
            return false;
    }
    return true;
}

/*!
    \fn sample_prime(vb &p)
    Randomly samples prime of size p.size()
    \param p Bit-vector in which the binary form the prime will be stored.
*/

void sample_prime(vb &p)
{
    // srand(time(NULL));

    int i = 0;
    bigint b;
    while (!primality(b))
    {
        // b = p;
        // cout << i++  << " " << b << endl;
        // print_vb(p);
        randomr(p);
        p[0] = 1;
        p[p.size() - 1] = 1;
        b = p;
    }
}
/*!
    \fn increment(vb &r)
    Increments input bool/bit-vector by 1.
    \param r Input to increment.
*/
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

/*!
    \fn xor_vec(vb &message, vb &key, vb &enc, int start, int end)
    XORs message with the key and stores in the enc. XOR is done from index start to index end (inclusive).

    \param message Input message to be XORed.
    \param key Bit-vector to be XORed with.
    \param enc Variable to store the result.
    \param start Initial index
    \param end Last index 
*/

void xor_vec(vb &message, vb &key, vb &enc, int start, int end)
{
    for (int i = start; i < end; i++)
    {
        enc[i] = message[i] ^ key[i % (end - start)];
    }
}
