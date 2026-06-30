// FUNC_NAME: NetObjectList::getObject
// Function at 0x004546d0
// Role: Returns the first 4 bytes (likely an object pointer or handle) of the element at the given index
// from a dynamic array stored in the object.
// Offsets:
//   +0x34: pointer to array (each element is 12 bytes)
//   +0x38: count (number of valid elements)
// Returns 0 if index is out of bounds.

int __thiscall NetObjectList::getObject(int index)
{
    // Check bounds against the stored count
    if ((uint)index < *(uint *)(this + 0x38))
    {
        // Access the array pointer at +0x34, then offset by index * 12 (0xC)
        // Return the first 4-byte field of that element (e.g., a pointer or object ID)
        return *(int *)(*(int *)(this + 0x34) + index * 0xC);
    }
    return 0;
}