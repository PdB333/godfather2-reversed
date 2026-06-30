// FUNC_NAME: SortedPointerArray::add
// Address: 0x006eaa20
// Role: Insert a pointer into a sorted array (sorted ascending by priority at offset 0x88), no duplicates allowed.

void __thiscall SortedPointerArray::add(void* this, void* element)
{
    // Offsets:
    // +0x30: void** m_array (pointer to array of element pointers)
    // +0x34: uint32 m_count (number of elements)
    // +0x38: uint32 m_capacity (allocated capacity)

    uint32 count = *(uint32*)((uint8*)this + 0x34);
    void*** pArray = (void***)((uint8*)this + 0x30); // pointer to the array pointer field

    uint32 i;

    // Check for duplicate (pointer equality)
    if (count != 0)
    {
        void** arr = *pArray;
        for (i = 0; i < count; i++)
        {
            if (arr[i] == element)
            {
                // Already present, early exit (the original condition (-1 < (int)i) is always true for uint)
                return;
            }
        }
    }

    // Find insertion point based on priority at offset 0x88 of the element and stored elements
    uint32 elementPriority = *(uint32*)((uint8*)element + 0x88);
    if (count != 0)
    {
        void** arr = *pArray;
        for (i = 0; i < count; i++)
        {
            uint32 currentPriority = *(uint32*)((uint8*)arr[i] + 0x88);
            if (elementPriority < currentPriority)
            {
                // Insert before this element (shift right from index i)
                void** slot = (void**)shiftRight(i); // FUN_006ea990 returns pointer to the slot at index i
                *slot = element;
                return;
            }
        }
    }

    // No insertion point found, append at end
    uint32 capacity = *(uint32*)((uint8*)this + 0x38);
    if (count == capacity)
    {
        // Reallocate (double or set to 1 if zero)
        uint32 newCapacity = (capacity == 0) ? 1 : (capacity * 2);
        reallocate(newCapacity); // FUN_006ea5e0
        // pArray still points to the field; the array pointer inside has been updated
    }

    // Append at position count
    void** targetSlot = &((*pArray)[count]); // address of array[count]
    *(uint32*)((uint8*)this + 0x34) = count + 1; // increment count
    if (targetSlot != (void**)0)
    {
        *targetSlot = element;
    }
}