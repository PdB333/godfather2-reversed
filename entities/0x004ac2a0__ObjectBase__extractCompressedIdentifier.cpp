// FUNC_NAME: ObjectBase::extractCompressedIdentifier

int __fastcall ObjectBase::extractCompressedIdentifier(int thisPtr)
{
    // Check if the pointer at +0x48 is valid (self-referential pointer to containing object)
    int base;
    if (*(int*)(thisPtr + 0x48) == 0) {
        base = 0;
    } else {
        // Subtract 0x48 to get the start of the outer object (common EA pattern for RTTI)
        base = *(int*)(thisPtr + 0x48) - 0x48;
    }

    // Read a pointer from the outer object at offset 0x218 (likely to a type info / hash table)
    int ptr = *(int*)(base + 0x218);

    if (ptr != 0) {
        // Combine high 24 bits of ptr with a byte at offset 0x30 into a 32-bit identifier
        // This appears to compress a hash or type ID into a single integer
        return (ptr & 0xFFFFFF00) | (*(unsigned char*)(ptr + 0x30) & 0xFF);
    }

    return 0;
}