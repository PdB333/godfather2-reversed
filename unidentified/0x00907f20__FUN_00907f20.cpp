// FUNC_NAME: SomeClass::clearArrayEntries
void __thiscall FUN_00907f20(int this)
{
    uint i;
    int entryPtr;

    // Loop over entries starting at this+0x14, each 8 bytes wide, count from this+0x94
    // +0x94: count of entries in the array
    // +0x14: start of array (each entry is 8 bytes)
    i = 0;
    if (*(int *)(this + 0x94) != 0) {
        entryPtr = this + 0x14;
        do {
            FUN_004086d0(entryPtr);  // likely destructor or cleanup for each entry
            FUN_00408310(entryPtr);  // likely reset/zero/free for each entry
            i = i + 1;
            entryPtr = entryPtr + 8;
        } while (i < *(uint *)(this + 0x94));
    }
    // Also clear a global/static data structure at DAT_01206940
    FUN_004086d0(&DAT_01206940);
    return;
}