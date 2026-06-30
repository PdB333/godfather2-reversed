// FUNC_NAME: ObjectArray::removeObject
// Function address: 0x00440020
// This method removes an object pointer from a dynamic array and triggers cleanup.
// this+0x04: int* pArray;            // pointer to array of object pointers
// this+0x08: uint capacity;          // number of allocated slots
// this+0x0c: int  count;             // current number of valid entries

uint __thiscall ObjectArray::removeObject(int thisPtr, int* pObject)
{
    uint result;
    int i;
    int* pSlot;
    int pObj;                  // placeholder for temporary pointer
    int retFromFirstCall;
    
    result = 0;
    // in_EAX was originally passed in EAX (not a clean parameter); we ignore its value

    if (*(int*)(thisPtr + 8) != 0)
    {
        pSlot = *(int**)(thisPtr + 4);   // base of the pointer array
        i = 0;
        while (*pSlot != pObject)        // search for the object pointer
        {
            i++;
            pSlot++;
            if (*(uint*)(thisPtr + 8) <= (uint)i)
            {
                // Not found; return original EAX & 0xFFFFFF00
                return result;
            }
        }

        // Found: first call virtual method at vtable+0x0c on the object
        // This likely returns a pointer to some owning manager
        retFromFirstCall = (**(code**)(*pObject + 0x0c))();

        // Second: call virtual method at vtable+0x54 on the returned object
        (**(code**)(*(int*)(retFromFirstCall + 0x54) + 0x54))();

        // Remove the entry from the array
        pSlot = *(int**)(thisPtr + 4);
        *(int*)(pSlot + i * 4) = 0;      // clear the slot

        // Decrement the count
        *(int*)(thisPtr + 0x0c) = *(int*)(thisPtr + 0x0c) - 1;

        // Build return value: low byte = 1, remaining bytes from array base >> 8
        result = ((uint)pSlot >> 8) & 0xFFFFFF00 | 1;
    }

    return result;
}