#include <vector>
#include <string>
#define vb vector<bool>
using namespace std;

class OWP{
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

class PRG{
    OWP owp_instance;
    vb key_owp;

public:
    PRG(string name, int key);
    vb eval(vb input);
    string get_name();
}; 

class PRF{
    vb key_prg;
    PRG prg_instance;

public:
    PRF(string name, vb key);
    vb eval(vb index);
    string get_name();
};

class SKE{
    vb key;
    int secpar, mode;
    string prf_name;
    PRF prf_instance;

    vb keygen(int secpar);

public:
    SKE(string name, int secpar, int mode);
    vb decrypt(vb enc);
    vb encrypt(vb message);
    string get_name();
    // vb serialize();
};