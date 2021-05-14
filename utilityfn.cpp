#ifndef SKE_H
#define SKE_H
#include "ske-lib.h"
#endif

/*
    This file contains various getter functions,
    helping at various places throughout the code

    functions:
        print_vb(a): prints the input bit vector a
        randomr(r): stores random but vector in r
        primality(p): primality check for bit vector p
        sample_prime(p): samples a random prime in p
        increment(p)
        xor_vec(params) : used for xoring the input message with the random pad generated 
*/

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


bool millerTest(bigint b, bigint b1){
    const int MAX_LEN = 200;
    vb r(MAX_LEN);

    randomr(r);
    bigint a;
    a = r;
    a = bigint(2) + a%(b-3);

    bigint x = a.modexp(b, b1);
    if(x==1 || x==b-1) return true;

    //runs 'r-1' times

    // b1*=2;
    while(b1 != b-1){
        x = x.modexp(b, 2);
        if(x==1) return false;
        if(x==b-1) return true;

        b1 *= 2;
    }
    return false;
}

bool primality(bigint b)
{   
    if(b==0 || b==1){
        return false;
    }
    if (b==2) return true;
    if(b%2==0) return false;

    bigint b1 = b-1;

    int PROB_K = 1;
    while(b1 != 0 && b1 % 2 == 0){
        b1/=2;
        PROB_K++;
    }

    PROB_K *= 2;
    for(int i=0; i<PROB_K; i++){
        if(!millerTest(b, b1))
            return false;
    }
    return true;
}

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
