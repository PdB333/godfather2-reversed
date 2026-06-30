// FUNC_NAME: TraverseToRootAndGetFlag
ushort __fastcall TraverseToRootAndGetFlag(int object) {
    // Walk up the chain using mNext (offset +0x68) until reaching a sentinel (0 or 0x48)
    // The stored value is the address of the end of the next node; subtract 0x48 to get the node base.
    while (*(int*)(object + 0x68) != 0 && *(int*)(object + 0x68) != 0x48) {
        object = *(int*)(object + 0x68) - 0x48; // Advance to the next node
    }
    // After loop, object points to the last valid node (or previous if sentinel was 0)
    // Extract bit 12 from a ushort at offset +0x15e
    return (*(ushort*)(object + 0x15e) >> 0xC) & 1;
}