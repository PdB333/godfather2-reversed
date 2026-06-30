// FUNC_NAME: GlobalConfig::loadFromBuffer
void __fastcall GlobalConfig::loadFromBuffer(uint16_t* pBuffer)
{
    // The buffer format:
    // offset 0x00: uint16 -> g_configField1
    // offset 0x02: uint16 -> g_configField2
    // offset 0x04: uint32 -> g_configField3
    // offset 0x08: uint32 -> g_configField4
    // offset 0x0C: uint32[40] -> g_configArray (total 160 bytes)

    g_configField1 = pBuffer[0];                          // +0x00
    g_configField2 = pBuffer[1];                          // +0x02
    g_configField3 = *(uint32_t*)(pBuffer + 2);           // +0x04
    g_configField4 = *(uint32_t*)(pBuffer + 4);           // +0x08

    // Copy 160 bytes (40 uint32) from buffer offset +0x0C to global array
    uint32_t* pSrc = (uint32_t*)(pBuffer + 6);            // +0x0C
    uint32_t* pDst = (uint32_t*)0x01218e50;               // start of global array
    uint32_t* pDstEnd = (uint32_t*)0x01218ef0;            // end (exclusive)
    while (pDst < pDstEnd)
    {
        *pDst = *pSrc;
        pDst[1] = pSrc[1];
        pDst += 2;
        pSrc += 2;
    }
}