// FUNC_NAME: GlobalConfig::setFromStruct
void __fastcall GlobalConfig::setFromStruct(undefined2 *pData)
{
    // Global data at 0x01218e40
    // Structure layout: 2 bytes field0, 2 bytes field1, 4 bytes field2, 4 bytes field3, then 160 bytes array
    DAT_01218e40 = pData[0];          // +0x00: field0 (2 bytes)
    DAT_01218e42 = pData[1];          // +0x02: field1 (2 bytes)
    DAT_01218e44 = *(undefined4 *)(pData + 2); // +0x04: field2 (4 bytes)
    DAT_01218e48 = *(undefined4 *)(pData + 4); // +0x08: field3 (4 bytes)

    // Copy 160 bytes from pData+6 to global buffer at 0x01218e50
    undefined4 *pDest = &DAT_01218e50;          // +0x10
    undefined4 *pSrc  = (undefined4 *)(pData + 6); // +0x0C
    do {
        *pDest = *pSrc;
        pDest[1] = pSrc[1];
        pDest += 2;
        pSrc  += 2;
    } while ((int)pDest < 0x1218ef0); // End address 0x01218ef0
}