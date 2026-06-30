// FUNC_NAME: GameGlobalArray::setSlot
void __thiscall GameGlobalArray::setSlot(int thisPtr, int value)
{
    // Access thread-local storage at FS:0x2c to get a pointer to the engine's global table
    // The global table is a pointer-to-pointer structure: [8] is an offset to a pointer to the array,
    // then +0x90 is the start of the array, and +thisPtr->slotIndex is the element offset.
    int* tlsPtr = *(int**)(*(int*)(*(int*)__readfsdword(0x2c) + 8) + 0x90);
    int slotIndex = *(int*)(thisPtr + 0x18);  // +0x18: index into the global array
    tlsPtr[slotIndex] = value;                 // Set the slot to the new value
    updateAfterSet();                          // FUN_004aa8f0 - likely performs post-set actions
    return;
}