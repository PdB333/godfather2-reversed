// FUNC_NAME: EngineObject::cleanupManagedPointers
void __fastcall EngineObject::cleanupManagedPointers(int this) // __thiscall via ecx
{
    int* pSlot;
    int idx;
    int slotBase;

    // Iterate over array of 4 slots at offsets +0xC4, +0xCC, +0xD4, +0xDC
    slotBase = this + 0xE4; // base after the array? Actually starts at end+8
    idx = 4;
    do {
        pSlot = (int*)(slotBase - 8); // point to current slot
        slotBase -= 8;
        if (*pSlot != 0) {
            releaseResource(slotBase); // release the resource at the slot address (not the pointer? Actually call address of slot? See note)
        }
        idx--;
    } while (idx >= 0);

    // Release two additional pointers at +0x84 and +0x7C
    if (*(int*)(this + 0x84) != 0) {
        releaseResource(this + 0x84);
    }
    if (*(int*)(this + 0x7C) != 0) {
        releaseResource(this + 0x7C);
    }
}

// Note: FUN_004daf90 is a release/destruct function.
// The loop seems to pass the address of the slot (the location of the pointer) rather than the pointer value itself.
// This is unusual but consistent with the decompiled code: it calls FUN_004daf90(iVar3) where iVar3 is the address of the slot after decrement.
// The check is on the content of the previous slot (pSlot = slotBase-8) before decrement, then it calls with the new slotBase (the current address).
// This pattern suggests that slots are stored in a contiguous block and the function is called on the slot address to nullify it or release the object.
// Likely releaseResource takes a pointer to a pointer and sets it to null after deletion.
// For clarity, we keep the decompiled logic.