#include <iostream>
#include <stdint.h>

/***********************************
 * Keygenerator for CSAW Challenge *
 * Jeffrey Crowell                 *
 * used in solution and server     *
 ***********************************/


typedef unsigned char uchar;
typedef unsigned int uint;
typedef struct keys keys;

using namespace std;

//simple pair of uints for returning from encrypt
struct keys
{
    uint v0;
    uint v1;
};

//TEA off of the wikipedia page :-)
keys encrypt (uint32_t* v, uint32_t* k) {
    uint32_t v0=v[0], v1=v[1], sum=0, i;           /* set up */
    uint32_t delta=0x9e3779b9;                     /* a key schedule constant */
    uint32_t k0=k[0], k1=k[1], k2=k[2], k3=k[3];   /* cache key */
    for (i=0; i < 32; i++) {                       /* basic cycle start */
        sum += delta;
        v0 += ((v1<<4) + k0) ^ (v1 + sum) ^ ((v1>>5) + k1);
        v1 += ((v0<<4) + k2) ^ (v0 + sum) ^ ((v0>>5) + k3);  
    }                                              /* end cycle */
    keys s = {v0, v1};
    return s;
}


int main(int argc, char** argv)
{
    uint v[2];
    uint k[4];
    string input(argv[1]);
    if(input.length() < 16) //less than 16 chars makes the keys not work
    {
        cout << "input must be at least 16 characters" << endl;
        cout << "you provided only " << input.length() << " characters" << endl;
        return 0;
    }
    v[0] = (input[0] << 24) | (input[1] << 16) | (input[2] << 8) | (input[3]); //fill up the plaintext
    v[1] = (input[4] << 24) | (input[5] << 16) | (input[6] << 8) | (input[7]);
    string inrev(input.rbegin(), input.rend());                                //reverse input
    k[0] = (inrev[0] << 24) | (inrev[1] << 16) | (inrev[2] << 8) | (inrev[3]); //fill up the keys
    k[1] = (inrev[4] << 24) | (inrev[5] << 16) | (inrev[6] << 8) | (inrev[7]);
    k[2] = (inrev[8] << 24) | (inrev[9] << 16) | (inrev[10] << 8) | (inrev[11]);
    k[3] = (inrev[12] << 24) | (inrev[13] << 16) | (inrev[14] << 8) | (inrev[15]);
    keys s = encrypt(v, k); //encrypt the input under the reverse input
    uint temp1 = s.v1 ^ 0x31333337; //this part is just to make it so that it isn't straight TEA as from the vm binary
    uchar ch1 = ((s.v0 & 0xFFFFFFFF) >> 24);
    uchar ch2 = ((s.v0 & 0x00FF0000) >> 16);
    uchar ch3 = ((s.v0 & 0x0000FF00) >> 8);
    uchar ch4 = ((s.v0 & 0x000000FF));
    uint temp2 = (ch3 << 24) | (ch1 << 16) | (ch2 << 8) | (ch4);
    cout << temp1 << " " << temp2 << endl;  //print out the keys, for use in the solver and the server
}

