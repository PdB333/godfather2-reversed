// FUNC_NAME: ElementArray::removeAt
void __thiscall ElementArray::removeAt(uint index)
{
    // this is the array base, count at +0xC0, each element 0xC bytes (three int32 fields)
    uint count = *(uint *)(this + 0xC0);
    if (index < count)
    {
        // Shift elements down by one position
        if (index < count - 1)
        {
            undefined8 *pSrc = (undefined8 *)(this + index * 0xC);
            do
            {
                // Copy 8 bytes (first two int32 fields)
                *pSrc = *(undefined8 *)((int)pSrc + 0xC);
                // Copy next 4 bytes (third int32 field)
                *(undefined4 *)(pSrc + 1) = *(undefined4 *)((int)pSrc + 0x14);
                index++;
                pSrc = (undefined8 *)((int)pSrc + 0xC);
            } while (index < count - 1);
        }
        // Decrement count
        count--;
        *(int *)(this + 0xC0) = count;
        // Clear the new last slot (which is now unused)
        undefined4 *pLast = (undefined4 *)(this + count * 0xC);
        if (pLast != (undefined4 *)0x0)
        {
            pLast[0] = 0;      // field1
            pLast[1] = 0;      // field2
            pLast[2] = DAT_00d5ccf8; // field3 (global default value)
        }
    }
}