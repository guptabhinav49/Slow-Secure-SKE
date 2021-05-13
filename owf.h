#include <vector>
#include <string>
using namespace std;

class OWF{
private:
    string name;
    int index;
public:
    OWF(string t, int i);
    vector<bool> eval(vector<bool> const &x) const;
    bool hardcore(vector<bool> const &x) const;
};

OWF::OWF(string t, int i){
    name = t;
    index = i;
}

vector<bool> OWF::eval(vector<bool> const &x) const{
    return x;
}
bool OWF::hardcore(vector<bool> const &x) const{
    return 1;
}
