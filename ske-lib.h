#include <bits/stdc++.h>

#ifndef BIG_INT
#define BIG_INT
#include "BigInt.cpp"
#endif

#define vb vector<bool>
using namespace std;

/*Mode 0 -> CTR Mode*/

class OWP
{
private:
    string name;
    bigint N;
    bigint e;
    vb key;
    int secpar;

public:
    OWP(int secpar, string);
    vb eval(vb const &x) const;
    bool hardcore(vb const &x) const;
    string get_name();
    vb get_key();
};

class PRG
{
    OWP *owp_instance;
    vb key_owp;

public:
    PRG(int secpar, string name);
    vb eval(vb input);
    string get_name();
    vb get_key();
};

class PRF
{   
    int secpar;
    vb key_prg;
    PRG *prg_instance;

public:
    PRF(int secpar, string name);
    vb eval(vb index);
    string get_name();
    int get_key_size();
};

class BLOCK
{   
    int secpar;
    int key_size;
    int mode;
    PRF *prf_instance;

public:
    BLOCK(int secpar, string name, int mode);
    vb encrypt(vb message);
    vb decrypt(vb enc);
    string get_name();
    string get_mode();
    // vb get_key();
};

class SKE
{
    // vb key;
    int secpar;
    BLOCK *block_instance;

public:
    SKE(int secpar, string name, int mode);
    vb decrypt(vb enc);
    vb encrypt(vb message);
    string get_name();
    string get_mode();
    // vb serialize();
};

class KeyGen_RSA
{
    int secpar;

public:
    KeyGen_RSA(int secpar);
    vb keygen(string name, bigint &N, bigint &e);
};

//FUNCTIONS

void sample_prime(vb &p);
bool primality(vb p);
void xor_vec(vb &message, vb &key, vb &enc, int start, int end);
void increment(vb &r);
void randomr(vb &r);
void print_vb(vb &a);