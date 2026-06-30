// FUNC_NAME: getSlotPointer
int __thiscall getSlotPointer(int thisPtr, int slotIndex)
{
    int storedPointer;

    // Select pointer from internal slot based on index
    if (slotIndex == -1) {
        storedPointer = *(int *)(thisPtr + 0x17c);   // +0x17c: slot for index -1
    } else if (slotIndex == 0) {
        storedPointer = *(int *)(thisPtr + 0x14c);   // +0x14c: slot for index 0
    } else if (slotIndex == 1) {
        storedPointer = *(int *)(thisPtr + 0x164);   // +0x164: slot for index 1
    } else {
        return 0;
    }

    // If the slot is empty, return null
    if (storedPointer == 0) {
        return 0;
    }

    // Adjust pointer backward by 0x3c to obtain the actual container object
    // (the stored pointer points 0x3c bytes into a larger structure)
    return storedPointer - 0x3c;
}