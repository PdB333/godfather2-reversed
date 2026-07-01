// FUNC_NAME: PairBuffer::addEntry

void __thiscall PairBuffer::addEntry(int thisPtr, uint param2, uint param3)
{
    uint count = *(uint *)(thisPtr + 0xfac); // +0xfac: number of entries stored
    if (count < 500) {
        // Array of 500 entries, each 8 bytes (two 32-bit values)
        // Base offset of array: +0x0c
        *(uint *)(thisPtr + 0xc + count * 8) = param2;   // +0x0c: first field of entry
        *(uint *)(thisPtr + 0x10 + count * 8) = param3;  // +0x10: second field of entry
        *(int *)(thisPtr + 0xfac) = count + 1;           // increment count
    }
}