// FUNC_NAME: SomeClass::getTableEntry
char __fastcall SomeClass::getTableEntry(void* thisPtr, int index)
{
    // State byte at offset +0x8: 1 or 3 enable table lookup, else return 0xFF
    char state = *(char*)((int)thisPtr + 8);

    // Embedded 3-byte table at offset +0xC (unused local_4 is the full dword, but only first 3 bytes matter)
    // In the original decompilation, the table appeared as a stack variable (auStack_7) 
    // but is actually a member array. Index should be 0,1,2.
    char* table = (char*)((int)thisPtr + 0xC);

    if (state == 1 || state == 3) {
        return table[index]; // auStack_7[index]
    }
    return 0xFF;
}