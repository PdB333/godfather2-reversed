// FUNC_NAME: ResourceSlotManager::TryAllocateSlot
int __thiscall ResourceSlotManager::TryAllocateSlot(int *slotArray, int **objectArray, char usePrimaryFlag)
{
    int *slotPtr;
    int **objPtrPtr;
    int result;
    uint slotIndex;
    uint iteration;

    result = 0xe1001; // default failure code
    if ((DAT_01205358 != '\0') && (this->field_0xe7e != 1)) // check global flag and this field
    {
        for (iteration = 0; iteration < 3; iteration++)
        {
            // Calculate slot index: start from (currentCounter - iteration) mod 4
            slotIndex = (this->counter - iteration) & 3;

            // Check if this slot is available based on primary flag and byte mask
            if ((usePrimaryFlag == '\0') ||
                (*(byte *)((int)this + 0x48 + slotIndex) == ((byte)(this->field_0xebe >> 4) & 1)))
            {
                slotPtr = &slotArray[slotIndex];
                if (*slotPtr == -1) // slot is free
                {
                    objPtrPtr = &objectArray[slotIndex];
                    // Call virtual method at vtable+0x1c on the object
                    result = (**(code **)(*(*objPtrPtr) + 0x1c))(*objPtrPtr, slotPtr, 4, 1);
                    if (result == 0)
                    {
                        result = 1;
                    }
                    else
                    {
                        // Map result: 1->2, 2->0, other->0
                        result = (-(uint)(result != 1) & 0xfffffffe) + 2;
                    }
                    if (result == 0)
                    {
                        *slotPtr = 0xe1001; // mark as allocated (success?)
                    }
                    else if (result == 2)
                    {
                        *slotPtr = -1; // keep as free (failure)
                    }
                    // result now holds the status after mapping
                }
                // If the slot now holds a valid non-sentinel value, return it
                if ((*slotPtr != -1) && (*slotPtr != 0xe1001))
                {
                    return *slotPtr;
                }
            }
        }
    }
    return result; // default failure value
}