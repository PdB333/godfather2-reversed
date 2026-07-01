// FUNC_NAME: SomeManager::getSlotAddress
int __thiscall SomeManager::getSlotAddress(int this, int outerIndex, int innerIndex)
{
    // Calculate address of a specific slot in a 2D array.
    // Layout: this + 0x7c is the base of an array of elements of size 0x50.
    // Each element contains a sub-array of size 0x10 per inner slot.
    // Returns pointer to the inner slot at (outerIndex, innerIndex).
    return this + outerIndex * 0x50 + innerIndex * 0x10 + 0x7c;
}