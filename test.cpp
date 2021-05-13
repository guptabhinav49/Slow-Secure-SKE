// #include<bits/stdc++.h>
#include "BigInt.cpp"
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

    // ios::sync_with_stdio(0), cin.tie(0);
	string str = "99999999999999999999999999999999";
	bigint BIG=str;
	BIG*=1000200000003000LL;

	print_vb(BIG.to_bitstring());

    return 0;
}