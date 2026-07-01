// FUNC_NAME: GrowableArray::reserve
void __thiscall GrowableArray::reserve(int* thisPtr, uint newCapacity)
{
    // Structure: thisPtr[0] = data pointer, thisPtr[1] = count, thisPtr[2] = capacity
    // Each element is 12 bytes (0xC)
    if ((uint)thisPtr[2] < newCapacity) // +0x08: current capacity
    {
        // Allocate new block: newCapacity * elementSize (12)
        undefined8* newData = (undefined8*)FUN_009c8e80(newCapacity * 0xc); // likely malloc/new
        if (thisPtr[0] != 0) // +0x00: existing data
        {
            uint copyCount = 0;
            if (thisPtr[1] != 0) // +0x04: current number of elements
            {
                int srcOffset = 0;
                undefined8* destPtr = newData;
                do
                {
                    int srcPtr = thisPtr[0]; // base of old array
                    if (destPtr != (undefined8*)0x0)
                    {
                        // Copy 12 bytes per element
                        *destPtr = *(undefined8*)(srcPtr + srcOffset);
                        *(undefined4*)(destPtr + 1) = *(undefined4*)((undefined8*)(srcPtr + srcOffset) + 1);
                    }
                    copyCount++;
                    srcOffset += 0xc;
                    destPtr = (undefined8*)((int)destPtr + 0xc);
                } while (copyCount < (uint)thisPtr[1]);
            }
            FUN_009c8f10(thisPtr[0]); // free old data
        }
        thisPtr[0] = (int)newData;
        thisPtr[2] = newCapacity; // update capacity
    }
    return;
}