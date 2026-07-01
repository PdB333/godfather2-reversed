// FUNC_NAME: GodfatherGameManager::shutdownCleanup
void __fastcall GodfatherGameManager::shutdownCleanup(undefined4 *this) {
    // Set vtable pointers (likely not the final ones)
    *this = &PTR_FUN_00d73b34;                // +0x00: vtable pointer 1
    this[1] = &PTR_LAB_00d73b30;              // +0x04: vtable pointer 2
    this[2] = &PTR_LAB_00d73b20;              // +0x08: vtable pointer 3

    // Release global static resources
    someDeallocationOrDestructor(&DAT_0112db74); // e.g., static AudioManager instance
    someDeallocationOrDestructor(&DAT_0112db7c);
    someDeallocationOrDestructor(&DAT_012069c4);
    someDeallocationOrDestructor(&DAT_012069b4);

    // Clean up array B (objects stored in a dynamic array at +0xD0)
    uint countB = (uint)this[0x35];           // +0xD4: number of elements in array B
    if (countB != 0) {
        uint idx = 0;
        do {
            // For each object, release internal data at offset 0xDC
            someDeallocationOrDestructor(*(int*)(this[0x34] + idx * 4) + 0xDC);
            // Then call destructor via vtable
            undefined4 *obj = *(undefined4 **)(this[0x34] + idx * 4);
            if (obj != (undefined4 *)0x0) {
                (**(code **)*obj)(1);          // virtual cleanup op with argument 1
            }
            idx++;
        } while (idx < countB);
    }

    // Clean up array A (objects at +0x14), similar pattern
    uint countA = (uint)this[6];              // +0x18: number of elements in array A
    if (countA != 0) {
        uint idx = 0;
        do {
            undefined4 *obj = *(undefined4 **)(this[5] + idx * 4);
            if (obj != (undefined4 *)0x0) {
                (**(code **)*obj)(1);          // vtable destructor
            }
            idx++;
        } while (idx < countA);
    }

    // Free array pointers themselves
    if (this[0x34] != 0) {                   // +0xD0 pointer
        operatorDelete(this[0x34]);           // FUN_009c8f10
    }
    someEngineCleanup();                     // FUN_00834170
    if (this[5] != 0) {                     // +0x14 pointer
        operatorDelete(this[5]);
    }
    finalizeShutdown();                       // FUN_004083d0

    // Switch to destruction vtable pointers (for base class or cleanup)
    this[1] = &PTR_LAB_00e32854;
    *this = &PTR_LAB_00d73b1c;

    DAT_0112db84 = 0;                         // Clear singleton pointer
}