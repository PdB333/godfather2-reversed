// FUNC_NAME: SlotManager::getSlotAddress
int __fastcall SlotManager::getSlotAddress(int this)
{
    // +0x4: index into array (element index)
    int index = *(int *)(this + 4);
    // +0xc: pointer to a structure containing the array base address
    int basePtr = *(int *)(this + 0xc);
    // basePtr + 0x4: base address of the slot array (each slot is 0x34 bytes)
    int base = *(int *)(basePtr + 4);
    // Calculate absolute address of the slot
    return index * 0x34 + base;
}