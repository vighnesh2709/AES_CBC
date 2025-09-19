#include<stdio.h>

void printBlock(unsigned char data[])
{

    printf("\n");
    for (int i = 0; i < 16; i++)
    {
        if (i % 4 == 0)
        {
            printf("\n");
        }
        printf("%c ", data[i]);
    }
    printf("\n");
    printf("\n");
}

void printHex(unsigned char data[])
{
    printf("\n");
    for (int i = 0; i < 16; i++)
    {
        if (i % 4 == 0)
        {
            printf("\n");
        }
        printf("%02X ", data[i]);
    }
    printf("\n");
    printf("\n");
}