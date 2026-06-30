// FUNC_NAME: SlotManager::createSlotObject
undefined4 * SlotManager::createSlotObject(int thisPtr) {
    ushort index;
    int *slotPtr;
    undefined4 *object;
    int *owner;
    int allocResult;
    char successFlag;
    undefined4 local_4[3]; // local_c, local_8, local_4

    index = 0;
    if (*(ushort *)(thisPtr + 0x20) != 0) { // slotCount > 0
        while (slotPtr = *(int **)(*(int *)(thisPtr + 0x1c) + (uint)index * 4), slotPtr[5] != 0x10) { // search for slot with type 0x10
            index = index + 1;
            if (*(ushort *)(thisPtr + 0x20) <= index) {
                return (undefined4 *)0x0; // not found
            }
        }
        owner = (int *)*slotPtr; // +0x00: pointer to owner object
        if ((owner != (int *)0x0) && (*(int *)((int)owner + 0x1c) != 0)) {
            object = (undefined4 *)GetMemoryAllocator(); // FUN_009c8f80 - returns allocator singleton
            local_4[0] = 2;   // alignment flags?
            local_4[1] = 0x10; // additional flag?
            local_4[2] = 0;    // success flag initially false
            allocResult = (**(code **)*object)(0x2c, &local_4[0]); // allocate 44 bytes via vfunc
            if (allocResult != 0) {
                object = (undefined4 *)initializeSlotObject(thisPtr, /* unaff_retaddr */, &local_4[2]); // FUN_004b6060 - init new object
                if ((char)local_4[2] != '\0') { // success flag set
                    return object;
                }
                if (object != (undefined4 *)0x0) {
                    (**(code **)*object)(1); // call destructor/release on allocated memory
                }
            }
        }
    }
    return (undefined4 *)0x0;
}