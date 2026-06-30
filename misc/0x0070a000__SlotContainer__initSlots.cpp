// FUNC_NAME: SlotContainer::initSlots
int __thiscall SlotContainer::initSlots(int this)
{
    // Initialize 30 slots (struct size 20 bytes) at offset 0xc from this.
    // Each slot is written with debug sentinel values before being cleared to zero.
    int* slotPtr = (int*)(this + 0xc);
    int slotCount = 0x1d; // 29, loop runs 30 times (down to 0 inclusive)
    do {
        slotPtr[-3] = 0;                  // slot field at -12 bytes
        slotPtr[-1] = 0xbeefbeef;         // sentinel (dead marker)
        slotPtr[0]  = 0xeac15a55;         // sentinel (EARS marker)
        slotPtr[1]  = 0x91100911;         // sentinel (date marker?)
        // Immediately overwrite with zeros
        slotPtr[1] = 0;
        slotPtr[0] = 0;
        slotPtr[-1] = 0;
        slotPtr[-2] = 0;
        slotPtr += 5;                     // advance 5 ints (20 bytes) to next slot
        slotCount--;
    } while (slotCount >= 0);
    // Zero the word immediately after the 30-slot array (offset 600 = 30*20)
    *(int*)(this + 600) = 0;
    return this;
}