// FUNC_NAME: ManagerBase::allocateSlotArray
void __thiscall ManagerBase::allocateSlotArray(void *this, int *allocator)
{
    int *allocatedBlock;
    int *tempPointer;
    int *slot1;
    int *slot2;
    int *slot3;
    undefined local_18 [4];
    undefined local_14 [4];
    undefined local_10 [4];
    undefined local_c [4];
    
    local_18 = 0;
    local_14 = 0;
    local_10 = 0;
    // Allocate 0x40 bytes via allocator's vtable
    allocatedBlock = (int *)(**(code **)*allocator)(0x40, &local_18);
    if (allocatedBlock == (int *)0x0) {
        slot1 = (int *)0x0;
    } else {
        local_14 = 0;
        local_10 = 0;
        local_c = 0;
        *allocatedBlock = 0;
        allocatedBlock[1] = 0;
        // Initialize sub-object at allocatedBlock[2] using allocator
        allocatedBlock[2] = allocateSubObject(&local_14, allocator);
        allocatedBlock[3] = allocator;
        // Increment reference on allocator?
        (**(code **)(*allocator + 8))();
        slot1 = allocatedBlock;
    }
    // Store first slot pointer at this+0x28
    *(int **)(this + 0x28) = slot1;
    
    // Second slot at allocatedBlock+4 (offset 4 bytes)
    slot2 = allocatedBlock + 4;
    if (slot2 == (int *)0x0) {
        slot2 = (int *)0x0;
    } else {
        initSecondSlot();
    }
    *(int **)(this + 0x30) = slot2;
    
    // Third slot at allocatedBlock+10 (offset 40 bytes)
    slot3 = allocatedBlock + 10;
    if (slot3 != (int *)0x0) {
        *slot3 = allocator;
        allocatedBlock[0xb] = 0;
        allocatedBlock[0xc] = 0;
        allocatedBlock[0xd] = 0;
        *(undefined1 *)(allocatedBlock + 0xe) = 0;
        allocatedBlock[0xf] = 0;
        // Increment reference on allocator again
        (**(code **)(*allocator + 8))();
        *(int **)(this + 0x2c) = slot3;
        initThirdSlot();
        *(int *)(this + 0x34) = 0;
        return;
    }
    *(int **)(this + 0x2c) = 0;
    initThirdSlot();
    *(int *)(this + 0x34) = 0;
    return;
}