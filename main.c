#include <stdio.h>
#include <stdlib.h>
#include "encryption.h"
#include "decryption.h"
#include "helpers.h"


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

    printf("key: ");
    printBlock(key);

    subBytes(block);

    shiftRows(block);
    // printBlock(block);
    mixColumns(block);

    addRoundKey(block, key);

    printf("\n");
    printHex(block);


    addRoundKey(block, key);
    invMixColumns(block);
    invShiftRows(block);
    invSubBytes(block);

    printf("\nDecrypted block: ");
    printBlock(block);

    return 0;
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