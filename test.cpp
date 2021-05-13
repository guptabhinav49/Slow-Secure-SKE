#include<bits/stdc++.h>
#include "ske-lib.h"

// #ifndef SKE_H
// #define SKE_H
// #endif
void print_vb(vb a){
    for (int i = 0; i<a.size(); i++) cout << a[i];
    cout << endl;
}

int main(){
    vb v1 = {0,1,1,0,0}, v2 = {1,1,0,0,0};
    OWP* a = new OWP("ads", v1, v2);
    PRG* b = new PRG("asd", v1);
    PRF* c = new PRF("asda", v2);

    vb v3 = {1,0,0,1,1};
    print_vb(c->eval(v3));
    return 0;
}