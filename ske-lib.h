#include <vector>
#include <string>
#define vb vector<bool>
using namespace std;

/*Mode 0 -> CTR Mode*/

class OWP
{
private:
    string name;
    int index1;
    int index2;

public:
    OWP(string, int i1, int i2);
    vb eval(vb const &x) const;
    bool hardcore(vb const &x) const;
    string get_name();
};

class PRG
{
    OWP owp_instance;
    vb key_owp;

public:
    PRG(string name, int key);
    vb eval(vb input);
    string get_name();
};

class PRF
{
    vb key_prg;
    PRG prg_instance;

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
    void xor_vec(vb &message, vb &key, vb &enc, int start, int end);
    void increment(vb &r);
    void randomr(vb &r);

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
    void sample_prime(vb &p);
    bool primality();
}