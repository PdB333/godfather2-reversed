// FUNC_NAME: SimManager::~SimManager
void __fastcall SimManager::~SimManager(int thisPtr) // __thiscall: this in ecx
{
    // vtable pointer initialization (chain of destructors)
    *(int*)thisPtr = &PTR_FUN_00d5d7a8;       // +0x00: first vtable
    *(int*)(thisPtr + 0xC) = &PTR_LAB_00d5d7a4; // +0x0C: second vtable (inheritance level 1)

    // Call base destructor or internal cleanup
    subDestructor_part1(thisPtr);

    // Delete individual pointer at offset +0x694 (0x1A5 * 4)
    if (*(int*)(thisPtr + 0x694) != 0) {
        operator_delete(*(void**)(thisPtr + 0x694));
    }
    // Delete individual pointer at offset +0x68C (0x1A3 * 4)
    if (*(int*)(thisPtr + 0x68C) != 0) {
        operator_delete(*(void**)(thisPtr + 0x68C));
    }

    // Delete first array (7 entries) at offset +0x67C (0x19F * 4), each entry is a struct of 40 bytes
    // The struct's first field (at offset 0) is a pointer; if non-null, delete the struct
    int arrayIndex = 7;
    int* currentSlot = (int*)(thisPtr + 0x67C); // start at +0x67C
    do {
        int* entryStart = currentSlot - 10; // move back 40 bytes (10 ints)
        currentSlot = entryStart;            // same address after decrement
        if (*currentSlot != 0) {
            operator_delete(currentSlot);    // delete the 40-byte struct (FUN_004daf90)
        }
        arrayIndex--;
    } while (arrayIndex >= 0);

    // Delete second array (31 entries) at offset +0x524 (0x149 * 4)
    // Similar pattern: each entry is a 40-byte struct
    if (*(int*)(thisPtr + 0x524) != 0) {
        operator_delete(*(void**)(thisPtr + 0x524));
    }
    arrayIndex = 0x1F; // 31
    currentSlot = (int*)(thisPtr + 0x524); // start at +0x524
    do {
        int* entryStart = currentSlot - 10;
        currentSlot = entryStart;
        if (*currentSlot != 0) {
            operator_delete(currentSlot);
        }
        arrayIndex--;
    } while (arrayIndex >= 0);

    // Update vtable to final base level
    *(int*)(thisPtr + 0xC) = &PTR_LAB_00d5d7a0;

    // Clear global singleton flag
    g_globalFlag = 0;

    // Call final cleanup
    finalDestructor_cleanup();
}