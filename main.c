#include <stdio.h>
#include <stdlib.h>
#include "encryption.h"
#include "decryption.h"
#include "helpers.h"
#include "keyScheduling.h"

// // AES-128 encryption (10 rounds)
// void encryptBlock(unsigned char block[16]) {
//     // Initial round key
//     addRoundKey(block, roundKeys[0]);

//     // 9 main rounds
//     for (int round = 1; round < 10; round++) {
//         subBytes(block);
//         shiftRows(block);
//         mixColumns(block);
//         addRoundKey(block, roundKeys[round]);
//     }

//     // Final round (no mixColumns)
//     subBytes(block);
//     shiftRows(block);
//     addRoundKey(block, roundKeys[10]);
// }

// // AES-128 decryption (10 rounds)
// void decryptBlock(unsigned char block[16]) {
//     // Initial round (use last round key)
//     addRoundKey(block, roundKeys[10]);

//     // 9 main rounds (inverse order)
//     for (int round = 9; round > 0; round--) {
//         invShiftRows(block);
//         invSubBytes(block);
//         addRoundKey(block, roundKeys[round]);
//         invMixColumns(block);
//     }

//     // Final round
//     invShiftRows(block);
//     invSubBytes(block);
//     addRoundKey(block, roundKeys[0]);
// }



int main()
{

    unsigned char block[16];
    unsigned char key[16];

    printf("Enter 16 unsigned characters (AES Block)");
    for (int i = 0; i < 16; i++)
    {

        int index = (i % 4) * 4 + (i / 4);
        scanf(" %c", &block[index]);
    }

    printf("Block:");
    printBlock(block);

    printf("Enter 16 unsigned character key (AES Block)");
    for (int i = 0; i < 16; i++)
    {

        int index = (i % 4) * 4 + (i / 4);
        scanf(" %c", &key[index]);
    }

    keyGen(key,0);

    // for(int i = 0 ; i < 11; i++){
    //     printHex(roundKeys[i]);
    // }

    /*
    initalround key
    10 rounds
    encrypted data

    use last key from table as main round key
    and do decryption
    */

    encryptBlock(block);
    printf("\nEncrypted Block: ");
    printHex(block);

    // Decrypt
    decryptBlock(block);
    printf("\nDecrypted Block: ");
    printBlock(block);

    return 0;
}

/*
AES

Main Fn
-------
Sub Bytes
Shift Rows
Mic Column
Add Round Key


Key Gen
-------
4 Words
Shift wors
XOR
Rij part

*/