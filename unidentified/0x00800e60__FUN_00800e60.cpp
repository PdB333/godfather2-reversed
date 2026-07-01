// FUNC_NAME: SomeClass::clearActiveSlots
void __fastcall SomeClass::clearActiveSlots(int this) // this = param_1
{
    // Array of 7 slots at offset 0x7e4, each 8 bytes (first 4 bytes = pointer, next 4 bytes = unknown/unused)
    // Iterate over slots
    int* slotPtr = (int*)(this + 0x7e4);
    int remaining = 7;
    do {
        if (*slotPtr != 0) {
            // Release the resource (likely decrement refcount or free)
            releaseResource(*slotPtr);
            if (*slotPtr != 0) {
                // Destroy/release the pointer itself
                destroyResource(slotPtr);
                *slotPtr = 0;
            }
        }
        slotPtr += 2; // Move to next slot (8 bytes stride)
        remaining--;
    } while (remaining != 0);

    // Set flag at offset 0x81c (bit 0x10) indicating slots are cleared
    *(uint*)(this + 0x81c) |= 0x10;
    // Store global constant (likely sentinel value)
    *(int*)(this + 0x79c) = DAT_00d5ccf8;
}