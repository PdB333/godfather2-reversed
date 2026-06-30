// FUNC_NAME: getFlagBasedTypeIdentifier
// Address: 0x0072d0c0
// Role: Returns a constant type identifier (0x8BBDCE97 or 0x7530F904) depending on bit 22 of a flag at offset 0x1F5C.
int __thiscall getFlagBasedTypeIdentifier(void* thisPtr)
{
    // Read 32-bit field at offset 0x1F5C from this (large object, e.g., manager or player)
    unsigned int field = *(unsigned int*)((char*)thisPtr + 0x1F5C); // +0x1F5C
    // Extract bit 22 (0x16)
    unsigned int bit = (field >> 22) & 1;
    // Conditional mask: -bit yields 0xFFFFFFFF if bit set, else 0
    unsigned int masked = -(unsigned int)(bit != 0) & 0xE9952A6D;
    // Base constant summed with optional mask
    return (int)(masked + 0x8BBDCE97);
}