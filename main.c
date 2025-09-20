#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "encryption.h"
#include "decryption.h"
#include "helpers.h"
#include "keyScheduling.h"

int main()
{
    
    FILE *fp = fopen("test_data/sample.txt", "rb");
    FILE *encOut = fopen("test_data/encrypted.bin", "wb");
    if (!fp || !encOut)
    {
        printf("Error while opening input/encrypt files\n");
        return 1;
    }

    unsigned char block[16];
    unsigned char key[16];
    unsigned char IV[16];
    unsigned char prevCipher[16];
    size_t bytesRead;

    
    printf("Enter 16 unsigned characters (AES Key): ");
    for (int i = 0; i < 16; i++)
    {
        int index = (i % 4) * 4 + (i / 4);
        scanf(" %c", &key[index]);
    }

    
    printf("Enter 16 unsigned characters (IV): ");
    for (int i = 0; i < 16; i++)
    {
        int index = (i % 4) * 4 + (i / 4);
        scanf(" %c", &IV[index]);
    }

    
    keyGen(key, 0);

   
    memcpy(prevCipher, IV, 16);

    
    while ((bytesRead = fread(block, 1, 16, fp)) > 0)
    {
        
        if (bytesRead < 16)
        {
            unsigned char padVal = 16 - bytesRead;
            for (size_t i = bytesRead; i < 16; i++)
            {
                block[i] = padVal;
            }
        }

        
        for (int i = 0; i < 16; i++)
        {
            block[i] ^= prevCipher[i];
        }

        
        encryptBlock(block);

        
        fwrite(block, 1, 16, encOut);

        
        memcpy(prevCipher, block, 16);
    }

    
    if (bytesRead == 0 && ftell(fp) % 16 == 0)
    {
        unsigned char padBlock[16];
        unsigned char padVal = 16;
        for (int i = 0; i < 16; i++)
        {
            padBlock[i] = padVal ^ prevCipher[i];
        }
        encryptBlock(padBlock);
        fwrite(padBlock, 1, 16, encOut);
    }

    fclose(fp);
    fclose(encOut);

    printf("Encryption complete. Output written to encrypted.bin\n");

    
    FILE *encIn = fopen("test_data/encrypted.bin", "rb");
    FILE *decOut = fopen("test_data/decrypted.txt", "wb");
    if (!encIn || !decOut)
    {
        printf("Error while opening decrypt files\n");
        return 1;
    }

    unsigned char curCipher[16];
    memcpy(prevCipher, IV, 16);

    
    fseek(encIn, 0, SEEK_END);
    long fileSize = ftell(encIn);
    rewind(encIn);

    size_t totalBytes = 0;

    while ((bytesRead = fread(curCipher, 1, 16, encIn)) > 0)
    {
        memcpy(block, curCipher, 16);
        decryptBlock(block);         

        for (int i = 0; i < 16; i++)
        {
            block[i] ^= prevCipher[i];
        }

        
        memcpy(prevCipher, curCipher, 16);
        totalBytes += bytesRead;

        
        if (totalBytes == fileSize)
        {
            unsigned char padVal = block[15];
            if (padVal > 0 && padVal <= 16)
            {
                bytesRead -= padVal;
            }
        }

        fwrite(block, 1, bytesRead, decOut);
    }

    fclose(encIn);
    fclose(decOut);

    printf("Decryption complete. Output written to decrypted.txt\n");

    return 0;
}
