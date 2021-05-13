#include <vector>
#include <string>
#include "BigInt.cpp"
#define vb vector<bool>
using namespace std;

/*Mode 0 -> CTR Mode*/

class OWP
{
private:
    string name;
    vb index1;
    vb index2;

public:
    OWP(string, vb i1, vb i2);
    vb eval(vb const &x) const;
    bool hardcore(vb const &x) const;
    string get_name();
};

class PRG
{
    OWP *owp_instance;
    vb index_owp;

public:
    PRG(string name, vb key);
    vb eval(vb input);
    string get_name();
};

class PRF
{
    vb key_prg;
    PRG *prg_instance;

public:
    PRF(string name, vb key);
    vb eval(vb index);
    string get_name();
};

class BLOCK
{
    vb key_block;
    int mode;
    PRF *prf_instance;

public:
    BLOCK(vb key, int mode, string name);
    vb encrypt(vb message);
    vb decrypt(vb enc);
    string get_name();
    string get_mode();
};

class SKE
{
    vb key;
    int secpar;
    BLOCK *block_instance;

public:
    SKE(string name, int secpar, int mode);
    vb decrypt(vb enc);
    vb encrypt(vb message);
    string get_name();
    string get_mode();
    // vb serialize();
};

class KEYGEN
{
    int secpar;

public:
    KEYGEN(int secpar);
    vb keygen(string name);
};

//FUNCTIONS

void sample_prime(vb &p);
bool primality(vb p);
void xor_vec(vb &message, vb &key, vb &enc, int start, int end);
void increment(vb &r);
void randomr(vb &r);