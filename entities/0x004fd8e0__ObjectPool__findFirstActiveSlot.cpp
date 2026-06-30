// FUNC_NAME: ObjectPool::findFirstActiveSlot
int __fastcall ObjectPool::findFirstActiveSlot(int thisPtr)
{
    int index = 0;
    int count = *(int*)(thisPtr + 0x3c); // +0x3c: number of slots in pool
    if (count > 0)
    {
        int slotBase = *(int*)(thisPtr + 0x34); // +0x34: pointer to array of slot structures (0x90 bytes each)
        byte* flagPtr = (byte*)(slotBase + 0x78); // +0x78 within slot: flag byte, bit0 = active
        do
        {
            if ((*flagPtr & 1) != 0)
            {
                // Found first active slot, return its address
                return slotBase + index * 0x90;
            }
            index++;
            flagPtr += 0x90; // advance to next slot
        } while (index < count);
    }
    return 0; // no active slot found
}