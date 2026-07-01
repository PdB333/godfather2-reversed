// FUNC_NAME: PointerArray::destroy
// Function address: 0x008ab5f0
// Role: Destroys a dynamic array of pointers. Iterates from the end, deletes each non-null element via FUN_004daf90 (presumably a destructor), then frees the array buffer via FUN_009c8f10 (likely operator delete[]).
// Struct layout:
//   +0x00: int* array (pointer to buffer of 8-byte elements)
//   +0x04: int count (number of elements)

void PointerArray::destroy(void)
{
    int count = *(int *)((char *)this + 4);    // +0x04: number of elements
    int *arrayPtr = *(int **)this;             // +0x00: base of array (each element is 8 bytes, but only first 4 used as pointer)
    while (count-- > 0)
    {
        if (arrayPtr[count] != 0)
        {
            FUN_004daf90(&arrayPtr[count]);    // destructor for element count
        }
    }
    if (arrayPtr != 0)
    {
        FUN_009c8f10(arrayPtr);                // free the array buffer
    }
}