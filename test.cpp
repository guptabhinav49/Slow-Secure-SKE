#ifndef SKE_H
#define SKE_H
#include "ske-lib.h"
#endif

int main()
{
    srand(time(NULL));
    // vb v1 = {0, 1, 1, 0, 0}, v2 = {1, 1, 0, 0, 0};
    // OWP *a = new OWP(17, "RSA");
    // cout << "hello!" << endl;

    // PRG *b = new PRG("asd", v1);
    // PRF *c = new PRF("asda", v2);

    // SKE *s = new SKE(64, "RSA", 0);
    // cout << "hello!" << endl;
    int message_size = 1e3;
    vb message(message_size);
    for(int i=0; i<message_size; i++){
        message[i] = rand()%2;
    }
    // print_vb(message);

    // vb enc = s->encrypt(message);
    // print_vb(enc);

    // cout << "ENC DONE" << endl;

    // vb dec = s->decrypt(enc);
    // print_vb(dec);

    // for(int i=0; i<message_size; i++){
    //     if(dec[i] != message[i]){
    //         cout << "wrong" << endl;
    //         break;
    //     }
    // }

    PRG* p = new PRG(100, "RSA");
    vb enc = p->eval(message);

    print_vb(enc);

    // cout << "correct\n";

    // vb v3 = {1, 0, 0, 1, 1};
    // print_vb(c->eval(v3));

    // // ios::sync_with_stdio(0), cin.tie(0);
    // string str = "0909";
    // bigint BIG = str;
    // BIG *= 1000200000003000LL;

    // print_vb(BIG.to_bitstring());
    // vb alpha = {0,1,1,0};
    // vb alpha1 = {0,1,1,0};
    // alpha1.insert(alpha1.end(), alpha.begin(), alpha.end());
    // print_vb(alpha1);


    // bigint b1 = 52131212;
    // bigint b2 = 90131231231212123;
    // b1 = b2.modexp();
    // cout << b1 << endl;
    return 0;
}