/*Main Fn
-------
Sub Bytes
Shift Rows
Mic Column
Add Round Key*/

void subBytes();
void shiftRows();
void mixColumns();
void addRoundKey();
void encryptBlock(unsigned char block[16]);
