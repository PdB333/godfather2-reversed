// FUNC_NAME: getStructureBaseFromPointer

int __cdecl getStructureBaseFromPointer(uint inputAddr)
{
    uint originalAddr = inputAddr;
    uint alignedAddr = inputAddr & 0xFFFFFF00;  // Align to 256-byte boundary

    // Call to low-level function that returns a base pointer (EDI) and an offset (EAX)
    // Assumed signature: void getAlignedBaseAndOffset(uint original, uint aligned, int zero, int alignedCopy);
    int base;   // unaff_EDI
    int offset; // in_EAX
    getAlignedBaseAndOffset(originalAddr, alignedAddr, 0, alignedAddr, &base, &offset);

    // Calculate final offset: base - ((offset - originalAddr) / 0x28) * 0x28
    // (0x28 = 40 bytes, size of each structure slot)
    int blockOffset = (offset - (int)originalAddr) / 0x28;  // Signed division
    return base - blockOffset * 0x28;
}