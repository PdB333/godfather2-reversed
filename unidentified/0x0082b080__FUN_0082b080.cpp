// FUNC_NAME: SomeClass::operator=
int __thiscall operator=(SomeClass *this, SomeClass *other) {
    // 0x0082b080 - Assignment operator with block copy from offset 0x50 to 0x10c
    if (this != other) {
        // Call to release/cleanup function on the source (unusual - possibly a move operation)
        // FUN_00820830 likely decrements reference count or releases owned data in 'other'
        FUN_00820830(other);

        // Copy 192-byte data block (48 dwords) from source to destination
        // Offset range: 0x50 - 0x10c (inclusive)
        // This block likely contains matrix/transform data or animation state
        // Compiler inlined the copy as 12 groups of 4 dwords each (16-byte chunks)
        // We represent as a memcpy for clarity
        const int blockSizeWords = 48; // 192 bytes / 4
        int *dest = reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x50);
        int *src  = reinterpret_cast<int*>(reinterpret_cast<char*>(other) + 0x50);
        for (int i = 0; i < blockSizeWords; ++i) {
            dest[i] = src[i];
        }
    }
    return this; // return this pointer
}