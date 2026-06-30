// FUNC_NAME: EntityArrayAccessor::getElement
// Address: 0x00570f50
// Returns a pointer to an element in the dynamic array at +0x70, indexed by short at +0x76.
// Element size is 0x18 bytes.
// Returns 0 if array is null, empty, or index out of bounds.
int __fastcall EntityArrayAccessor::getElement(int thisPtr)
{
    int arrayPtr = *(int *)(thisPtr + 0x70);  // +0x70: pointer to dynamic array header
    short index = *(short *)(thisPtr + 0x76); // +0x76: index (signed short) into the array

    if (arrayPtr != 0)
    {
        int count = *(int *)(arrayPtr + 0x18);   // +0x18: element count
        int data = *(int *)(arrayPtr + 0x1c);    // +0x1c: pointer to element data buffer
        if (count > 0 && data != 0 && index >= 0 && index < count)
        {
            return data + index * 0x18;  // each element is 0x18 bytes
        }
    }
    return 0;
}