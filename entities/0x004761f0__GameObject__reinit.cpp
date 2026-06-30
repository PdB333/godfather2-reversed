// FUNC_NAME: GameObject::reinit
// This function at 0x004761f0 appears to be a reinitialization or reset method for a game object.
// It sets up virtual method table pointers, initializes sub-objects, and cleans up any existing resources.
// Offsets are in 4-byte words.
void __thiscall GameObject::reinit(void* thisPtr) {
    // Set vtable pointer at offset 0x00
    *(int**)thisPtr = &PTR_FUN_00e32e84;
    // Set additional function pointers (vtable entries?) at offsets 0x3C, 0x48, 0x50
    *(int**)((char*)thisPtr + 0x3C) = &PTR_LAB_00e32ea0;  // +0x0F*4 = +0x3C
    *(int**)((char*)thisPtr + 0x48) = &PTR_LAB_00e32eb0;  // +0x12*4 = +0x48
    *(int**)((char*)thisPtr + 0x50) = &PTR_LAB_00e32eb4;  // +0x14*4 = +0x50

    // Initialize sub-object at offset 0x54 (0x15*4)
    FUN_004086d0((char*)thisPtr + 0x54);  // subObjectA constructor
    FUN_00408310((char*)thisPtr + 0x54);  // additional init for subObjectA

    // Initialize sub-object at offset 0x5C (0x17*4)
    FUN_00408310((char*)thisPtr + 0x5C);  // subObjectB init

    // Iterate over an array of pairs (starting at +0x1B*4 = +0x6C, ending at +0x2B*4 = +0xAC)
    // Each element is 2 ints (8 bytes). Step by 2 ints.
    for (int* pairPtr = (int*)((char*)thisPtr + 0x6C); pairPtr != (int*)((char*)thisPtr + 0xAC); pairPtr += 2) {
        if (pairPtr[1] != -1) {
            FUN_00441e00();  // release/cleanup resource if second element is valid
        }
    }

    // Overwrite vtable pointer at offset 0x50 with a different entry (final stage?)
    *(int**)((char*)thisPtr + 0x50) = &PTR_LAB_00e32e7c;

    FUN_0046c640();  // finalization call
}