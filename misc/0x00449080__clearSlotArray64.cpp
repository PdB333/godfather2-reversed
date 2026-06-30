// FUNC_NAME: clearSlotArray64
void clearSlotArray64(void)
{
    // this pointer in EAX: object base
    int* slotBase = (int*)((char*)this + 0x10); // start of slot array
    for (int i = 0; i < 64; i++)
    {
        // Each slot is 0x1C (28) bytes, clear 5 ints (offsets 0x08, 0x0C, 0x10, 0x14, 0x18 from slot start)
        slotBase[2] = 0;  // offset 0x08 from slot start
        slotBase[3] = 0;  // offset 0x0C
        slotBase[4] = 0;  // offset 0x10
        slotBase[5] = 0;  // offset 0x14
        slotBase[6] = 0;  // offset 0x18
        slotBase = (int*)((char*)slotBase + 0x1C); // advance to next slot
    }
}