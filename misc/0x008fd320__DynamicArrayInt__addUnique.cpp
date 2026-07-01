// FUNC_NAME: DynamicArrayInt::addUnique
// Function address: 0x008fd320
// Role: Adds an integer to a dynamic array if not already present, resizing if necessary.

void __thiscall DynamicArrayInt::addUnique(int thisPtr, int value)
{
    uint count = *(uint*)(thisPtr + 0x24); // current element count
    uint index = 0;

    // Search for existing element
    if (count != 0)
    {
        int* data = *(int**)(thisPtr + 0x20); // pointer to elements
        do
        {
            if (data[index] == value)
            {
                // If found and index is valid (not 0xFFFFFFFF), return without adding
                if (index != 0xFFFFFFFF)
                    return;
                break; // fall through to add if somehow index is magic value (unlikely)
            }
            index++;
        } while (index < count);
    }

    // Not found, need to add
    uint capacity = *(uint*)(thisPtr + 0x28); // current capacity
    if (count == capacity)
    {
        // Need to resize: double capacity (or set to 1 if capacity is 0)
        int newCapacity;
        if (capacity == 0)
            newCapacity = 1;
        else
            newCapacity = capacity * 2;
        FUN_008fc8f0(newCapacity); // likely reallocation function (resizes internal buffer)
    }

    // Add new element at the end
    int* data = *(int**)(thisPtr + 0x20);
    data[count] = value;
    *(uint*)(thisPtr + 0x24) = count + 1; // increment count
}