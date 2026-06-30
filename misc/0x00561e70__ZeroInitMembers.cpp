// FUNC_NAME: ZeroInitMembers
// Address: 0x00561e70
// Role: Initializes a structure's members to zero (skips fields at offsets +0x08 and +0x0C)
void __thiscall ZeroInitMembers(int* thisPtr)
{
    // +0x00, +0x04
    thisPtr[0] = 0;
    thisPtr[1] = 0;
    // Skipped indices 2 and 3 (offsets +0x08, +0x0C) – possibly set elsewhere
    // +0x10, +0x14, +0x18, +0x1C (indices 4,5,6,7)
    thisPtr[7] = 0;
    thisPtr[6] = 0;
    thisPtr[5] = 0;
    thisPtr[4] = 0;
    // +0x20, +0x24, +0x28, +0x2C, +0x30, +0x34, +0x38, +0x3C, +0x40, +0x44, +0x48, +0x4C
    thisPtr[8] = 0;
    thisPtr[9] = 0;
    thisPtr[10] = 0;
    thisPtr[0xb] = 0;
    thisPtr[0xc] = 0;
    thisPtr[0xd] = 0;
    thisPtr[0xe] = 0;
    thisPtr[0xf] = 0;
    thisPtr[0x10] = 0;
    thisPtr[0x11] = 0;
    thisPtr[0x12] = 0;
    thisPtr[0x13] = 0;
}