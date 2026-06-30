// FUNC_NAME: RefCountedPair::release
void RefCountedPair::release()
{
    if (this == nullptr) {
        return;
    }

    // this is a pointer to a structure with two handle fields
    // this[0] : pointer to control block A
    // this[1] : pointer to control block B
    RefCountedObject* controlA = this[0]; // *in_EAX
    RefCountedObject* controlB = this[1]; // in_EAX[1]

    // Release controlB if it exists
    if (controlB != nullptr) {
        // controlB points to a slot in an array; the slot index is stored at offset -8 from controlB
        int slotIndex = *(int*)((char*)controlB - 8);
        // The array base is stored at offset 0xc in controlA
        void** arrayBase = *(void***)((char*)controlA + 0xc);
        // Clear the slot (set to null)
        arrayBase[slotIndex] = nullptr;

        // Decrement reference count at controlA + 4
        ((int*)((char*)controlA + 4))--;

        // Free the memory block starting at 16 bytes before controlB
        void* memBlock = (void*)((char*)controlB - 0x10);
        operatorDelete(memBlock);
    }

    // Release the main object itself (this)
    // The slot index for this is stored at offset -8 from this
    int thisSlotIndex = *(int*)((char*)this - 8);
    // The control block for this is the same as controlA (since it's stored at *this)
    RefCountedObject* mainControl = controlA; // Actually after the if, controlA might be reused; but the code uses *in_EAX again
    // Actually in the decompiled, after the if, iVar2 = *in_EAX; so it's the same as controlA
    void** mainArrayBase = *(void***)((char*)mainControl + 0xc);
    mainArrayBase[thisSlotIndex] = nullptr;

    // Decrement reference count at mainControl + 4
    ((int*)((char*)mainControl + 4))--;

    // Free the memory block starting at 4 bytes before this (offset -4 because int* arithmetic, -4 means -16 bytes? No: in_EAX + -4 gives a pointer to 16 bytes before this since int is 4 bytes, -4 ints = -16 bytes)
    void* thisMemBlock = (void*)((char*)this - 0x10);
    operatorDelete(thisMemBlock);
}