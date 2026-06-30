// FUNC_NAME: ObjectArray::removeValue
void __thiscall ObjectArray::removeValue(void* thisPtr, int valueToRemove)
{
    int* entries = *(int**)((int)thisPtr + 0x198);  // +0x198: pointer to dynamic array
    int count = *(int*)((int)thisPtr + 0x19c);      // +0x19c: number of elements

    if (count > 0)
    {
        int index = 0;
        while (entries[index] != valueToRemove)
        {
            index++;
            if (index >= count)
            {
                // Value not found – exit without modification
                return;
            }
        }

        // Value found at 'index'
        if (index != count - 1)
        {
            // Replace removed element with the last element (fast removal)
            entries[index] = entries[count - 1];
        }

        // Decrement element count
        *(int*)((int)thisPtr + 0x19c) = count - 1;
    }
}