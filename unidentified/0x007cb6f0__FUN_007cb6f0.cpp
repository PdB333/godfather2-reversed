// FUNC_NAME: UnknownClass::handleActionCommand
void __thiscall UnknownClass::handleActionCommand(void* pArg1, void* pArg2) {
    // Check if a global manager (identified by hash 0x187b7e2b) exists
    int checkResult = FUN_00625050(0x187b7e2b, 0);
    if (checkResult == 0) {
        // Set bit 1 at offset +0x1d0 (flags field)
        *(uint*)((int)this + 0x1d0) |= 2;
        return;
    }

    // Reset pending state
    FUN_007cb610();

    // Build a packed identifier from the this pointer and a field
    // Combines top 24 bits of this pointer with bit 0 of (flags >> 6)
    uint packedId = ((uint)this >> 8) << 8;
    packedId |= (*(uint*)((int)this + 0x1d0) >> 6) & 0x01;

    // Call with pArg1, a 16-bit value from offset +0x1d6, pArg2, and the packedId
    byte actionResult = FUN_00772de0(pArg1, *(ushort*)((int)this + 0x1d6), pArg2, packedId);

    // If pArg2 is non-null (checked as char), store result at offset +0x20c
    if ((char)pArg2 != 0) {
        *(byte*)((int)this + 0x20c) = actionResult;
    }
}