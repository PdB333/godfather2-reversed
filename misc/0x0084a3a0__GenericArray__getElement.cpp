// FUNC_NAME: GenericArray::getElement
// Function address: 0x0084a3a0
// Role: Returns the element at the given index in an array stored in the object.
// Object structure: +0x04 = pointer to array of uint (4-byte elements), +0x08 = number of elements.
uint GenericArray::getElement(uint index) // __thiscall
{
    // Return 0 if index is out of bounds
    if (index >= this->elementCount) // *(uint *)(this + 0x08)
    {
        return 0;
    }
    // Return the element at the given index from the array
    return this->arrayPointer[index]; // *(uint *)(*(int *)(this + 0x04) + index * 4)
}