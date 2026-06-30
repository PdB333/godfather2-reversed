// FUNC_NAME: EADynamicArray::removeElement
// Function address: 0x004fc010
// Role: Removes an element at the specified index from a dynamic array.
// Structure layout:
//   +0x00: unknown fields (not used here)
//   +0x08: start of 8-byte elements (each element: two 4-byte values)
//   +0x58: current number of elements (unsigned int)
// The array is embedded in the object. Removal shifts the last element into the vacated slot.

void __fastcall EADynamicArray::removeElement(unsigned int index)
{
    unsigned int count = *(unsigned int *)((char *)this + 0x58);

    if (index < count)
    {
        // If the element to remove is not the last one, move the last element into its place
        if (index < count - 1)
        {
            // Copy the two 4-byte fields of the last element (at count-1) to the removed position
            *(unsigned int *)((char *)this + 8 + index * 8) = *(unsigned int *)((char *)this + 8 + (count - 1) * 8);
            *(unsigned int *)((char *)this + 12 + index * 8) = *(unsigned int *)((char *)this + 12 + (count - 1) * 8);
        }

        // Decrement the element count
        count--;
        *(unsigned int *)((char *)this + 0x58) = count;

        // Clear the now-unused last slot (the one that was just vacated)
        unsigned int *lastSlot = (unsigned int *)((char *)this + 8 + count * 8);
        if (lastSlot != nullptr)
        {
            lastSlot[0] = 0;
            lastSlot[1] = 0;
        }
    }
}