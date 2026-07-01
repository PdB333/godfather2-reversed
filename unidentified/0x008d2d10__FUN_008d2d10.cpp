// FUNC_NAME: SomeManager::getSlotAddress
int __thiscall SomeManager::getSlotAddress(int thisPtr, int slotIndex)
{
    // +0x30: base of an array of structures, each 0x14 bytes
    return thisPtr + 0x30 + slotIndex * 0x14;
}