#include <bits/stdc++.h>

#ifndef BIG_INT
#define BIG_INT
#include "BigInt.cpp"
#endif

#define vb vector<bool>
using namespace std;

/*Mode 0 -> CTR Mode*/

// OWP based on RSA for now, can be extended later
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
    string get_name() const;
    vb get_key() const;
};

// PRG class: Object that takes _secpar_ as input. 
// We get a PRG on instanstiation, with key length O(secpar)
class PRG
{
    OWP *owp_instance;
    vb key_owp;

public:
    PRG(int secpar, string name);
    vb eval(vb input) const;
    string get_name() const;
    vb get_key() const;
};

// Returns a PRF. Initialisation with secpar.
// Functions:
//     eval- outputs PRFs output on input index 
class PRF
{   
    int secpar;
    vb key_prg;
    PRG *prg_instance;

public:
    PRF(int secpar, string name);
    vb eval(vb index) const;
    string get_name() const;
    int get_key_size() const; 
};

// Utility class to encrypt the messages with multiple blocks
// Instantiated by class SKE
class BLOCK
{   
    int secpar;
    int key_size;
    int mode;
    PRF *prf_instance;

public:
    BLOCK(int secpar, string name, int mode);
    vb encrypt(vb message) const;
    vb decrypt(vb enc) const;
    string get_name() const;
    string get_mode() const;
    // vb get_key();
};

// CPA-secure SKE scheme
// Instantiated with _secpar_
// Functions: 
//      encrypt: encrypts the message
//      decrypt: decrypts

class SKE
{
    // vb key;
    int secpar;
    BLOCK *block_instance;

public:
    SKE(int secpar, string name, int mode);
    vb decrypt(vb enc) const;
    vb encrypt(vb message) const;
    string get_name() const;
    string get_mode() const;
    // vb serialize();
};


// Class to generate keys for RSA OWP
// called internally by OWP class on initialisation with secpar
class KeyGen_RSA
{
    int secpar;

public:
    KeyGen_RSA(int secpar);
    vb keygen(string name, bigint &N, bigint &e) const;
};

// UTILITY FUNCTIONS

void sample_prime(vb &p);
bool primality(vb p);
void xor_vec(vb &message, vb &key, vb &enc, int start, int end);
void increment(vb &r);
void randomr(vb &r);
void print_vb(vb const &a);