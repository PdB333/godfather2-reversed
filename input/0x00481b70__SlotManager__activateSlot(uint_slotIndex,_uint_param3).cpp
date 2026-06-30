// FUNC_NAME: SlotManager::activateSlot(uint slotIndex, uint param3)
void __thiscall SlotManager::activateSlot(int *this, uint slotIndex, uint param3)
{
    int *slotArray;  // piVar1
    int slotCount;   // from global
    int *slotEntry;  // piVar4
    int *allocatedObj; // piVar3
    int allocationResult; // iVar2
    // Stack buffer for virtual call return
    undefined auStack_8[8];
    
    // Virtual call: likely pre-activation or validation
    (*(code **)(*this + 0x34))();
    
    // Attempt to allocate a new object (size 0x54 bytes)
    allocationResult = FUN_009c8e50(0x54);
    if (allocationResult == 0 ||
        (allocationResult = FUN_004a8750(this, param3), allocationResult == 0)) {
        // First attempt failed; try again with default param3 = 1
        allocationResult = FUN_009c8e50(0x54);
        if (allocationResult == 0) {
            allocationResult = 0;
        } else {
            allocationResult = FUN_004a8750(this, 1);
        }
    }
    // Store allocated object pointer at this+0x0C
    this[3] = allocationResult;
    
    // Validate slot index against global count
    slotCount = *(uint *)(DAT_0122344c + 0x38);
    if (slotIndex < slotCount) {
        slotArray = (int *)(DAT_0122344c + 0x34);
        slotEntry = (int *)(*(int *)(DAT_0122344c + 0x34) + slotIndex * 0x0C);
        // Check slot state: if slot[0] == 2, compare with a pair from a virtual call
        if (*slotEntry == 2) {
            // Virtual call at vtable+0x04 returns a struct (two ints)
            allocatedObj = (int *)(**(code **)(*this + 4))(auStack_8);
            if (slotEntry[1] == *allocatedObj && slotEntry[2] == allocatedObj[1]) {
                // Mark slot as activated (state 4)
                *(undefined4 *)(*(int *)(DAT_0122344c + 0x34) + slotIndex * 0x0C) = 4;
            }
        }
    }
    return;
}