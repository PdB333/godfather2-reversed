// FUNC_NAME: IntArray::contains
// Address: 0x008b1b10
// Searches for an integer value in a dynamic array of ints.
bool __thiscall IntArray::contains(int value) const
{
    uint index = 0;                      // current index in the loop
    uint foundIndex = 0xFFFFFFFF;        // index of found element, -1 if not found

    // +0x14: count of elements in the array
    if (*(uint *)(this + 0x14) != 0)
    {
        // +0x10: pointer to array of ints (stored as int** here; likely a handle or a pointer to pointer)
        int **arrayPtr = *(int ***)(this + 0x10);

        // Linear search: while current element != value
        while (foundIndex = index, *arrayPtr != value)
        {
            index++;
            arrayPtr++;
            if (*(uint *)(this + 0x14) <= index)
            {
                return false; // not found
            }
        }
    }

    // Return true if foundIndex is not -1
    return (int)foundIndex >= 0;
}