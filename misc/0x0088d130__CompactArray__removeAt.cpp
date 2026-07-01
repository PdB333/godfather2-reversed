// FUNC_NAME: CompactArray::removeAt
// Address: 0x0088d130
// Role: Removes an element at a given index from a compact array of 4-byte elements stored at offset 0, count at offset 0xC8.
void __thiscall CompactArray::removeAt(uint index)
{
    // this + 0xC8 : number of elements in the array (uint)
    if (index < *(uint *)(this + 0xC8)) // index is valid
    {
        if (index < *(uint *)(this + 0xC8) - 1) // not the last element
        {
            // Shift elements left by one position, starting at index
            do {
                *(int *)(this + index * 4) = *(int *)(this + 4 + index * 4);
                index = index + 1;
            } while (index < (uint)(*(int *)(this + 0xC8) - 1));
        }
        // Decrement the element count
        *(int *)(this + 0xC8) = *(int *)(this + 0xC8) - 1;
    }
}