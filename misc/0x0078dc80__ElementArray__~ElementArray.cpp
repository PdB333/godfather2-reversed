// FUNC_NAME: ElementArray::~ElementArray
void __fastcall ElementArray::~ElementArray(int *this) // this contains [0] = elements pointer, [1] = count
{
    int count = this[1]; // +0x04: number of elements
    // Iterate backwards over the array of 8-byte elements
    for (int i = count - 1; i >= 0; i--)
    {
        int* elementPtr = (int*)(this[0] + i * 8); // +0x00: base pointer, each element is 8 bytes
        if (*elementPtr != 0) // Check if the element's first field (likely a pointer or handle) is non-null
        {
            FUN_004daf90(elementPtr); // Destroy/release the element
        }
    }
    if (this[0] != 0) // +0x00: dynamic array pointer
    {
        FUN_009c8f10(this[0]); // Deallocate the array memory (likely operator delete[])
    }
    // Note: this function does not zero out this[0] or this[1]; it acts as a destructor.
}