// FUNC_NAME: SlotManager::releaseAllSlots
void __thiscall SlotManager::releaseAllSlots(int *thisPtr)
{
    int slotCount = thisPtr[1] - 1; // param_1[1] is number of slots
    if (slotCount >= 0) {
        int stride = slotCount * 0x70; // each slot is 0x70 bytes
        do {
            int *slotBase = (int *)((int)thisPtr[0] + stride); // base of current slot
            int *refPtr = (int *)slotBase[0x40 / 4]; // offset +0x40: pointer to ref-counted object
            if (refPtr != nullptr) {
                decRefCount(refPtr); // FUN_00557020 - likely decrements reference
                // Check if there is a non-zero short at offset 4 (ref count? Or maybe another counter)
                short *countAt4 = (short *)(refPtr + 1); // offset 4? Actually refPtr is int*, +1 = offset 4
                if (*countAt4 != 0) {
                    short *countAt6 = (short *)((int)refPtr + 6); // offset 6
                    *countAt6 = *countAt6 - 1;
                    if (*countAt6 == 0) {
                        // If ref count reaches zero, call destructor (vtable at start) with argument 1
                        (*(void (__thiscall **)(int))(*refPtr))(1);
                    }
                }
                slotBase[0x40 / 4] = 0; // null out the pointer
            }
            slotCount--;
            stride -= 0x70;
        } while (slotCount >= 0);
    }
    // Call virtual functions on objects at offsets 0x10 and 0xC (in this pointer?)
    // thisPtr[4] is likely a vtable pointer at offset 0x10? Actually index 4 means offset 0x10
    // (**(code **)(*(int *)param_1[4] + 4))(*param_1,0);
    // This calls a function at vtable+4 with arguments: thisPtr[0] (the slot array) and 0.
    (*(void (__thiscall **)(int, int))(*((int *)thisPtr[4]) + 1))(thisPtr[0], 0);
    if (thisPtr[3] != 0) {
        (*(void (__thiscall **)(int, int))(*((int *)thisPtr[3]) + 1))(thisPtr[3], 0);
    }
    // vtable+12: call with no arguments
    (*(void (__thiscall **)(void))(*((int *)thisPtr[4]) + 3))();
}