// FUNC_NAME: setObjectSentinelValues
void __fastcall setObjectSentinelValues(uint32_t* pObject)
{
    // Write known magic debug values into the first 4 dwords of the structure
    // Typical EA EARS sentinel pattern used for memory validation
    pObject[0] = 0xBADBADBA;   // +0x00: Common freed heap marker
    pObject[1] = 0xBEEFBEEF;   // +0x04: Additional fill pattern
    pObject[2] = 0xEAC15A55;   // +0x08: Engine-specific magic (possibly "EACS" version)
    pObject[3] = 0x91100911;   // +0x0C: Another sentinel value
    // Clear the next two dwords, likely for metadata or flags
    pObject[4] = 0;            // +0x10: Reserved
    pObject[5] = 0;            // +0x14: Reserved
}